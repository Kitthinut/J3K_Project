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
        Entity() {
            for (int i = 0; i < 5; ++i)
                _skills[i] = nullptr;
        }

        Entity(std::string name, int maxHP, int currentHP, int maxMana,
               int currentMana, int attackPower, int defensePower, int level)
            : _name(name), _maxHP(maxHP), _currentHP(currentHP), _maxMana(maxMana),
              _currentMana(currentMana), _attackPower(attackPower),
              _defensePower(defensePower), _level(level) {
            for (int i = 0; i < 5; ++i)
                _skills[i] = nullptr;
        }

        Entity(std::string name, int maxHP, int maxMana, int attackPower,
               int defensePower, int level)
            : Entity(name, maxHP, maxHP, maxMana, maxMana, attackPower,
                     defensePower, level) {}

        ~Entity() {
            for (int i = 0; i < 5; ++i)
                if (_skills[i]) delete _skills[i];
        }

        // Getters for the entity attributes
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

        // Increase max HP by a specified amount
        void increaseMaxHP(int amount) { _maxHP += amount; }

        // Increase max mana by a specified amount
        void increaseMaxMana(int amount) { _maxMana += amount; }

        // Increase attack power by a specified amount
        void increaseAttackPower(int amount) { _attackPower += amount; }

        // Increase defense power by a specified amount
        void increaseDefensePower(int amount) { _defensePower += amount; }

        // Increase current HP by a specified amount
        void increaseCurrentHP(int amount) {
            _currentHP += amount;
            _currentHP  = _currentHP > _maxHP ? _maxHP : _currentHP;
        }

        // Increase current mana by a specified amount
        void increaseCurrentMana(int amount) {
            _currentMana += amount;
            _currentMana  = _currentMana > _maxMana ? _maxMana : _currentMana;
        }

        void setCurrentHP(int currentHP) { _currentHP = currentHP; }

        void setCurrentMana(int currentMana) { _currentMana = currentMana; }

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
};

#include "Skill.hpp"