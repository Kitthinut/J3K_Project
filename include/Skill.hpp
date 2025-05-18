#pragma once
#include <string>
#include <Entity.hpp>


#ifndef SKILL_H
#define SKILL_H

class Entity;

class Skill{
    private:
        std::string _name; // The name of the skill
        int _manaCost; // The mana cost of the skill
        int _cooldown; // The cooldown time of the skill 
        int _baseDamage; // The base damage of the skill
        float _ratioPlayerAtk; // The ratio of the player's attack power to the skill's damage
        int _pierceRate; // The rate at which the skill pierces the target's defense
    public:
        Skill() = default; // Default constructor
        Skill(std::string name,int manaCost, int cooldown, int baseDamage, float ratioPlayerAtk, int pierceRate) : 
            _name(name), _manaCost(manaCost), _cooldown(cooldown), _baseDamage(baseDamage), 
            _ratioPlayerAtk(ratioPlayerAtk), _pierceRate(pierceRate) {}
        Skill(std::string name) : 
            _name(name), _manaCost(0), _cooldown(0), _baseDamage(0), 
            _ratioPlayerAtk(0.0f), _pierceRate(0) {}
        ~Skill() = default;
        
        // Getters for the skill attributes
        void printInfo() const {
            std::cout << "Skill Name\t: " << _name << std::endl;
            std::cout << "Mana Cost\t: " << _manaCost << std::endl;
            std::cout << "Cooldown\t: " << _cooldown << std::endl;
            std::cout << "Base Damage\t: " << _baseDamage << std::endl;
            std::cout << "Ratio Player Attack\t: " << _ratioPlayerAtk << std::endl;
            std::cout << "Pierce Rate\t: " << _pierceRate << std::endl;
        }
        std::string getName() const { return _name; }
        int getManaCost() const { return _manaCost; }
        int getCooldown() const { return _cooldown; }
        int getBaseDamage() const { return _baseDamage; }
        float getRatioPlayerAtk() const { return _ratioPlayerAtk; }
        int getPierceRate() const { return _pierceRate; }

        int calculateDamage(Entity *user, Entity *target);

};

// Define some example skills with proper initialization
Skill normalAttack("Normal Attack", 0, 0, 5, 1.0f, 0);
Skill fireball("Fireball", 10, 5, 20, 1.25f, 5); // The fireball skill of the entity
Skill iceSpike("Ice Spike", 15, 7, 25, 1.5f, 10); // The ice spike skill of the entity
Skill lightningBolt("Lightning Bolt", 20, 10, 30, 2.0f, 15); // The lightning bolt skill of the entity
Skill fireStorm("Fire Storm", 25, 15, 20, 3.0f, 20); // The fire storm skill of the entity
Skill thunderStorm("Thunder Storm", 30, 20, 25, 4.0f, 25); // The thunder storm skill of the entity
Skill meteor("Meteor", 35, 25, 30, 5.0f, 30); // The meteor skill of the entity

Skill ledExplosion("LED Explosion", 10, 2, 30, 0.5f, 0); // The LED explosion skill of the entity
Skill capacitorExplosion("Capacitor Explosion", 45, 35, 40, 7.0f, 40); // The capacitor explosion skill of the entity
Skill resistorExplosion("Resistor Explosion", 50, 40, 50, 8.0f, 45); // The resistor explosion skill of the entity
Skill diodeExplosion("Diode Explosion", 55, 45, 60, 9.0f, 50); // The diode explosion skill of the entity
Skill transistorExplosion("Transistor Explosion", 60, 50, 70, 10.0f, 55); // The transistor explosion skill of the entity
Skill microcontrollerExplosion("Microcontroller Explosion", 65, 55, 80, 11.0f, 60); // The microcontroller explosion skill of the entity
Skill hotLine("Hot Line", 70, 60, 90, 12.0f, 65); // The hot line skill of the entity

Skill iDontBuyIt("I Don't Buy It", 0, 0, 0, 0.0f, 0); // The iDontBuyIt skill of the entity

// Dummy for testing system. ข้าพเจ้าไม่ทราบว่าจะ รวมโค้ดยังไงดี
namespace SkillDB {
    const Skill FireBall("Fire Ball");
    const Skill IceSpike("Ice Spike");
    const Skill Heal("Heal");
    const Skill Thunder("Thunder");
    const Skill WindSlash("Wind Slash");
}
#endif // SKILL_H