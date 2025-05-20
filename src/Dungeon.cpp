#include "Dungeon.hpp"

#include <filesystem>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

Dungeon::Dungeon(UI &ui, Player &player)
    : ui(&ui), player(&player), currentTurn(Person), phase(Phase::Opening), turnCount(1),
      selectedSkillIndex(-1),
      boss("Boss", 200, 200, 100, 100, 30, 10, 1), bossHitFlash(false),
      playerHitFlash(false), openingDuration(1.5f), currentPhaseHandler(nullptr) {
    // Load background
    backgroundTexture.loadFromFile("assets/background/Dungeon.png");
    backgroundSprite.setTexture(backgroundTexture);

    // Random boss image
    randomizeBossImage();

    // Set initial phase
    setPhase(Phase::Opening);
}

void Dungeon::handleEvent(const sf::Event &event, bool &exitDungeonTest) {
    // If the dialogue is open, let it handle input and block phase input
    if (ui->dialogue.isOpen()) {
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Space) {
            ui->dialogue.continues();
        }
        return;
    }

    // Allow ESC to exit if game ended
    if (isGameEnded() && event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
        exitDungeonTest = true;
        return;
    }

    if (currentPhaseHandler)
        currentPhaseHandler->handleEvent(this, event, exitDungeonTest);
}

void Dungeon::update() {
    if (phase == Phase::Opening) {
        if (openingClock.getElapsedTime().asSeconds() > openingDuration) {
            setPhase(Phase::PlayerPick);
        }
        return;
    }
    if (currentPhaseHandler) currentPhaseHandler->update(this);
}

void Dungeon::render(sf::RenderWindow &window) {
    window.draw(backgroundSprite);

    // Font
    sf::Font font;
    font.loadFromFile("assets/fonts/Electrolize-Regular.ttf");

    // Title
    sf::Text title("Dungeon Test Mode", font, 48);
    centerText(title, 960, 60);
    title.setFillColor(sf::Color::White);
    window.draw(title);

    // Boss
    bossSprite.setColor(bossHitFlash ? sf::Color::Red : sf::Color::White);
    window.draw(bossSprite);
    if (bossHitFlash) {
        sf::RectangleShape redOverlay(sf::Vector2f(1920, 1080));
        redOverlay.setFillColor(sf::Color(255, 0, 0, 80));
        window.draw(redOverlay);
    }
    updateBossHitFlash();
    std::string bossHpStr = "Boss HP: " + std::to_string(boss.getCurrentHP());
    sf::Text    bossHpText(bossHpStr, font, 28);
    bossHpText.setPosition(1500, 1000);
    bossHpText.setFillColor(sf::Color::Red);
    window.draw(bossHpText);

    // Player hit flash
    if (playerHitFlash) {
        sf::RectangleShape redOverlay(sf::Vector2f(1920, 1080));
        redOverlay.setFillColor(sf::Color(255, 0, 0, 100));
        window.draw(redOverlay);
    }

    // Turn counter
    sf::Text turnText("Turn: " + std::to_string(turnCount), font, 32);
    turnText.setFillColor(sf::Color::Cyan);
    turnText.setPosition(30, 30);
    window.draw(turnText);

    // Opening animation
    if (phase == Phase::Opening) {
        drawCenteredBoxWithText(window, "A powerful foe appears!", 700, 100, 960,
                                440, font, 40, sf::Color(0, 0, 0, 220),
                                sf::Color::Red);
        drawCenteredBoxWithText(window, "Boss: Goku Drip Entity", 700, 80, 960,
                                540, font, 36, sf::Color(0, 0, 0, 200),
                                sf::Color::Yellow);
        window.draw(bossSprite);
        return;
    }

    // Delegate to phase handler
    if (currentPhaseHandler) currentPhaseHandler->render(this, window, font);

    // UI
    ui->render(window);

    if (player) {
        std::string playerHpStr =
            "Player HP: " + std::to_string(player->getCurrentHP());
        sf::Text playerHpText(playerHpStr, font, 28);
        playerHpText.setPosition(30, 1000);
        playerHpText.setFillColor(sf::Color::Green);
        window.draw(playerHpText);

        std::string playerManaStr =
            "Player Mana: " + std::to_string(player->getCurrentMana());
        sf::Text playerManaText(playerManaStr, font, 28);
        playerManaText.setPosition(30, 1040);
        playerManaText.setFillColor(sf::Color::Cyan);
        window.draw(playerManaText);
    }
}

void Dungeon::reset() {
    gameEnded               = false; 
    waitingForContinue      = false;
    selectedSkillIndex      = -1;
    pendingSkillIndex       = -1;
    confirmNormalAtFullMana = false;

    currentTurn        = Person;
    phase              = Phase::Opening;
    turnCount          = 1;
    selectedSkillIndex = -1;
    bossHitFlash       = false;
    playerHitFlash     = false;
    openingClock.restart();
    randomizeBossImage();
    setPhase(Phase::Opening);

    // Reset boss stats
    boss.setCurrentHP(boss.getMaxHP());

    if (player) {
        player->setCurrentMana(player->getMaxMana());
    }

    // Reset player stats
}

void Dungeon::setPhase(Phase newPhase) {
    phase = newPhase;
    switch (phase) {
        case Phase::PlayerPick  : currentPhaseHandler = &playerPickPhase; break;
        case Phase::PlayerAttack: currentPhaseHandler = &playerAttackPhase; break;
        case Phase::OpponentPick: currentPhaseHandler = &opponentPickPhase; break;
        case Phase::OpponentAttack:
            currentPhaseHandler = &opponentAttackPhase;
            ++turnCount;
            break;
        default: currentPhaseHandler = nullptr; break;
    }
}

void Dungeon::drawCenteredBoxWithText(sf::RenderWindow  &window,
                                      const std::string &message, float boxWidth,
                                      float boxHeight, float centerX,
                                      float centerY, const sf::Font &font,
                                      unsigned int charSize, sf::Color boxColor,
                                      sf::Color textColor) {
    sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
    box.setFillColor(boxColor);
    box.setOrigin(boxWidth / 2, boxHeight / 2);
    box.setPosition(centerX, centerY);
    window.draw(box);

    sf::Text text(message, font, charSize);
    centerText(text, centerX, centerY);
    text.setFillColor(textColor);
    window.draw(text);
}

void Dungeon::centerText(sf::Text &text, float x, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
    text.setPosition(x, y);
}

void Dungeon::randomizeBossImage() {
    std::vector<std::string> bossImages;
    for (const auto &entry :
         std::filesystem::directory_iterator("assets/dungeon/Boss")) {
        if (entry.is_regular_file() && (entry.path().extension() == ".PNG" ||
                                        entry.path().extension() == ".png")) {
            bossImages.push_back(entry.path().string());
        }
    }
    if (!bossImages.empty()) {
        std::random_device              rd;
        std::mt19937                    gen(rd());
        std::uniform_int_distribution<> dist(0, bossImages.size() - 1);
        std::string                     bossImagePath = bossImages[dist(gen)];
        bossTexture.loadFromFile(bossImagePath);
    }
    bossSprite.setTexture(bossTexture);
    bossSprite.setScale(0.3f, 0.3f);
    bossSprite.setPosition(1920 / 2, 500);
}

void Dungeon::showMessage(const std::string &msg) {
    ui->dialogue.setText(msg);
    ui->dialogue.open();
}