#pragma once
#include <entity.h>

class Skill{
    private:
        int _manaCost; // The mana cost of the skill
        int _cooldown; // The cooldown time of the skill 
        int _baseDamage; // The base damage of the skill
        float _ratioPlayerAtk; // The ratio of the player's attack power to the skill's damage
        int _pierceRate; // The rate at which the skill pierces the target's defense
    public:
        Skill(int manaCost, int cooldown, int baseDamage, float ratioPlayerAtk, int pierceRate) : 
            _manaCost(manaCost), _cooldown(cooldown), _baseDamage(baseDamage), 
            _ratioPlayerAtk(ratioPlayerAtk), _pierceRate(pierceRate) {}
        ~Skill() = default;
        
        // Getters for the skill attributes
        int getManaCost() const { return _manaCost; }
        int getCooldown() const { return _cooldown; }
        int getBaseDamage() const { return _baseDamage; }
        float getRatioPlayerAtk() const { return _ratioPlayerAtk; }
        int getPierceRate() const { return _pierceRate; }

        int calculateDamage(Entity *user, Entity *target) const {
            // Calculate the damage dealt by the skill
            int defenseReduction = target->getDefensePower() - _pierceRate; // Calculate the defense reduction
            int damage = _baseDamage + (user->getAttackPower() * _ratioPlayerAtk) - defenseReduction; // Calculate the total damage

            return damage > 0 ? damage : 0; // Ensure damage is not negative
        }

};

Skill normalAttack(0, 0, 5, 1, 0); // The normal attack skill of the entity
Skill fireball(10, 5, 20, 1.25, 5); // The fireball skill of the entity
Skill iceSpike(15, 7, 25, 1.5, 10); // The ice spike skill of the entity
Skill lightningBolt(20, 10, 30, 2, 15); // The lightning bolt skill of the entity
Skill fireStorm(25, 15, 20, 3, 20); // The fire storm skill of the entity
Skill thunderStorm(30, 20, 25, 4, 25); // The thunder storm skill of the entity
Skill meteor(35, 25, 30, 5, 30); // The meteor skill of the entity

Skill LEDExplosion(10, 2, 30, 0.5, 0); // The led explosion skill of the entity
Skill capacitorExplosion(45, 35, 40, 7, 40); // The capacitor explosion skill of the entity
Skill resistorExplosion(50, 40, 50, 8, 45); // The resistor explosion skill of the entity
Skill diodeExplosion(55, 45, 60, 9, 50); // The diode explosion skill of the entity
Skill transistorExplosion(60, 50, 70, 10, 55); // The transistor explosion skill of the entity
Skill microcontrollerExplosion(65, 55, 80, 11, 60); // The microcontroller explosion skill of the entity

Skill iDontBuyIt(0, 0, 0, 0, 0); // The iDontButIt skill of the entity