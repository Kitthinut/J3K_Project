#include "Dungeon.hpp"

#include "Skill.hpp"

Dungeon::Dungeon(): currentTurn(Player) {
    if (!backgroundTexture.loadFromFile("assets/background/Dungeon.png")) {
        std::cerr << "Failed to load dungeon background!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    float scaleX = 1920.0f / backgroundTexture.getSize().x;
    float scaleY = 1080.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Dummy Skill for testing
    playerSkills = {SkillDB::FireBall, SkillDB::IceSpike, SkillDB::Heal,
                    SkillDB::Thunder, SkillDB::WindSlash};

    // --- Boss image ---
    if (!bossTexture.loadFromFile("assets/dungeon/Boss/Calculus.png")) {
        std::cerr << "Failed to load boss image!" << std::endl;
    }

    bossSprite.setTexture(bossTexture);
    bossSprite.setScale(0.7f, 0.7f);   // Adjust scale as needed
    bossSprite.setPosition(1400, 300); // Adjust position as needed

    phase = BattlePhase::Opening;
    openingClock.restart();
}

void Dungeon::handleEvent(const sf::Event &event, bool &exitDungeonTest) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            exitDungeonTest = true;
            reset();
            return;
        }

        switch (phase) {
            case BattlePhase::PlayerPick:
                if (event.key.code >= sf::Keyboard::Num1 &&
                    event.key.code <= sf::Keyboard::Num5) {
                    int skillIndex = event.key.code - sf::Keyboard::Num1;
                    if (skillIndex < playerSkills.size()) {
                        selectedSkillIndex = skillIndex;
                        // Do NOT set lastActionMessage here!
                    }
                }
                if (event.key.code == sf::Keyboard::E &&
                    selectedSkillIndex != -1) {
                    phase = BattlePhase::PlayerConfirm;
                }
                break;
            case BattlePhase::PlayerConfirm:
                if (selectedSkillIndex != -1) {
                    lastActionMessage = "Player used \"" +
                                        playerSkills[selectedSkillIndex].name +
                                        "\"!";
                    bossHitFlash = true;
                    animClock.restart();
                    phase = BattlePhase::PlayerAttackAnim;
                }
                break;
            case BattlePhase::OpponentPick:
                // Do nothing, handled by update() with a delay
                break;
            default: break;
        }
    }
}

void Dungeon::update() {

    if (phase == BattlePhase::Opening) {
        if (openingClock.getElapsedTime().asSeconds() > openingDuration) {
            phase = BattlePhase::PlayerPick;
        }
        return;
    }
    if (phase == BattlePhase::PlayerAttackAnim &&
        animClock.getElapsedTime().asSeconds() > animDuration) {
        bossHitFlash = false;
        phase        = BattlePhase::OpponentPick;
        opponentPickClock.restart(); // Start the boss "thinking" timer
    }
    if (phase == BattlePhase::OpponentPick &&
        opponentPickClock.getElapsedTime().asSeconds() > opponentPickDelay) {
        lastActionMessage =
            "Boss used \"" + playerSkills[selectedSkillIndex].name + "\"!";
        playerHitFlash = true;
        animClock.restart();
        phase = BattlePhase::OpponentAttackAnim;
    }
    if (phase == BattlePhase::OpponentAttackAnim &&
        animClock.getElapsedTime().asSeconds() > animDuration) {
        playerHitFlash     = false;
        selectedSkillIndex = -1;
        phase              = BattlePhase::PlayerPick;
        turnCount++; // Increment turn after both player and boss act
    }
}

void Dungeon::render(sf::RenderWindow &window) {
    window.draw(backgroundSprite);

    // Boss hit flash
    if (bossHitFlash) {
        bossSprite.setColor(sf::Color::Red);
    } else {
        bossSprite.setColor(sf::Color::White);
    }
    window.draw(bossSprite);

    // Player hit flash (screen overlay)
    if (playerHitFlash) {
        sf::RectangleShape redOverlay(sf::Vector2f(1920, 1080));
        redOverlay.setFillColor(sf::Color(255, 0, 0, 100));
        window.draw(redOverlay);
    }

    // Load font
    sf::Font font;
    font.loadFromFile("assets/fonts/Electrolize-Regular.ttf");

    // Title
    sf::Text title("Dungeon Test Mode", font, 48);
    centerText(title, 960, 60);
    title.setFillColor(sf::Color::White);
    window.draw(title);

    // Turn counter (always show)
    std::string turnStr = "Turn: " + std::to_string(turnCount);
    sf::Text    turnText(turnStr, font, 32);
    turnText.setFillColor(sf::Color::Cyan);
    turnText.setPosition(30, 30);
    window.draw(turnText);

    // Opening animation
    if (phase == BattlePhase::Opening) {
        drawCenteredBoxWithText(window, "A powerful foe appears!", 700, 100, 960,
                                440, font, 40, sf::Color(0, 0, 0, 220),
                                sf::Color::Red);
        drawCenteredBoxWithText(window, "Boss: Goku Drip Entity", 700, 80, 960,
                                540, font, 36, sf::Color(0, 0, 0, 200),
                                sf::Color::Yellow);
        window.draw(bossSprite);
        return;
    }

    // Draw UI based on phase
    if (phase == BattlePhase::PlayerPick) {
        // Skill list
        std::string skillList = "Skills: ";
        for (size_t i = 0; i < playerSkills.size(); ++i) {
            skillList += "[" + std::to_string(i + 1) + "] " + playerSkills[i].name;
            if (i != playerSkills.size() - 1) skillList += "  ";
        }
        drawCenteredBoxWithText(window, skillList, 1200, 80, 960, 800, font, 28,
                                sf::Color(0, 0, 0, 200), sf::Color::White);

        // Show selected skill message if any
        if (selectedSkillIndex != -1) {
            std::string msg = "Player picked \"" +
                              playerSkills[selectedSkillIndex].name +
                              "\". Press [E] to confirm.";
            drawCenteredBoxWithText(window, msg, 1000, 60, 960, 870, font, 28,
                                    sf::Color(0, 0, 0, 200), sf::Color::Yellow);
        } else {
            drawCenteredBoxWithText(window, "Press [1-5] to select skill", 800, 60,
                                    960, 900, font, 28, sf::Color(0, 0, 0, 200),
                                    sf::Color::Cyan);
        }
    } else if (phase == BattlePhase::PlayerConfirm) {
        // Show selected skill and confirm prompt
        if (selectedSkillIndex != -1) {
            std::string msg =
                "Selected: " + playerSkills[selectedSkillIndex].name +
                ". Press [E] to confirm.";
            drawCenteredBoxWithText(window, msg, 1000, 60, 960, 800, font, 28,
                                    sf::Color(0, 0, 0, 200), sf::Color::Yellow);
        }
    } else if (phase == BattlePhase::PlayerAttackAnim) {
        // Show attack message
        if (selectedSkillIndex != -1) {
            std::string msg =
                "Player used \"" + playerSkills[selectedSkillIndex].name + "\"!";
            drawCenteredBoxWithText(window, msg, 1000, 60, 960, 800, font, 28,
                                    sf::Color(0, 0, 0, 200), sf::Color::White);
        }
    } else if (phase == BattlePhase::OpponentPick) {
        drawCenteredBoxWithText(window, "Boss is choosing...", 800, 60, 960, 800,
                                font, 28, sf::Color(0, 0, 0, 200), sf::Color::Red);
    } else if (phase == BattlePhase::OpponentAttackAnim) {
        if (selectedSkillIndex != -1) {
            std::string msg =
                "Boss used \"" + playerSkills[selectedSkillIndex].name + "\"!";
            drawCenteredBoxWithText(window, msg, 1000, 60, 960, 800, font, 28,
                                    sf::Color(0, 0, 0, 200), sf::Color::Red);
        }
    }

    // // Last action message (if any)
    // if (!lastActionMessage.empty())
    //     drawCenteredBoxWithText(window, lastActionMessage, 1000, 60, 960, 700,
    //     font, 28,
    //                             sf::Color(0, 0, 0, 180), sf::Color::Yellow);
}

Dungeon::Turn Dungeon::getCurrentTurn() const { return currentTurn; }

void Dungeon::reset() {
    currentTurn = Player;
    phase       = BattlePhase::Opening;
    openingClock.restart();
    turnCount          = 1;
    selectedSkillIndex = -1;
    lastActionMessage.clear();
    bossHitFlash   = false;
    playerHitFlash = false;
}

void Dungeon::centerText(sf::Text &text, float x, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
    text.setPosition(x, y);
}

void Dungeon::drawCenteredBoxWithText(sf::RenderWindow  &window,
                                      const std::string &message, float boxWidth,
                                      float boxHeight, float centerX,
                                      float centerY, const sf::Font &font,
                                      unsigned int charSize, sf::Color boxColor,
                                      sf::Color textColor) {
    // Draw rectangle
    sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
    box.setFillColor(boxColor);
    box.setOrigin(boxWidth / 2, boxHeight / 2);
    box.setPosition(centerX, centerY);
    window.draw(box);

    // Draw centered text
    sf::Text text(message, font, charSize);
    centerText(text, centerX, centerY);
    text.setFillColor(textColor);
    window.draw(text);
}

void Dungeon::setPlayerSkills(const std::vector<Skill> &skills) {
    playerSkills = skills;
}