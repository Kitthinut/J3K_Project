#include "Game.hpp"

#include "Struct/CollisionManager.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

Game::Game() {

    // Load character portrait
    if (!portraitTexture.loadFromFile("assets/characters/temp-1.png")) {
        std::cerr << "Failed to load portrait texture!" << std::endl;
    }
    portrait.setTexture(portraitTexture);
    portrait.setPosition(500, 500);

    // Load background
    if (!backgroundTexture.loadFromFile("assets/background/Dorm.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    background.setTexture(backgroundTexture);
    background.setScale(WINDOW_WIDTH / backgroundTexture.getSize().x,
                        WINDOW_HEIGHT / backgroundTexture.getSize().y);

    dialogueBox.setText("Welcome to FIBO XI Dungeon!\nYou have to survive 80 "
                        "days here to receive your grade!");

    portrait.setPosition(playerPosition);

    // Obstacles
    // obstacles.push_back(sf::FloatRect(600, 200, 150, 150));
    obstacles.push_back(sf::FloatRect(440, 200, 150, 150));

    // Interactables
    sf::Vector2f interactableSize(40, 40);
    sf::Vector2f bottomRightPosition(window.getSize().x - interactableSize.x - 20,
                                     window.getSize().y - interactableSize.y - 20);

    interactables.push_back(
        {.bounds     = sf::FloatRect(bottomRightPosition, interactableSize),
         .name       = "Play Station",
         .onInteract = [this]() {
             ui.popup_choice.open();
             ui.popup_choice.setChoices(
                 {"Upgrade Stats", "Select side quests", "Play Games", "Go to sleep"});
         }});

    // Load player sprite
    if (!spriteSheet.loadFromFile("assets/characters/temp-1.png")) {
        std::cerr << "Failed to load sprite sheet!" << std::endl;
    }
    playerSprite.setScale(3.0f, 3.0f);
    playerSprite.setTexture(spriteSheet);
    playerSprite.setTextureRect(sf::IntRect(currentFrame * PLAYER_FRAME,
                                            playerDirection * PLAYER_FRAME, PLAYER_FRAME,
                                            PLAYER_FRAME));
    playerSprite.setPosition(playerPosition);

    collisionManager.setCurrentRoom(Room::Dorm);
    obstacles = collisionManager.getCurrentObstacles();
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::C) {
                // Toggle character info screen
                showCharacterInfo = !showCharacterInfo;
            }

            if (event.key.code == sf::Keyboard::Space) {
                if (ui.popup_choice.isOpen()) {
                    // Apply the selected choice
                    switch (ui.popup_choice.getSelected()) {
                        case 0:
                            std::cout << "You chose to upgrade stats!" << std::endl;
                            showUpgradeStatsPopup = true; // Show the upgrade stats window
                            break;
                        case 1:
                            std::cout << "You chose to play games!" << std::endl;
                            break;
                        case 2 : showStatsPopup = true; break;
                        default: break;
                    }

                    // Hide the choice popup after selection
                    ui.popup_choice.close();
                } else if (showStatsPopup) {
                    showStatsPopup = false; // Close the stats window when space
                                            // is pressed again
                } else if (showUpgradeStatsPopup) {
                    // Apply upgrade changes
                    if (selectedStat == 0) // HP upgrade
                    {
                        if (upgradePoints > 0) {
                            currentHP += 10;
                            upgradePoints--; // Deduct one upgrade point
                        }
                    } else if (selectedStat == 1) // Mana upgrade
                    {
                        if (upgradePoints > 0) {
                            currentMana += 5;
                            upgradePoints--; // Deduct one upgrade point
                        }
                    }
                    // Close the upgrade stats popup when space is pressed
                    showUpgradeStatsPopup = false;
                } else {
                    // No popup, handle interaction with an object
                    bool interacted = false;
                    for (auto &obj : interactables) {
                        if (playerSprite.getGlobalBounds().intersects(obj.bounds)) {
                            if (obj.name == "Play Station") {
                                // Show the choices (you could change this dynamically)
                                ui.popup_choice.open();
                                ui.popup_choice.setChoices(
                                    {"Upgrade Stats", "Play Games", "Check Stats"});
                            } else {
                                obj.onInteract(); // Regular interaction
                            }
                            interacted = true;
                            break;
                        }
                    }
                    if (!interacted) {
                        dialogueBox.advance(); // No interaction, advance dialogue
                    }
                }
            }

            // Handle choice navigation (Up/Down keys)
            if (ui.popup_choice.isOpen()) {
                if (event.key.code == sf::Keyboard::Up) ui.popup_choice.moveSelection(-1);
                else if (event.key.code == sf::Keyboard::Down)
                    ui.popup_choice.moveSelection(1);
            }

            // Handle stat selection in the upgrade popup (Up/Down)
            if (showUpgradeStatsPopup) {
                if (event.key.code == sf::Keyboard::Up)
                    selectedStat =
                        (selectedStat + 1) % 2; // Toggle between HP (0) and Mana (1)
                else if (event.key.code == sf::Keyboard::Down)
                    selectedStat = (selectedStat + 1) % 2;
            }

            // Handle plus/minus for upgrading stats
            if (showUpgradeStatsPopup) {
                if (event.key.code == sf::Keyboard::Right) // Plus
                {
                    if (selectedStat == 0 && upgradePoints > 0) // HP
                    {
                        currentHP += 10;
                        upgradePoints--;
                    } else if (selectedStat == 1 && upgradePoints > 0) // Mana
                    {
                        currentMana += 5;
                        upgradePoints--;
                    }
                } else if (event.key.code == sf::Keyboard::Left) // Minus
                {
                    if (selectedStat == 0 && currentHP > 0) // HP
                    {
                        currentHP -= 10;
                        upgradePoints++;
                    } else if (selectedStat == 1 && currentMana > 0) // Mana
                    {
                        currentMana -= 5;
                        upgradePoints++;
                    }
                }
            }
        }
    }
}

void Game::update() {
    // Update HP and Mana bars
    ui.setBarVolume({currentHP, maxHP}, {currentMana, maxMana}, {currentEXP, maxEXP});

    // Movement logic (updating position and direction)
    sf::Vector2f movement(0.f, 0.f);
    sf::Time     deltaTime = clock.restart();
    float        dt        = deltaTime.asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y      -= playerSpeed * dt;
        playerDirection  = Up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y      += playerSpeed * dt;
        playerDirection  = Down;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x      -= playerSpeed * dt;
        playerDirection  = Left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x      += playerSpeed * dt;
        playerDirection  = Right;
    }

    // Update animation frame if the player is moving
    static float animationTimer = 0.0f;
    float        animationSpeed = 0.1f; // Adjust animation speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        animationTimer += dt;
        if (animationTimer >= animationSpeed) {
            animationTimer = 0.0f;
            currentFrame   = (currentFrame + 1) % 4; // Loop through 4 frames
            playerSprite.setTextureRect(sf::IntRect(currentFrame * PLAYER_FRAME,
                                                    playerDirection * PLAYER_FRAME,
                                                    PLAYER_FRAME, PLAYER_FRAME));
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        movement.x *= 2;
        movement.y *= 2;
    }

    // Predict next position for collision detection
    sf::FloatRect nextBounds  = playerSprite.getGlobalBounds();
    nextBounds.left          += movement.x;
    nextBounds.top           += movement.y;

    playerSprite.setPosition(playerPosition); // Update sprite position

    if (playerPosition.y > 1080) {
        // Transition to another room
        currentRoom = Classroom;
        collisionManager.setCurrentRoom(Room::Classroom);
        obstacles      = collisionManager.getCurrentObstacles();
        playerPosition = sf::Vector2f(800, 100); // Reset position in new room
        playerSprite.setPosition(playerPosition);

        // Load new background or update other data
        if (!backgroundTexture.loadFromFile("assets/background/Classroom.png")) {
            std::cerr << "Failed to load classroom background!" << std::endl;
        }
        background.setTexture(backgroundTexture);
        background.setScale(WINDOW_WIDTH / backgroundTexture.getSize().x,
                            WINDOW_HEIGHT / backgroundTexture.getSize().y);

        dialogueBox.setText("You entered the classroom.");
    }

    // Move to LOBBY if walking up off the screen
    if (playerPosition.y < 0) {
        currentRoom = Dorm;
        collisionManager.setCurrentRoom(Room::Classroom);
        obstacles      = collisionManager.getCurrentObstacles();
        playerPosition = sf::Vector2f(800, 900); // Spawn from bottom
        playerSprite.setPosition(playerPosition);

        if (!backgroundTexture.loadFromFile("assets/background/Dorm.png")) {
            std::cerr << "Failed to load lobby background!" << std::endl;
        }
        background.setTexture(backgroundTexture);
        background.setScale(WINDOW_WIDTH / backgroundTexture.getSize().x,
                            WINDOW_HEIGHT / backgroundTexture.getSize().y);

        dialogueBox.setText("You entered the lobby.");
    }
}

void Game::render() {
    window.clear();
    window.draw(background);
    window.draw(playerSprite);
    dialogueBox.draw(window);
    ui.render(window);

    // Draw interactables
    for (const auto &obj : interactables) {
        sf::RectangleShape box;
        box.setPosition(obj.bounds.left, obj.bounds.top);
        box.setSize(sf::Vector2f(obj.bounds.width, obj.bounds.height));

        if (playerSprite.getGlobalBounds().intersects(obj.bounds)) {
            box.setFillColor(sf::Color(255, 255, 0, 100)); // Yellow highlight
            box.setOutlineColor(sf::Color::Yellow);
            box.setOutlineThickness(3);
        } else {
            box.setFillColor(sf::Color(0, 255, 0, 50)); // Green highlight
            box.setOutlineColor(sf::Color::Green);
            box.setOutlineThickness(1);
        }

        window.draw(box);
    }

    // Draw obstacle collision boxes
    for (const auto &box : obstacles) {
        sf::RectangleShape rect;
        rect.setPosition(box.left, box.top);
        rect.setSize(sf::Vector2f(box.width, box.height));
        rect.setFillColor(sf::Color(255, 0, 0, 100)); // Red
        window.draw(rect);
    }

    // // ==== Stats Popup ====
    // if (showStatsPopup) {
    //     sf::RectangleShape statsWindow(sf::Vector2f(500, 300));
    //     statsWindow.setFillColor(sf::Color(0, 0, 0, 200));
    //     statsWindow.setOutlineThickness(3);
    //     statsWindow.setOutlineColor(sf::Color::White);
    //     statsWindow.setPosition(710, 390);
    //     window.draw(statsWindow);

    //     std::vector<std::string> lines = {
    //         "Player Stats",
    //         "HP: " + std::to_string(currentHP) + " / " + std::to_string(maxHP),
    //         "Mana: " + std::to_string(currentMana) + " / " + std::to_string(maxMana),
    //         "Grades: A- (placeholder)", "Tasks Completed: 5/10 (placeholder)"};

    //     for (size_t i = 0; i < lines.size(); ++i) {
    //         sf::Text line(lines[i], gameFont, 24);
    //         line.setPosition(730, 410 + i * 40);
    //         line.setFillColor(sf::Color::White);
    //         window.draw(line);
    //     }
    // }

    // // ==== Upgrade Stats Popup ====
    // if (showUpgradeStatsPopup) {
    //     sf::RectangleShape upgradeStatsWindow(sf::Vector2f(500, 300));
    //     upgradeStatsWindow.setFillColor(sf::Color(0, 0, 0, 200));
    //     upgradeStatsWindow.setOutlineThickness(3);
    //     upgradeStatsWindow.setOutlineColor(sf::Color::White);
    //     upgradeStatsWindow.setPosition(710, 390);
    //     window.draw(upgradeStatsWindow);

    //     // Upgrade points
    //     sf::Text upgradePointsText("Upgrade Points: " + std::to_string(upgradePoints),
    //                                gameFont, 24);
    //     upgradePointsText.setPosition(1300, 50);
    //     upgradePointsText.setFillColor(sf::Color::White);
    //     window.draw(upgradePointsText);

    //     // === HP Stat ===
    //     sf::Text hpText("HP: " + std::to_string(currentHP), gameFont, 24);
    //     hpText.setPosition(730, 410);
    //     hpText.setFillColor(sf::Color::White);
    //     window.draw(hpText);

    //     sf::RectangleShape hpMinusButton(sf::Vector2f(30, 30));
    //     hpMinusButton.setPosition(880, 410);
    //     hpMinusButton.setFillColor(sf::Color::Red);
    //     window.draw(hpMinusButton);

    //     sf::Text hpMinusText("-", gameFont, 24);
    //     hpMinusText.setPosition(885, 413);
    //     hpMinusText.setFillColor(sf::Color::White);
    //     window.draw(hpMinusText);

    //     sf::RectangleShape hpPlusButton(sf::Vector2f(30, 30));
    //     hpPlusButton.setPosition(930, 410);
    //     hpPlusButton.setFillColor(sf::Color::Green);
    //     window.draw(hpPlusButton);

    //     sf::Text hpPlusText("+", gameFont, 24);
    //     hpPlusText.setPosition(935, 413);
    //     hpPlusText.setFillColor(sf::Color::White);
    //     window.draw(hpPlusText);

    //     // === Mana Stat ===
    //     sf::Text manaText("Mana: " + std::to_string(currentMana), gameFont, 24);
    //     manaText.setPosition(730, 460);
    //     manaText.setFillColor(sf::Color::White);
    //     window.draw(manaText);

    //     sf::RectangleShape manaMinusButton(sf::Vector2f(30, 30));
    //     manaMinusButton.setPosition(880, 460);
    //     manaMinusButton.setFillColor(sf::Color::Red);
    //     window.draw(manaMinusButton);

    //     sf::Text manaMinusText("-", gameFont, 24);
    //     manaMinusText.setPosition(885, 463);
    //     manaMinusText.setFillColor(sf::Color::White);
    //     window.draw(manaMinusText);

    //     sf::RectangleShape manaPlusButton(sf::Vector2f(30, 30));
    //     manaPlusButton.setPosition(930, 460);
    //     manaPlusButton.setFillColor(sf::Color::Green);
    //     window.draw(manaPlusButton);

    //     sf::Text manaPlusText("+", gameFont, 24);
    //     manaPlusText.setPosition(935, 463);
    //     manaPlusText.setFillColor(sf::Color::White);
    //     window.draw(manaPlusText);
    // }

    // // Draw the character info screen if it's active
    // if (showCharacterInfo) {
    //     // Create a background for the character info popup
    //     sf::RectangleShape infoWindow(sf::Vector2f(600, 400));
    //     infoWindow.setFillColor(sf::Color(0, 0, 0, 200)); // Semi-transparent black
    //     infoWindow.setOutlineThickness(5);
    //     infoWindow.setOutlineColor(sf::Color::White);
    //     infoWindow.setPosition(660, 300); // Position in the center

    //     // Draw the info window
    //     window.draw(infoWindow);

    //     // Display character details
    //     std::vector<std::string> lines = {
    //         "Character Info",
    //         "Name: " + playerName,
    //         "Level: " + std::to_string(playerLevel),
    //         "HP: " + std::to_string(currentHP) + " / " + std::to_string(maxHP),
    //         "Mana: " + std::to_string(currentMana) + " / " + std::to_string(maxMana),
    //         "Coins: " + std::to_string(ui.coin.getCoins())};

    //     // Set font for the text
    //     for (size_t i = 0; i < lines.size(); ++i) {
    //         sf::Text text(lines[i], gameFont, 24);
    //         text.setPosition(680, 320 + i * 40); // Slight padding between lines
    //         text.setFillColor(sf::Color::White);
    //         window.draw(text);
    //     }
    // }

    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}