#pragma once
#include <Skill.hpp>
#include <iostream> // For std::cout and std::endl

#ifndef ENTITY_H
#define ENTITY_H

class Skill;
class Entity{
    private: 
        std::string _name; // The name of the entity
        int _maxHP;
        int _currentHP;
        int _maxMana;
        int _currentMana;
        int _attackPower;
        int _defensePower;
        int _level;

        
        Skill *_skills[5]; // Array of skills available to the entity
        // Skill *_normalAttack = &normalAttack; // The normal attack skill of the entity
        Skill _normalAttack(); // The normal attack skill of the entity
    public : 
        Entity() = default; // Default constructor
        Entity(std::string name, int maxHP, int currentHP, int maxMana, int currentMana, int attackPower, int defensePower, int level) : 
            _name(name), _maxHP(maxHP), _currentHP(currentHP), _maxMana(maxMana), _currentMana(currentMana), 
            _attackPower(attackPower), _defensePower(defensePower), _level(level){}
        Entity(std::string name, int maxHP, int maxMana, int attackPower, int defensePower, int level) : 
            Entity(name, maxHP, maxHP, maxMana, maxMana, attackPower, defensePower, level){}
        ~Entity() = default;
        // Getters for the entity attributes
        int getMaxHP() const { return _maxHP; }
        int getCurrentHP() const { return _currentHP; }
        int getMaxMana() const { return _maxMana; }
        int getCurrentMana() const { return _currentMana; }
        int getAttackPower() const { return _attackPower; }
        int getDefensePower() const { return _defensePower; }
        int getLevel() const { return _level; }
        Skill* getSkill(int index) const { return _skills[index]; } // Get a skill at a specific index

        // Setters for the entity attributes
        void setCurrentHP(int currentHP) { _currentHP = currentHP; }
        void decreaseCurrentHP(int amount) { _currentHP -= amount; } // Decrease current HP by a specified amount
        void setCurrentMana(int currentMana) { _currentMana = currentMana; }
        void decreaseCurrentMana(int amount) { _currentMana -= amount; } // Decrease current mana by a specified amount
        void setSkill(int index, Skill *skill) { _skills[index] = skill; } // Set a skill at a specific index    

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
#endif // ENTITY_H