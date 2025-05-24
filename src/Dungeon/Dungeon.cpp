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

    // Load boss texture
    for (const auto &entry :
         std::filesystem::directory_iterator("assets/dungeon/Boss")) {
        if (entry.is_regular_file() && (entry.path().extension() == ".PNG" ||
                                        entry.path().extension() == ".png")) {
            bossImages.push_back(entry.path().string());
        }
    }
    boss.setSkill(0, new Skill("Normal Attact", 0, 0, 10, 1.0f, 0));
    
    // Set initial phase
    setPhase(Phase::Opening);
}

void Dungeon::handleEvent(const sf::Event &event, bool &exitDungeonTest) {
    // If the dialogue is open, let it handle input and block phase input
    if (!gameEnded && ui->dialogue.isOpen()) {
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Space) {
            ui->dialogue.continues();
        }
        return;
    }

    if (event.type != sf::Event::KeyPressed) return;

    // Allow ESC to exit if game ended
    if (isGameEnded() && event.key.code == sf::Keyboard::Escape) {
        exitDungeonTest = true;
        ui->dialogue.close();
        return;
    }

    if (currentPhaseHandler)
        currentPhaseHandler->handleEvent(event.key.code, exitDungeonTest);
}

void Dungeon::update() {
    if (phase == Phase::Opening) {
        if (openingClock.getElapsedTime().asSeconds() > openingDuration) {
            setPhase(Phase::PlayerPick);
        }
        return;
    }
    if (currentPhaseHandler) currentPhaseHandler->update();
}

void Dungeon::reset() {
    gameEnded          = false;
    waitingForContinue = false;
    selectedSkillIndex = -1;
    pendingSkillIndex  = -1;

    currentTurn        = Person;
    phase              = Phase::Opening;
    turnCount          = 1;
    selectedSkillIndex = -1;
    bossHitFlash       = false;
    playerHitFlash     = false;
    openingClock.restart();
    randomizeBoss();
    setPhase(Phase::Opening);
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

void Dungeon::triggerBossHitFlash() {
    bossHitFlash = true;
    HitClock.restart();
}

void Dungeon::triggerPlayerHitFlash() {
    playerHitFlash = true;
    HitClock.restart();
}

void Dungeon::updateHitFlash() {
    if (HitClock.getElapsedTime().asSeconds() <= hitFlashDuration) return;

    if (bossHitFlash) bossHitFlash = false;
    else if (playerHitFlash) playerHitFlash = false;
}

void Dungeon::drawCenteredBoxWithText(sf::RenderWindow  &window,
                                      const std::string &message, float boxWidth,
                                      float boxHeight, float centerX,
                                      float centerY, unsigned int charSize,
                                      sf::Color boxColor, sf::Color textColor) {
    sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
    box.setFillColor(boxColor);
    float x = centerX - (boxWidth / 2);
    float y = centerY - (boxHeight / 2);
    box.setPosition(x, y);
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

void Dungeon::randomizeBoss() {
    if (!bossImages.empty()) {
        std::random_device              rd;
        std::mt19937                    gen(rd());
        std::uniform_int_distribution<> dist(0, bossImages.size() - 1);
        std::string                     bossImagePath = bossImages[dist(gen)];

        size_t      pos      = bossImagePath.find_last_of("/\\");
        std::string bossName = bossImagePath.substr(
            pos + 1, bossImagePath.find_last_of(".") - pos - 1);
        boss.setName(bossName);
        bossTexture.loadFromFile(bossImagePath);
    }
    bossSprite.setTexture(bossTexture);
    float factor      = 0.4f;
    float size_width  = bossTexture.getSize().x * factor;
    float size_height = bossTexture.getSize().y * factor;
    bossSprite.setScale(factor, factor);
    bossSprite.setPosition((WINDOW_WIDTH - size_width) / 2,
                           WINDOW_HEIGHT - size_height);

    int level = (player->getLevel() - 5) + (rand() % 11);
    if (level < 1) level = 1; // Ensure level is at least 1
    float hp  = 100 + (2 * level * BOSS_FACTOR);
    float atk = (10 + level) * BOSS_FACTOR;
    float def = 10 + (level * BOSS_FACTOR);
    boss.setLevel(level);
    boss.setCurrentHP(hp);
    boss.setAttackPower(atk);
    boss.setDefensePower(def);
}

void Dungeon::showMessage(const std::string &msg) {
    ui->dialogue.setText(msg);
    ui->dialogue.open();
}

void Dungeon::render(sf::RenderWindow &window) {
    window.draw(backgroundSprite);

    // Title
    // sf::Text title("Class", *font, 48);
    // centerText(title, WINDOW_WIDTH / 2, 60);
    // title.setFillColor(sf::Color::White);
    // window.draw(title);

    updateHitFlash();

    // Boss
    bossSprite.setColor(bossHitFlash ? sf::Color::Red : sf::Color::White);
    window.draw(bossSprite);
    std::string bossLevel = "Lv: " + std::to_string(boss.getLevel());
    std::string bossHpStr = "Boss HP: " + std::to_string(boss.getCurrentHP());
    drawCenteredBoxWithText(window, bossLevel, 300, 60, WINDOW_WIDTH / 2, 170, 30,
                            sf::Color(0, 0, 0, 180), sf::Color::White);
    drawCenteredBoxWithText(window, bossHpStr, 300, 60, WINDOW_WIDTH / 2, 230, 30,
                            sf::Color(0, 0, 0, 180), sf::Color::Red);

    // Player hit flash
    if (playerHitFlash) {
        sf::RectangleShape redOverlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        redOverlay.setFillColor(sf::Color(255, 0, 0, 80));
        window.draw(redOverlay);
    }

    // Turn counter
    sf::Text turnText("Turn: " + std::to_string(turnCount), *font, 32);
    turnText.setFillColor(sf::Color::Cyan);
    turnText.setPosition(30, 30);
    window.draw(turnText);

    // Opening animation
    if (phase == Phase::Opening) {
        drawCenteredBoxWithText(window, "A powerful foe appears!",
                                WINDOW_WIDTH / 2, 100, 960, 440, 40,
                                sf::Color(0, 0, 0, 220), sf::Color::Red);
        drawCenteredBoxWithText(window, "Boss: " + boss.getName(),
                                WINDOW_WIDTH / 2, 80, 960, 540, 36,
                                sf::Color(0, 0, 0, 200), sf::Color::Yellow);
        return;
    }

    // Delegate to phase handler
    if (currentPhaseHandler) currentPhaseHandler->render(window);

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