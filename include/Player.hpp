#pragma once

#include "Collision.hpp"
#include "Enum/Direction.hpp"

#include <SFML/Graphics.hpp>

// #include <Entity.hpp>

#define PLAYER_FRAME    64
#define PLAYER_SPEED    200
#define ANIMATION_SPEED 0.1

// class Player : public Entity {
class Player {
    private:
        Collision     collision;
        sf::Vector2f  position;
        sf::FloatRect next_bounds;

        sf::Clock   clock;
        sf::Sprite  sprite;
        sf::Texture texture;
        float       dt              = 0;
        int         current_frame   = 0;
        float       animation_timer = 0.0f;
        bool        moveable        = true;

        Interact interact = Empty;

        void movement();

        void animation(Direction direction);

        int _level = 1; // The level of the player
        int _EXPtoNextLevel; // The experience points required to reach the next level
        int _EXP = 0; // The experience points of the player
        int _gold; // The amount of gold the player has
        int _statePoint; // The number of skill points the player has

    public:
        Player(sf::Vector2f position);

        void setMoveable(bool moveable) { this->moveable = moveable; }

        void setPosition(sf::Vector2f position);

        const sf::FloatRect getBounds();

        const sf::FloatRect &getNextBounds() { return next_bounds; }

        Collision &getCollision() { return collision; }

        Interact GetInteract() { return interact; }

        Room warpTo();

        void update();

        void draw(sf::RenderWindow &window);
};