#pragma once

class Skill; // Forward declaration of the Skill class

#include <iostream>

class Entity {
    private:
        std::string _name; // The name of the entity
        int         _maxHP;
        int         _currentHP;
        int         _maxMana;
        int         _currentMana;
        int         _attackPower;
        int         _defensePower;
        int         _level;

        Skill *_skills[5]; // Array of skills available to the entity

    public:
        Entity(std::string name, int maxHP, int currentHP, int maxMana,
               int currentMana, int attackPower, int defensePower, int level);

        Entity(std::string name, int maxHP, int maxMana, int attackPower,
               int defensePower, int level);

        ~Entity() {
            for (int i = 0; i < 5; ++i)
                if (_skills[i]) delete _skills[i];
        }

        // Getters for the entity attributes

        std::string getName() const { return _name; }

        int getMaxHP() const { return _maxHP; }

        int getCurrentHP() const { return _currentHP; }

        int getMaxMana() const { return _maxMana; }

        int getCurrentMana() const { return _currentMana; }

        int getAttackPower() const { return _attackPower; }

        int getDefensePower() const { return _defensePower; }

        int getLevel() const { return _level; }

        Skill *getSkill(int index) const {
            if (index < 0 || index >= 5) return nullptr;
            return _skills[index];
        }

        // Setters for the entity attributes

        void setName(const std::string &name) { _name = name; }

        void setCurrentHP(int currentHP) { _currentHP = currentHP; }

        void setCurrentMana(int currentMana) { _currentMana = currentMana; }

        void setAttackPower(int attackPower) { _attackPower = attackPower; }

        void setDefensePower(int defensePower) { _defensePower = defensePower; }

        void setLevel(int level) { _level = level; }

        // Set a skill at a specific index
        void setSkill(int index, Skill *skill) { _skills[index] = skill; }

        // Method to cast a skill on a target entity
        void attack(Entity *target);
        void castSkill(int skillIndex, Entity *target);

        void showInfo() const {
            std::cout << "Entity Info:" << std::endl;
            std::cout << "Max HP: " << _maxHP << std::endl;
            std::cout << "Current HP: " << _currentHP << std::endl;
            std::cout << "Max Mana: " << _maxMana << std::endl;
            std::cout << "Current Mana: " << _currentMana << std::endl;
            std::cout << "Attack Power: " << _attackPower << std::endl;
            std::cout << "Defense Power: " << _defensePower << std::endl;
            std::cout << "Level: " << _level << std::endl;
        }

        // Increase Level by 1
        void increaseLevel() { ++_level; }

        // Increase max HP by a specified amount
        void increaseMaxHP(int amount);

        // Increase max mana by a specified amount
        void increaseMaxMana(int amount);

        // Increase attack power by a specified amount
        void increaseAttackPower(int amount) { _attackPower += amount; }

        // Increase defense power by a specified amount
        void increaseDefensePower(int amount) { _defensePower += amount; }

        // Increase current HP by a specified amount
        void increaseCurrentHP(int amount);

        // Increase current mana by a specified amount
        void increaseCurrentMana(int amount);
};

#include "Skill.hpp"