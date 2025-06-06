#include "Game/Game.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

Game::Game() {
    // Game's icon
    sf::Image icon;
    if (icon.loadFromFile("assets/ui/Icon.PNG")) {
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

    // Introduction / How to play
    ui.dialogue.setText("Welcome to FIBO XI Dungeon!\n"
                        "You're stuck in a mysterious academic maze...\n"
                        "Survive 40 days to break free!\n"
                        "Controls:"
                        "Move with 'W' 'A' 'S' 'D'\n"
                        "Hold 'Left Shift' to run\n"
                        "Press 'C' to check your character stats\n"
                        "Look out for glowing objects - those are interactive!\n"
                        "Press 'SPACE' to interact with objects or people\n"
                        "Doors to other rooms are visible on your map!\n"
                        "Tip: Plan carefully, every action consumes time.\n"
                        "Good luck, and enjoy your journey here! ^_^\n"
                        "Press 'SPACE' to start your adventure!");
}

// Function to change the room and update the background
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

// Function to modify player stats based on the selected upgrade
void Game::modifyStat(const int direction) {
    if ((direction > 0 && player.getStatePoint() <= 0) || direction == 0) return;

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
    player.increaseStatePoint(-delta);
    ui.popup_upgrade.close();
}

// Function to handle the selection of choices in the popup
void Game::handleChoiceSelection() {
    const int selected = ui.popup_choice.getSelected();
    switch (player.GetInteract()) {
        case Wardrobe:
            std::cout << "You chose to upgrade stats!" << std::endl;
            ui.popup_upgrade.open();
            break;
        case Bed:
            std::cout << "Bed" << std::endl;
            switch (selected) {
                case 0:
                    player.setCurrentHP(player.getMaxHP());
                    NextDay();
                    break;
                case 1:
                    player.increaseCurrentHP(player.getCurrentHP() / 2);
                    --slot_remaining;
                    break;
                default: break;
            }

            player.setMoveable(true);
            break;
        case Teacher_Table:
            if (!inDungeonTest) {
                std::cout << "You chose to play games!" << std::endl;
                --slot_remaining;
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

// Function to open the appropriate popup based on the player's interaction
void Game::openPopupForInteraction() {
    switch (player.GetInteract()) {
        case Wardrobe:
            ui.popup_choice.open();
            ui.popup_choice.setChoices({"Upgrade Stats"});
            player.setMoveable(false);
            break;
        case Bed:
            ui.popup_choice.open();
            ui.popup_choice.setChoices(
                {"Sleep (+100% HP & Skip Day)", "Rest (+50% HP)"});
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

void Game::NextDay() {
    ++day;
    slot_remaining = 5; // Reset skill points for the next day
}

// Function to process events such as key presses and window events
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            break;
        }

        if (event.type != sf::Event::KeyPressed) break;

        if (inDungeonTest) {
            bool exitDungeonTest = false;
            dungeon.handleEvent(event, exitDungeonTest);
            if (exitDungeonTest) {
                inDungeonTest = false;
                ui.setDungeon(false);

                player.setMoveable(true);
                if (player.getCurrentHP() <= 0) {
                    player.setCurrentHP(player.getMaxHP() / 2);
                    player.setCurrentMana(player.getMaxMana());
                }
                return;
            }
            break;
        }

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

    if (slot_remaining <= 0) NextDay();

    // Update HP and Mana bars
    Volume    hp   = {player.getCurrentHP(), player.getMaxHP()};
    Volume    mana = {player.getCurrentMana(), player.getMaxMana()};
    Volume    exp  = {player.getEXP(), 100};
    const int atk  = player.getAttackPower();
    const int def  = player.getDefensePower();
    ui.setBarsVolume(hp, mana, exp);
    ui.popup_character_info.update(playerName, player.getLevel(), hp, mana, exp,
                                   atk, def);
    ui.popup_upgrade.update(player.getStatePoint(), hp, mana, atk, def);
    ui.setLevel(player.getLevel());
    ui.setDays(day);

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

// Function to render the game elements on the window
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

// Main game loop that runs the game
void Game::run() {
    story.introduction(window);
    while (window.isOpen() && day <= 40) {
        processEvents();
        update();
        render();
    }
    story.showEnding(window);
    story.showCredits(window);
}