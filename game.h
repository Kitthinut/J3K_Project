#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "render.h"
#include "character.h"

class Game {
private:
    Render renderer;     // Handles all rendering
    PlayerClass player;  // Player character
    Monster enemy;       // Enemy character

public:
    // Default constructor that initializes player and enemy
    Game() : player("Default Player", 100, 15), enemy("Goblin", 50, 10) {}

    // Initializes the game with title screen and input
    // This function manages the main menu loop, allowing the player to select an option (start game, show about, upgrade, or exit).
    void start() {
        int choice;
        do {
            renderer.renderTitleScreen();  // Render title screen
            std::cout << "Choose option (1-4): ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    play();  // Start the game
                    break;
                case 2:
                    renderer.renderAbout();  // Display about information
                    waitForEnter();
                    break;
                case 3:
                    upgrade();  // Start the upgrade process
                    break;
                case 4:
                    renderer.print("Exiting game...");  // Exit message
                    break;
                default:
                    renderer.print("Invalid choice.");  // Invalid option message
                    break;
            }
        } while (choice != 4);  // Exit the loop if the user selects option 4 (exit)
    }

private:
    // Starts the game and initializes characters
    // This function initializes the player and enemy characters and begins the combat loop.
    void play() {
        renderer.renderDungeonIntro();  // Render intro screen
        waitForEnter();  // Wait for user input

        std::string playerName;
        std::cout << "Enter your character's name: ";  
        std::cin >> playerName;

        player.setName(playerName);  // Set the player's name from input

        combat();  // Start the combat loop
    }

    // Executes the combat loop
    // This function simulates the combat between the player and the enemy, processing player and enemy actions.
    void combat() {
        srand(static_cast<unsigned int>(time(nullptr)));  // Seed random number generator

        while (player.isAlive() && enemy.isAlive()) {
            renderer.renderCombatScene(player.getName(), player.getHP(), enemy.getName(), enemy.getHP());  // Render combat scene

            std::cout << "\n1. Attack\n2. Defend\nChoose action: ";  // Display combat options
            int choice;
            std::cin >> choice;

            if (choice == 1) {
                int damage = rand() % 10 + 5;  // Random damage between 5 and 15
                enemy.takeDamage(damage);      // Apply damage to enemy
                renderer.print(player.getName() + " attacks " + enemy.getName() + " for " + std::to_string(damage) + " damage!");
            } else {
                renderer.print(player.getName() + " defends!");  // Player defends
            }

            // If the enemy is still alive, it counterattacks
            if (enemy.isAlive()) {
                int enemyDamage = rand() % 10 + 3;  // Random enemy damage between 3 and 12
                player.takeDamage(enemyDamage);     // Apply damage to player
                renderer.print(enemy.getName() + " attacks back for " + std::to_string(enemyDamage) + " damage!");
            }

            waitForEnter();  // Wait for player to continue
        }

        // After combat ends, display result
        renderer.clear();
        if (!player.isAlive()) {
            renderer.drawBox("Game Over", { player.getName() + " has fallen in battle." });
        } else {
            renderer.drawBox("Victory!", { enemy.getName() + " has been defeated." });
        }

        waitForEnter();  // Wait for player to continue
    }

    // Waits for user input to continue
    // This function pauses the game and waits for the player to press enter before continuing.
    void waitForEnter() {
        std::cout << WHITE_COLOR "\n(Press Enter to continue...)";
        std::cin.ignore();
        std::cin.get();
    }

    // Upgrade function to allow the player to enhance their stats
    void upgrade() {
        int upgradeChoice;
        do {
            renderer.renderUpgradeScreen();  // Render the upgrade screen with thematic style
            
            std::cout << "Choose an upgrade option: ";
            std::cin >> upgradeChoice;
    
            switch (upgradeChoice) {
                case 1:
                    player.gainExperience(10);  // Increase attack power
                    renderer.print("+10 Attack Power increased!");
                    waitForEnter();
                    break;
                case 2:
                    player.gainExperience(10);  // Increase HP
                    renderer.print("+10 HP increased!");
                    waitForEnter();
                    break;
                case 3:
                    return;  // Exit upgrade menu
                default:
                    renderer.print("Invalid choice.");
                    break;
            }
        } while (upgradeChoice != 3);  // Continue until the user chooses to return
    }
    
};

#endif
