#include "Dungeon/Dungeon.hpp"

#include <filesystem>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

Dungeon::Dungeon(UI &ui, Player &player): ui(&ui), player(&player) {
    // Load *font
    font = &ui.getFont();

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

    // if (player) {
    //     player->setCurrentMana(player->getMaxMana());
    // }

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
                                      float centerY, unsigned int charSize,
                                      sf::Color boxColor, sf::Color textColor) {
    sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
    box.setFillColor(boxColor);
    box.setOrigin(boxWidth / 2, boxHeight / 2);
    box.setPosition(centerX, centerY);
    window.draw(box);

    sf::Text text(message, *font, charSize);
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
    float factor      = 0.4f;
    float size_width  = bossTexture.getSize().x * factor;
    float size_height = bossTexture.getSize().y * factor;
    bossSprite.setScale(factor, factor);
    bossSprite.setPosition((WINDOW_WIDTH - size_width) / 2,
                           WINDOW_HEIGHT - size_height);
}

void Dungeon::showMessage(const std::string &msg) {
    ui->dialogue.setText(msg);
    ui->dialogue.open();
}

void Dungeon::render(sf::RenderWindow &window) {
    window.draw(backgroundSprite);

    // Title
    sf::Text title("Dungeon Test Mode", *font, 48);
    centerText(title, 960, 60);
    title.setFillColor(sf::Color::White);
    window.draw(title);

    // Boss
    bossSprite.setColor(bossHitFlash ? sf::Color::Red : sf::Color::White);
    window.draw(bossSprite);
    if (bossHitFlash) {
        sf::RectangleShape redOverlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        redOverlay.setFillColor(sf::Color(255, 0, 0, 80));
        window.draw(redOverlay);
    }
    updateBossHitFlash();
    std::string bossHpStr = "Boss HP: " + std::to_string(boss.getCurrentHP());
    sf::Text    bossHpText(bossHpStr, *font, 28);
    bossHpText.setPosition(1500, 1000);
    bossHpText.setFillColor(sf::Color::Red);
    window.draw(bossHpText);

    // Player hit flash
    if (playerHitFlash) {
        sf::RectangleShape redOverlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        redOverlay.setFillColor(sf::Color(255, 0, 0, 100));
        window.draw(redOverlay);
    }

    // Turn counter
    sf::Text turnText("Turn: " + std::to_string(turnCount), *font, 32);
    turnText.setFillColor(sf::Color::Cyan);
    turnText.setPosition(30, 30);
    window.draw(turnText);

    // Opening animation
    if (phase == Phase::Opening) {
        drawCenteredBoxWithText(window, "A powerful foe appears!", 700, 100, 960,
                                440, 40, sf::Color(0, 0, 0, 220), sf::Color::Red);
        drawCenteredBoxWithText(window, "Boss: Goku Drip Entity", 700, 80, 960,
                                540, 36, sf::Color(0, 0, 0, 200),
                                sf::Color::Yellow);
        // window.draw(bossSprite);
        return;
    }

    // Delegate to phase handler
    if (currentPhaseHandler) currentPhaseHandler->render(this, window);

    if (player) {
        float x = 1700;
        float y = 30;

        std::string playerHpStr =
            "Player HP: " + std::to_string(player->getCurrentHP());
        sf::Text playerHpText(playerHpStr, *font, 28);
        playerHpText.setPosition(x, y);
        playerHpText.setFillColor(sf::Color::Green);
        window.draw(playerHpText);

        std::string playerManaStr =
            "Player Mana: " + std::to_string(player->getCurrentMana());
        sf::Text playerManaText(playerManaStr, *font, 28);
        playerManaText.setPosition(x, y + 40);
        playerManaText.setFillColor(sf::Color::Cyan);
        window.draw(playerManaText);
    }

    // UI
    ui->render(window);
}