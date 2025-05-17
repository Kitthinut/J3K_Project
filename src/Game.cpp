#include "Game.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

Game::Game() {
    // Load background
    if (!backgroundTexture.loadFromFile("assets/background/Dorm.png")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    background.setTexture(backgroundTexture);
    background.setScale(WINDOW_WIDTH / backgroundTexture.getSize().x,
                        WINDOW_HEIGHT / backgroundTexture.getSize().y);

    ui.dialogue.setText("Welcome to FIBO XI Dungeon!\nYou have to survive 80 "
                        "days here to receive your grade!");
}

void Game::changeRoomTo(Room room, std::string path, sf::Vector2f spawn_pos) {

    // Load new background or update other data
    if (!backgroundTexture.loadFromFile(path)) {
        std::cerr << "Failed to load classroom background!" << std::endl;
    }
    background.setTexture(backgroundTexture);
    background.setScale(WINDOW_WIDTH / backgroundTexture.getSize().x,
                        WINDOW_HEIGHT / backgroundTexture.getSize().y);

    // Transition to another room
    player.setPosition(spawn_pos);

    player.getCollision().setCurrentRoom(room);
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            break;
        }

        if (event.type != sf::Event::KeyPressed) break;
        const sf::Keyboard::Key key = event.key.code;

        if (key == sf::Keyboard::C) {
            // Toggle character info screen
            if (ui.popup_character_info.isOpen()) ui.popup_character_info.close();
            else ui.popup_character_info.open();
        }

        if (key == sf::Keyboard::Escape) ui.closePopUp();

        if (key == sf::Keyboard::Space) {
            if (ui.dialogue.isOpen()) {
                ui.dialogue.continues();
            } else if (ui.popup_choice.isOpen()) {
                // Apply the selected choice
                switch (ui.popup_choice.getSelected()) {
                    case 0:
                        std::cout << "You chose to upgrade stats!" << std::endl;
                        ui.popup_upgrade.open();
                        break;
                    case 1:
                        std::cout << "You chose to play games!" << std::endl;
                        break;
                    default: break;
                }

                // Hide the choice popup after selection
                ui.popup_choice.close();
            } else {
                switch (player.GetInteract()) {
                    case Computor:
                        ui.popup_choice.open();
                        ui.popup_choice.setChoices(
                            {"Upgrade Stats", "Play Games"});
                        break;

                    default: break;
                }
            }
        }

        // Handle choice navigation (Up/Down keys)
        if (ui.popup_choice.isOpen()) {
            if (key == sf::Keyboard::Up) ui.popup_choice.moveSelection(-1);
            else if (key == sf::Keyboard::Down) ui.popup_choice.moveSelection(1);
        }

        // Handle stat selection in the upgrade popup (Up/Down)
        if (ui.popup_upgrade.isOpen()) {
            if (key == sf::Keyboard::Up) ui.popup_upgrade.moveSelection(-1);
            else if (key == sf::Keyboard::Down) ui.popup_upgrade.moveSelection(1);
        }

        // Handle plus/minus for upgrading stats
        if (ui.popup_upgrade.isOpen()) {
            int selected = ui.popup_upgrade.getSelected();
            if (key == sf::Keyboard::Left) {
                if (selected == 0 && upgradePoints > 0) {
                    maxHP += 10;
                    upgradePoints--;
                } else if (selected == 1 && upgradePoints > 0) {
                    maxMana += 5;
                    upgradePoints--;
                }
                ui.popup_upgrade.close();
            } else if (key == sf::Keyboard::Right) {
                if (selected == 0 && maxHP > 0) {
                    maxHP -= 10;
                    upgradePoints++;
                } else if (selected == 1 && maxMana > 0) {
                    maxMana -= 5;
                    upgradePoints++;
                }
                ui.popup_upgrade.close();
            }
        }
    }
}

void Game::update() {
    // Update HP and Mana bars
    Volume hp   = {currentHP, maxHP};
    Volume mana = {currentMana, maxMana};
    Volume exp  = {currentEXP, maxEXP};
    ui.setBarsVolume(hp, mana, exp);
    ui.popup_character_info.update(playerName, 1, hp, mana, exp);
    ui.popup_upgrade.update(currentHP, currentMana);

    // Update Movement
    player.update();
    switch (player.warpTo()) {
        case Dorm:
            changeRoomTo(Classroom, "assets/background/Classroom.png", {460, 220});
            break;
        case Classroom:
            changeRoomTo(Dorm, "assets/background/Dorm.png", {660, 800});
            break;
        default: break;
    }
}

void Game::render() {
    window.clear();
    window.draw(background);
    player.draw(window);
    ui.render(window);
    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}