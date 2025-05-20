#include "Game.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

Game::Game() {
    // Game's icon
    sf::Image icon;
    if (icon.loadFromFile("assets/ui/icon_game.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    window.setFramerateLimit(60);

    // Load backgroundca
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

void Game::modifyStat(const int direction) {
    if ((direction > 0 && upgradePoints <= 0) || direction == 0) return;

    int delta = direction;
    switch (ui.popup_upgrade.getSelected()) {
        case 0:
            if (direction == -1 && player.getMaxHP() <= 10) delta = 0;
            player.increaseMaxHP(delta * 10);
            break;
        case 1:
            if (direction == -1 && player.getMaxMana() <= 0) delta = 0;
            player.increaseMaxMana(delta * 5);
            break;
        case 2:
            if (direction == -1 && player.getAttackPower() <= 0) delta = 0;
            player.increaseAttackPower(delta * 5);
            break;
        case 3:
            if (direction == -1 && player.getDefensePower() <= 0) delta = 0;
            player.increaseDefensePower(delta * 5);
            break;
    }

    player.setMoveable(true);
    upgradePoints -= delta;
    ui.popup_upgrade.close();
}

void Game::handleChoiceSelection() {
    const int selected = ui.popup_choice.getSelected();
    switch (player.GetInteract()) {
        case Computor:
            std::cout << "Enter Mini-Dungeon" << std::endl;
            player.setMoveable(true);
            break;
        case Wardrobe:
            std::cout << "You chose to upgrade stats!" << std::endl;
            ui.popup_upgrade.open();
            break;
        case Dining:
            std::cout << "Dining" << std::endl;
            switch (selected) {
                case 0 : player.increaseCurrentHP(30); break;
                case 1 : player.increaseCurrentMana(10); break;
                default: break;
            }
            player.setMoveable(true);
            break;
        case Bed:
            std::cout << "Bed" << std::endl;
            switch (selected) {
                case 0 : player.increaseCurrentHP(50); break;
                case 1 : player.increaseCurrentHP(20); break;
                default: break;
            }
            player.setMoveable(true);
            break;
        case Teacher_Table:
            if (!inDungeonTest) {
                std::cout << "You chose to play games!" << std::endl;
                inDungeonTest = true;
                dungeon.reset();
                ui.setDungeon(true);
                player.setMoveable(true);
            }
            break;
        default: break;
    }

    // Hide the choice popup after selection
    ui.popup_choice.close();
}

void Game::openPopupForInteraction() {
    switch (player.GetInteract()) {
        case Computor:
            ui.popup_choice.open();
            ui.popup_choice.setChoices({"Enter Mini-Dungeon"});
            player.setMoveable(false);
            break;
        case Wardrobe:
            ui.popup_choice.open();
            ui.popup_choice.setChoices({"Upgrade Stats"});
            player.setMoveable(false);
            break;
        case Dining:
            ui.popup_choice.open();
            ui.popup_choice.setChoices({"[food left] Eat Food (+30 HP)",
                                        "Drink Water (+10 HP)", "Drink Potion"});
            player.setMoveable(false);
            break;
        case Bed:
            ui.popup_choice.open();
            ui.popup_choice.setChoices({"Sleep (+50 HP)", "Nap (+20 HP)"});
            player.setMoveable(false);
            break;
        case Teacher_Table:
            ui.popup_choice.open();
            ui.popup_choice.setChoices({"Enter Class"});
            player.setMoveable(false);
            break;
        default: break;
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            break;
        }

        if (inDungeonTest) {
            bool exitDungeonTest = false;
            dungeon.handleEvent(event, exitDungeonTest);
            if (exitDungeonTest) {
                inDungeonTest = false;
                ui.setDungeon(false);

                player.setMoveable(true);
                if (player.getCurrentHP() <= 0) {
                    player.setCurrentHP(player.getMaxHP() / 2);
                }
                return;
            }
            break;
        }

        if (event.type != sf::Event::KeyPressed) break;
        const sf::Keyboard::Key key = event.key.code;

        switch (key) {
            case sf::Keyboard::Escape:
                player.setMoveable(true);
                ui.closePopUp();
                break;
            case sf::Keyboard::C:
                // Toggle character info screen
                ui.popup_character_info.isOpen() ? ui.popup_character_info.close()
                                                 : ui.popup_character_info.open();
                break;
            case sf::Keyboard::Space:
                if (ui.dialogue.isOpen()) {
                    ui.dialogue.continues();
                } else if (ui.popup_choice.isOpen()) {
                    handleChoiceSelection();
                } else if (!ui.popUpIsOpen()) {
                    openPopupForInteraction();
                }
                break;
            default: break;
        }

        // Handle choice navigation
        if (ui.popup_choice.isOpen()) {
            switch (key) {
                case sf::Keyboard::Up  : ui.popup_choice.moveSelection(-1); break;
                case sf::Keyboard::Down: ui.popup_choice.moveSelection(1); break;
                default                : break;
            }
        }

        // Handle stat selection in the upgrade popup
        if (ui.popup_upgrade.isOpen()) {
            switch (key) {
                case sf::Keyboard::Up   : ui.popup_upgrade.moveSelection(-1); break;
                case sf::Keyboard::Down : ui.popup_upgrade.moveSelection(1); break;
                case sf::Keyboard::Right: modifyStat(1); break;
                case sf::Keyboard::Left : modifyStat(-1); break;
                default                 : break;
            }
        }
    }
}

void Game::update() {
    if (inDungeonTest) {
        dungeon.update();
        return;
    }

    // Update HP and Mana bars
    Volume hp   = {player.getCurrentHP(), player.getMaxHP()};
    Volume mana = {player.getCurrentMana(), player.getMaxMana()};
    Volume exp  = {player.getEXP(), player.getEXPtoNextLevel()};
    ui.setBarsVolume(hp, mana, exp);
    ui.popup_character_info.update(playerName, 1, hp, mana, exp);
    ui.popup_upgrade.update(hp, mana, player.getAttackPower(),
                            player.getDefensePower());

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

    if (inDungeonTest) {
        dungeon.render(window);
    } else {
        window.draw(background);
        player.draw(window);
        ui.render(window);
    }

    window.display();
}

void Game::run() {
    // story.introduction(window);
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
    story.showCredits(window);
}