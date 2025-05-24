#pragma once

#include "Entity.hpp"
#include "Enum/Direction.hpp"
#include "Game/Collision.hpp"

#include <SFML/Graphics.hpp>

#define PLAYER_FRAME    64
#define PLAYER_SPEED    200.0f // Speed of the player in pixels per second
#define ANIMATION_SPEED 0.1

// class Player : public Entity {
class Player: public Entity {
    private:
        Collision     _collision;
        sf::Vector2f  _position;
        sf::FloatRect _next_bounds;

        sf::Clock    _clock;
        sf::Sprite   _sprite;
        sf::Texture  _texture;
        float        _dt              = 0;
        int          _current_frame   = 0;
        float        _animation_timer = 0.0f;
        bool         _moveable        = true;
        sf::Keyboard _last_key;

        int _exp          = 0;   // The experience points of the player
        int _exp_to_level = 100; // The experience points required to level up
        int _state_point  = 5;   // The number of skill points the player has

        Interact _interact = Empty;

        void movement();

        void animation(const Direction direction);

    public:
        Player(sf::Vector2f position, std::string name, int maxHP, int currentHP,
               int maxMana, int currentMana, int attackPower, int defensePower,
               int level);
        ;

        int getEXP() const { return _exp; }

        int getStatePoint() const { return _state_point; }

        void setMoveable(bool moveable) { _moveable = moveable; }

        void setPosition(sf::Vector2f position);

        void setEXP(int exp) { _exp = exp; }

        void increaseStatePoint(int amount) { _state_point += amount; }

        void increaseEXP(int amount);

        const sf::FloatRect getBounds();

        const sf::FloatRect &getNextBounds() { return _next_bounds; }

        Collision &getCollision() { return _collision; }

        Interact GetInteract() { return _interact; }

        Room warpTo();

        void update();

        void draw(sf::RenderWindow &window);
};