#pragma once

#include "Collision.hpp"
#include "Enum/Direction.hpp"

#include <SFML/Graphics.hpp>

#include <Entity.hpp>
#include <Inventory.hpp>

#define PLAYER_FRAME    64
#define PLAYER_SPEED    200
#define ANIMATION_SPEED 0.1

// class Player : public Entity {
class Player : public Entity {
    private:
        Collision     _collision;
        sf::Vector2f  _position;
        sf::FloatRect _next_bounds;

        sf::Clock   _clock;
        sf::Sprite  _sprite;
        sf::Texture _texture;
        float       _dt              = 0;
        int         _current_frame   = 0;
        float       _animation_timer = 0.0f;
        bool        _moveable        = true;

        Interact interact = Empty;

        void movement();

        void animation(Direction direction);

        int _level = 1; // The level of the player
        int _EXPtoNextLevel; // The experience points required to reach the next level
        int _EXP = 0; // The experience points of the player
        int _gold; // The amount of gold the player has
        int _statePoint; // The number of skill points the player has

        Inventory _inventory; // The inventory of the player

    public:
        Player(sf::Vector2f position, std::string name, int maxHP, int currentHP, int maxMana, int currentMana, int attackPower, int defensePower, int level);;

        int getEXP() const { return _EXP; }
        int getEXPtoNextLevel() const { return _EXPtoNextLevel; }
        
        void setMoveable(bool moveable) { _moveable = moveable; }

        void setPosition(sf::Vector2f position);

        const sf::FloatRect getBounds();

        const sf::FloatRect &getNextBounds() { return _next_bounds; }

        Collision &getCollision() { return _collision; }

        Interact GetInteract() { return interact; }

        Room warpTo();

        void update();

        void draw(sf::RenderWindow &window);
};