#pragma once

class Entity; // Forward declaration of the Entity class

#include <string>

class Skill {
    private:
        std::string _name;       // The name of the skill
        int         _manaCost;   // The mana cost of the skill
        int         _cooldown;   // The cooldown time of the skill
        int         _baseDamage; // The base damage of the skill
        float _ratioPlayerAtk;   // The ratio of the player's attack power to the
                                 // skill's damage
        int _pierceRate; // The rate at which the skill pierces the target's
                         // defense
    public:
        Skill() = default; // Default constructor

        Skill(std::string name, int manaCost, int cooldown, int baseDamage,
              float ratioPlayerAtk, int pierceRate)
            : _name(name), _manaCost(manaCost), _cooldown(cooldown),
              _baseDamage(baseDamage), _ratioPlayerAtk(ratioPlayerAtk),
              _pierceRate(pierceRate) {}

        Skill(std::string name)
            : _name(name), _manaCost(0), _cooldown(0), _baseDamage(0),
              _ratioPlayerAtk(0.0f), _pierceRate(0) {}

        ~Skill() = default;


        std::string getName() const { return _name; }

        int getManaCost() const { return _manaCost; }

        int getCooldown() const { return _cooldown; }

        int getBaseDamage() const { return _baseDamage; }

        float getRatioPlayerAtk() const { return _ratioPlayerAtk; }

        int getPierceRate() const { return _pierceRate; }

        int calculateDamage(Entity *user, Entity *target);
};

#include "Entity.hpp"