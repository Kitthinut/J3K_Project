#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>

class Character {
    protected:
        std::string name;
        int         maxHP;
        int         currentHP;
        int         attackPower;

    public:
        // Build a character with name, max HP, and attack power
        Character(const std::string &name, int hp, int attack)
            : name(name), maxHP(hp), currentHP(hp), attackPower(attack) {}

        virtual ~Character() {}

        std::string getName() const { return name; }

        int getHP() const { return currentHP; }

        int getAttackPower() const { return attackPower; }

        // Add setName function here to allow name changes
        void setName(const std::string &newName) { name = newName; }

        void takeDamage(int dmg) {
            currentHP -= dmg;
            if (currentHP < 0) currentHP = 0;
        }

        bool isAlive() const { return currentHP > 0; }

        virtual void displayStats() const = 0;
};

// Build a player class that inherits from Character ; name, max HP, attack power,
// level, and experience
class PlayerClass: public Character {
    private:
        int level;
        int experience;
        int upgradePoints; // Points available for upgrades

    public:
        PlayerClass(const std::string &name, int hp, int attack)
            : Character(name, hp, attack), level(1), experience(0),
              upgradePoints(5) {} // Default points set to 5

        // Function to gain experience and potentially level up
        void gainExperience(int exp) {
            experience += exp;
            if (experience >= 100) {
                level++;
                experience  -= 100;
                maxHP       += 10;
                currentHP    = maxHP;
                attackPower += 2;
            }
        }

        // Function to use upgrade points
        void upgrade() {
            if (upgradePoints > 0) {
                int choice;
                std::cout << "You have " << upgradePoints << " points to upgrade.\n";
                std::cout << "1. Increase HP (+10)\n2. Increase Attack Power "
                             "(+2)\nChoose an upgrade: ";
                std::cin >> choice;

                if (choice == 1) {
                    maxHP     += 10;
                    currentHP  = maxHP; // Reset HP to max after upgrade
                    upgradePoints--;    // Reduce points after upgrade
                    std::cout << "HP increased by 10!" << std::endl;
                } else if (choice == 2) {
                    attackPower += 2;
                    upgradePoints--; // Reduce points after upgrade
                    std::cout << "Attack Power increased by 2!" << std::endl;
                } else {
                    std::cout << "Invalid choice. No upgrade made." << std::endl;
                }
            } else {
                std::cout << "No upgrade points remaining." << std::endl;
            }
        }

        // Function to display stats with upgrades
        void displayStats() const override {
            std::cout << "Player: " << name << " | HP: " << currentHP << "/" << maxHP
                      << " | ATK: " << attackPower << " | LVL: " << level
                      << " | EXP: " << experience
                      << "/100 | Upgrade Points: " << upgradePoints << std::endl;
        }

        // Function to add upgrade points at the start of a new round or event
        void addUpgradePoints() {
            int additionalPoints = rand() % 6 + 5; // Random points between 5-10
            upgradePoints        = additionalPoints;
            std::cout << "You have gained " << additionalPoints << " upgrade points!"
                      << std::endl;
        }
};

// Build a monster class that inherits from Character ; name, max HP, and attack
// power
class Monster: public Character {
    public:
        Monster(const std::string &name, int hp, int attack)
            : Character(name, hp, attack) {}

        void displayStats() const override {
            std::cout << "Monster: " << name << " | HP: " << currentHP << "/"
                      << maxHP << " | ATK: " << attackPower << std::endl;
        }
};

#endif
