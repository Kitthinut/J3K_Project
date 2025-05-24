#include "Entity/Entity.hpp"

// Method to cast a skill on a target entity
void Entity::attack(Entity *target) {
    // damage dealt by the normal attack
    target->setCurrentHP(target->getCurrentHP() -
                         this->_attackPower); // Apply the damage to the target
}

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
        target->setCurrentHP(target->getCurrentHP() - damage);
    } else {
        std::cout << "Not enough mana to cast the skill!" << std::endl;
    }
}