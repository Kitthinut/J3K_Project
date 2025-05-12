#pragma once
#include <skill.h>
#include <iostream> // For std::cout and std::endl
#include <vector> // For std::vector

class Entity{
    private: 
        int _maxHP;
        int _currentHP;
        int _maxMana;
        int _currentMana;
        int _attackPower;
        int _defensePower;
        int _level;

        Skill *normalAttack = normalAttack; // The normal attack skill of the entity
        Skill *skills[5]; // Array of skills available to the entity
    public : 
        Entity(int maxHP, int currentHP, int maxMana, int currentMana, int attackPower, int defensePower, int level) : 
            _maxHP(maxHP), _currentHP(currentHP), _maxMana(maxMana), _currentMana(currentMana), 
            _attackPower(attackPower), _defensePower(defensePower), _level(level) {}
        Entity(int maxHP, int maxMana, int attackPower, int defensePower, int level) : 
            Entity(maxHP, maxHP, maxMana, maxMana, attackPower, defensePower, level){}
        ~Entity() = default;
        // Getters for the entity attributes
        int getMaxHP() const { return _maxHP; }
        int getCurrentHP() const { return _currentHP; }
        int getMaxMana() const { return _maxMana; }
        int getCurrentMana() const { return _currentMana; }
        int getAttackPower() const { return _attackPower; }
        int getDefensePower() const { return _defensePower; }
        int getLevel() const { return _level; }
        Skill* getSkill(int index) const { return skills[index]; } // Get a skill at a specific index

        // Setters for the entity attributes
        void setCurrentHP(int currentHP) { _currentHP = currentHP; }
        void decreaseCurrentHP(int amount) { _currentHP -= amount; } // Decrease current HP by a specified amount
        void setCurrentMana(int currentMana) { _currentMana = currentMana; }
        void decreaseCurrentMana(int amount) { _currentMana -= amount; } // Decrease current mana by a specified amount
        void setSkill(int index, Skill *skill) { skills[index] = skill; } // Set a skill at a specific index
        

        // Method to cast a skill on a target entity
        void normalAttack(Entity *target) {
            int damage = normalAttack->calculateDamage(this, target); // Calculate the damage dealt by the normal attack
            target->setCurrentHP(target->getCurrentHP() - damage); // Apply the damage to the target
        }
        void castSkill(Skill *skill, Entity *target) {
            if (_currentMana >= skill->getManaCost()) {
                _currentMana -= skill->getManaCost(); // Deduct the mana cost of the skill
                int damage = skill->calculateDamage(this, target); // Calculate the damage dealt by the skill
                target->setCurrentHP(target->getCurrentHP() - damage); // Apply the damage to the target
            } else {
                std::cout << "Not enough mana to cast the skill!" << std::endl;
            }
        }
};