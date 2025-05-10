#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

struct PlayerClass {
    std::string role;
    std::string weapon;
    std::string skill;
    std::string item;
    int hp = 100;
    int mana = 50;
    int attack = 10;
    int defense = 5;
    
    PlayerClass(std::string r = "Knight", std::string w = "Sword", std::string s = "Slash", std::string i = "Potion")
        : role(r), weapon(w), skill(s), item(i) {}

    void upgradeStats(int attackBoost, int hpBoost) {
        attack += attackBoost;
        hp += hpBoost;
    }
};

struct Monster {
    std::string name;
    int hp;
    int attack;
    int defense;
    char headIcon;
    
    Monster(std::string n, int h, int a, int d)
        : name(n), hp(h), attack(a), defense(d) {}
    
    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
    }
    
    bool isAlive() {
        return hp > 0;
    }
};
#endif
