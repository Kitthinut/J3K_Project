#include "Entity/Entity.hpp"

Entity::Entity(std::string name, int maxHP, int currentHP, int maxMana,
               int currentMana, int attackPower, int defensePower, int level)
    : _name(name), _maxHP(maxHP), _currentHP(currentHP), _maxMana(maxMana),
      _currentMana(currentMana), _attackPower(attackPower),
      _defensePower(defensePower), _level(level) {
    for (int i = 0; i < 5; ++i)
        _skills[i] = nullptr;
}

Entity::Entity(std::string name, int maxHP, int maxMana, int attackPower,
               int defensePower, int level)
    : Entity(name, maxHP, maxHP, maxMana, maxMana, attackPower, defensePower,
             level) {}

// Method to cast a skill on a target entity
void Entity::attack(Entity *target) {
    target->increaseCurrentHP(-_attackPower); // Apply the damage to the target
}

// Method to set a skill at a specific index
void Entity::castSkill(int skillIndex, Entity *target) {
    if (skillIndex < 0 || skillIndex >= 5) {
        std::cout << "Invalid skill index!" << std::endl;
        return;
    } else if (_skills[skillIndex] == nullptr) {
        std::cout << "Skill not available!" << std::endl;
        return;
    }
    if (_currentMana >= _skills[skillIndex]->getManaCost()) {
        std::cout << "Casting skill: " << _skills[skillIndex]->getName()
                  << std::endl;

        // Deduct the mana cost of the skill
        _currentMana -= _skills[skillIndex]->getManaCost();
        // Calculate the damage dealt by the skill
        int damage = _skills[skillIndex]->calculateDamage(this, target);
        // Apply the damage to the target
        target->increaseCurrentHP(-damage);
    } else {
        std::cout << "Not enough mana to cast the skill!" << std::endl;
    }
}

// Increase max HP by a specified amount
void Entity::increaseMaxHP(int amount) {
    _maxHP     += amount;
    _currentHP  = _currentHP > _maxHP ? _maxHP : _currentHP < 0 ? 0 : _currentHP;
}

// Increase max mana by a specified amount
void Entity::increaseMaxMana(int amount) {
    _maxMana     += amount;
    _currentMana  = _currentMana > _maxMana ? _maxMana
                    : _currentMana < 0      ? 0
                                            : _currentMana;
}

// Function to increase HP by a specified amount
void Entity::increaseCurrentHP(int amount) {
    _currentHP += amount;
    _currentHP  = _currentHP > _maxHP ? _maxHP : _currentHP < 0 ? 0 : _currentHP;
}

// Function to increase max Mana by a specified amount
void Entity::increaseCurrentMana(int amount) {
    _currentMana += amount;
    _currentMana  = _currentMana > _maxMana ? _maxMana
                    : _currentMana < 0      ? 0
                                            : _currentMana;
}