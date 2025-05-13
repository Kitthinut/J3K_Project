#pragma once
#include "entity.h" // Assuming this header file contains the definition of the Entity class
#include "skill.h" // Assuming this header file contains the definition of the Skill class

#ifndef PLAYER_H
#define PLAYER_H
class Player : public Entity {
    private : 
        int _level = 1; // The level of the player
        int _EXPtoNextLevel; // The experience points required to reach the next level
        int _EXP = 0; // The experience points of the player
        int _gold; // The amount of gold the player has
        int _statePoint; // The number of skill points the player has
    public :
        Player(int maxHP, int currentHP, int maxMana, int currentMana, int attakPerPower, int defensePower, int level, int EXPtoNextLevel, int gold):
            Entity(maxHP, currentHP, maxMana, currentMana, attakPerPower, defensePower, level), 
            _level(level), _EXPtoNextLevel(EXPtoNextLevel), _gold(gold){}
        Player(int maxHP, int maxMana, int attakPerPower, int defensePower, int level, int EXPtoNextLevel, int gold):
            Player(maxHP, maxHP, maxMana, maxMana, attakPerPower, defensePower, level, EXPtoNextLevel, gold) {}
        ~Player() = default;
 };
#endif // PLAYER_H