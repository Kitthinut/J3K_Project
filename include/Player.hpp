#pragma once

#include "Collision.hpp"
#include "Enum/Direction.hpp"

#include <SFML/Graphics.hpp>

#define PLAYER_FRAME    64
#define PLAYER_SPEED    200
#define ANIMATION_SPEED 0.1

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

        Interact interact = Empty;

        void movement();

        void animation(Direction direction);

    public:
        Player(sf::Vector2f position);

        void setPosition(sf::Vector2f position);

        const sf::FloatRect getBounds();

        const sf::FloatRect &getNextBounds() { return next_bounds; }

        Collision &getCollision() { return collision; }

        Interact GetInteract() { return interact; }

        Room warpTo();

        void update();

        void draw(sf::RenderWindow &window);
};