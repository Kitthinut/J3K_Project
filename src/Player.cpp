#include "Player.hpp"

#include <iostream>

Player::Player(sf::Vector2f position) {
    // Load player sprite
    if (!texture.loadFromFile("assets/characters/Spritesheet.png")) {
        std::cerr << "Failed to load sprite sheet!" << std::endl;
    }
    sprite.setScale(3.0f, 3.0f);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, PLAYER_FRAME, PLAYER_FRAME));
    setPosition(position);
}

void Player::setPosition(sf::Vector2f position) {
    this->position = position;
    sprite.setPosition(position);
}

const sf::FloatRect Player::getBounds() {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    int           width  = bounds.width / 6;
    int           height = bounds.height / 6;

    bounds.left   += width * 2;
    bounds.top    += bounds.height - height;
    bounds.width   = width * 2;
    bounds.height  = height;
    return bounds;
}

void Player::movement() {
    // Movement logic (updating position and direction)
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= PLAYER_SPEED * dt;
        animation(Up);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += PLAYER_SPEED * dt;
        animation(Down);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= PLAYER_SPEED * dt;
        animation(Left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += PLAYER_SPEED * dt;
        animation(Right);
    }

    next_bounds       = getBounds();
    next_bounds.left += movement.x;
    next_bounds.top  += movement.y;
}

void Player::animation(Direction direction) {
    // Update animation frame if the player is moving
    animation_timer += dt;
    if (animation_timer < ANIMATION_SPEED) return;
    animation_timer = 0.0f;
    current_frame   = (current_frame + 1) % 4; // Loop through 4 frames
    sprite.setTextureRect(sf::IntRect(current_frame * PLAYER_FRAME,
                                      direction * PLAYER_FRAME, PLAYER_FRAME,
                                      PLAYER_FRAME));
}

Room Player::warpTo() { return collision.hitWarps(getBounds()); }

void Player::update() {
    sf::Time deltaTime = clock.restart();
    dt                 = deltaTime.asSeconds();

    if (!moveable) return;
    movement();

    bool hit_obstacles = collision.hitObstacles(getNextBounds());
    if (!hit_obstacles) {
        sf::FloatRect bounds  = getBounds();
        position.x           += next_bounds.left - bounds.left;
        position.y           += next_bounds.top - bounds.top;
        sprite.setPosition(position);    }
}

void Player::draw(sf::RenderWindow &window) {
    interact = collision.onInteractables(getBounds());
    collision.draw(window, interact, false);
    window.draw(sprite);
}