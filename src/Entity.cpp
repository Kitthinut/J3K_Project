#pragma once
#include "Skill.hpp"
#include "Entity.hpp"

// Method to cast a skill on a target entity
void Entity :: attack(Entity *target) {
    int damage = _normalAttack->calculateDamage(this, target); // Calculate the damage dealt by the normal attack
    target->setCurrentHP(target->getCurrentHP() - damage); // Apply the damage to the target
}
void Entity :: castSkill(int skillIndex, Entity *target) {
    if (skillIndex < 0 || skillIndex >= 5 ) {
        std::cout << _name << "Invalid skill index!" << std::endl;
        return;
    }else if (_skills[skillIndex] == nullptr) {
        std::cout << "Skill not available!" << std::endl;
        return;
    }
    if (_currentMana >= _skills[skillIndex]->getManaCost()) {
        std::cout << _name << " casting \"" << _skills[skillIndex]->getName() << "\" to " << target->getName() <<  std::endl;
        _currentMana -= _skills[skillIndex]->getManaCost(); // Deduct the mana cost of the skill
        int damage = _skills[skillIndex]->calculateDamage(this, target); // Calculate the damage dealt by the skill
        target->setCurrentHP(target->getCurrentHP() - damage); // Apply the damage to the target
    } else {
        std::cout << _name << " not enough mana to cast \"" << _skills[skillIndex]->getName() << "\"!" << std::endl;
    }
}