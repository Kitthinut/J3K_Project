#include <Skill.hpp>

int Skill :: calculateDamage(Entity *user, Entity *target) {
            // Calculate the damage dealt by the skill
            int defenseReduction = target->getDefensePower() - _pierceRate; // Calculate the defense reduction
            int damage = _baseDamage + (user->getAttackPower() * _ratioPlayerAtk) - defenseReduction; // Calculate the total damage
            std::cout << "Damage dealt: " << damage << std::endl; // Print the damage dealt
            return damage > 0 ? damage : 0; // Ensure damage is not negative
        }