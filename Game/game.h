#ifndef GAME_H
#define GAME_H

#include "screen.h"
#include "entity.h"
#include <iostream>
#include <vector>
#include <cstdlib>

class Game
{
private:
    Screen screen;
    PlayerClass player;
    bool running = true;
    int level = 1;

    void renderMonster(Monster &monster)
    {
        screen.print("Monster: " + monster.name, false);
        screen.print("HP: " + std::to_string(monster.hp) + "  Attack: " + std::to_string(monster.attack) +
                         "  Defense: " + std::to_string(monster.defense),
                     false);
    }

    void combat(Monster &monster) {
        bool playerTurn = true;
    
        while (player.hp > 0 && monster.isAlive()) {
            renderCombatScene(player.role, player.hp, monster.name, monster.hp);
    
            if (playerTurn) {
                screen.print("Player's turn.\n", false);
                screen.print("HP: " + std::to_string(player.hp) + "  Mana: " + std::to_string(player.mana) + "\n", false);
                screen.print("Choose action:\n", false);
                screen.print("(1) Normal Attack\n", false);
                screen.print("(2) Skill\n", false);
    
                int choice;
                std::cin >> choice;
                std::cin.ignore();
    
                int damage = 0;
                switch (choice) {
                    case 1: 
                        damage = std::max(0, player.attack - monster.defense);
                        monster.takeDamage(damage);
                        screen.print("You dealt " + std::to_string(damage) + " damage!\n", false);
                        break;
                    case 2: 
                        if (player.mana >= 10) {
                            player.mana -= 10;
                            damage = player.attack * 2;
                            monster.takeDamage(damage);
                            screen.print("Skill used! You dealt " + std::to_string(damage) + " damage!\n", false);
                        } else {
                            screen.print("Not enough mana for skill!\n", false);
                        }
                        break;
                    default: 
                        screen.print("Invalid choice. Try again.\n", false);
                        continue;
                }
    
                renderCombatScene(player.role, player.hp, monster.name, monster.hp);
                playerTurn = false;
    
            } else {
                int monsterDamage = std::max(0, monster.attack - player.defense);
                player.hp -= monsterDamage;
    
                screen.print("Monster " + monster.name + " attacked and dealt " + std::to_string(monsterDamage) + " damage!\n", false);
    
                if (!monster.isAlive()) {
                    screen.print("Monster " + monster.name + " got defeated!\n", false);
                    renderCombatScene(player.role, player.hp, monster.name, monster.hp);
                    break;
                }
    
                renderCombatScene(player.role, player.hp, monster.name, monster.hp);
                playerTurn = true;
            }
    
            screen.render(true);
            std::cin.get();
        }
    
        if (player.hp <= 0) {
            screen.print("You have been defeated! Game Over!\n", false);
        }
    }

    void renderCombatScene(const std::string &playerName, int playerHP, const std::string &enemyName, int enemyHP)
    {
        screen.clear();
        screen.rawPrint(R"(
    ╔═════════════════════════════════════════════════════════════╗
    ║                        ⚔ COMBAT START ⚔                    ║
    ╚═════════════════════════════════════════════════════════════╝
    )");

        screen.rawPrint("\n");

        screen.rawPrint(" " + playerName + " (HP: " + std::to_string(playerHP) + ")               vs               " + enemyName + " (HP: " + std::to_string(enemyHP) + ")\n");

        screen.rawPrint(R"(
         ███████████                                 ███████████
         ███████████                                 ███████████
         ██       ██        BATTLEFIELD              ██       ██
         ██       ██          [ARENA]                ██       ██
         ██       ██                                 ██       ██
         ███████████                                 ███████████
    )");

        screen.rawPrint(R"(
    ────────────────────────────────────────────────────────────────────
      [1] Attack    [2] Defend    [3] Use Item    [4] Run
    ────────────────────────────────────────────────────────────────────
    )");

        screen.render(true);
    }
    

    void levelUp()
    {
        screen.clear();
        screen.render();
        std::cout << "Level " << level << " Complete!" << std::endl;
        std::cout << "Select a card to upgrade your stats:" << std::endl;
        std::cout << "[1] +5 Attack" << std::endl;
        std::cout << "[2] +10 HP" << std::endl;
        std::cout << "[3] +5 Attack, +5 HP" << std::endl;

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1)
        {
            player.upgradeStats(5, 0);
        }
        else if (choice == 2)
        {
            player.upgradeStats(0, 10);
        }
        else if (choice == 3)
        {
            player.upgradeStats(5, 5);
        }
        level++;
    }

    void dungeon()
    {
        std::vector<Monster> monsters = {
            Monster("Goblin", 10, 5, 3),
            Monster("Orc", 10, 7, 4),
            Monster("Troll", 15, 10, 5),
            Monster("Boss", 30, 15, 8)};

        for (int i = 0; i < monsters.size(); i++)
        {
            combat(monsters[i]);
            if (player.hp <= 0)
            {
                std::cout << "Game Over!" << std::endl;
                return;
            }
            if (i == monsters.size() - 1)
            {
                levelUp();
            }
        }
    }

    void safeRoom()
    {
        bool inSafeRoom = true;
        while (inSafeRoom)
        {
            screen.clear();
            screen.drawBox("Lobby || Safe Zone", {"Talk to your co-workers or rest or fight monsters.",
                                                  "[1] Enter Dungeon",
                                                  "[2] Change Hero",
                                                  "[3] Exit to Menu"});
            screen.render();
            screen.print("Your choice: ", false);

            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
            case 1:
                enterDungeon();
                break;
            case 2:
                chooseClass();
                return;
            case 3:
                inSafeRoom = false;
                break;
            default:
                break;
            }
        }
    }

    void enterDungeon()
    {
        renderDungeon();
        std::cin.get();
        dungeon();
    }

    void renderDungeon()
    {
        screen.clear();
        screen.drawBox("Dungeon", {
                                      "████████████████████████████████████████████████████████████████████████████",
                                      "█      Welcome to the Dungeon!                           █",
                                      "█   /\\                                                  █",
                                      "█  /  \\  Get a new buff after 1 stages!                 █",
                                      "█  |  |                                                   █",
                                      "█  \\  /  When the game is over, the remaining gold coins  █",
                                      "█   \\/   will be converted to gems                       █",
                                      "█                                                         █",
                                      "█  Beware of the monsters that roam here.                █",
                                      "█                                                       █",
                                      "████████████████████████████████████████████████████████████████████████████",
                                  });
        screen.render();
        screen.print("Press Enter to enter the dungeon...", false);
    }

    void chooseClass()
    {
        screen.clear();
        screen.drawBox("Select a Hero", {"[1] Knight  - \"You go, I'm taking a break\"",
                                         "[2] Paladin  - \"I like this TV show \"",
                                         "[3] Engineer   - \"Fixing my turret\""});
        screen.render();
        screen.print("Enter choice: ", false);

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
            player = PlayerClass("Knight", "Sword", "Slash", "Potion");
            break;
        case 2:
            player = PlayerClass("Wizard", "Wand", "Fireball", "Potion");
            break;
        case 3:
            player = PlayerClass("Engineer", "Vernier Caliper", "Backstab", "Potion");
            break;
        default:
            player = PlayerClass();
            break;
        }

        safeRoom();
    }

    void mainMenu()
    {
        while (running)
        {
            screen.clear();
            screen.drawBox("Main Menu", {"[1] Start Game",
                                         "[2] About",
                                         "[3] Exit"});
            screen.render();
            screen.print("Choose an option: ", false);

            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
            case 1:
                chooseClass();
                break;
            case 2:
                showAbout();
                break;
            case 3:
                running = false;
                break;
            default:
                break;
            }
        }
    }

    void showAbout()
    {
        screen.clear();
        screen.drawBox("About", {"Soul J3K Project",
                                 "Some game data are stored locally, and",
                                 "cannot be restored if you delete the game."});
        screen.render();
        screen.print("Press Enter to go back...");
        std::cin.get();
    }

public:
    void start()
    {
        screen.clear();
        titleScreen();
        mainMenu();
    }

    void titleScreen()
    {
        screen.clear();
        screen.rawPrint(R"(
       _ ____  _  __   _____  ____  _    _ _      _   _ _____ _____ _    _ _______ 
      | |___ \| |/ /  / ____|/ __ \| |  | | |    | \ | |_   _/ ____| |  | |__   __|
      | | __) | ' /  | (___ | |  | | |  | | |    |  \| | | || |  __| |__| |  | |   
  _   | ||__ <|  <    \___ \| |  | | |  | | |    | . ` | | || | |_ |  __  |  | |   
 | |__| |___) | . \   ____) | |__| | |__| | |____| |\  |_| || |__| | |  | |  | |   
  \____/|____/|_|\_\ |_____/ \____/ \____/|______|_| \_|_____\_____|_|  |_|  |_|   
                                                                                 

              S O U L N I G H T

           PRESS [ENTER] TO START)");
        screen.render(true);
        std::cin.get();
    }
};

#endif
