#include "Entity/Player.hpp"

#include <iostream>

// Constructor for Player class
Player::Player(sf::Vector2f position, std::string name, int maxHP, int currentHP,
               int maxMana, int currentMana, int attackPower, int defensePower,
               int level)
    : Entity(name, maxHP, currentHP, maxMana, currentMana, attackPower,
             defensePower, level) {
    // Load player sprite
    if (!_texture.loadFromFile("assets/character/Spritesheet.png")) {
        std::cerr << "Failed to load sprite sheet!" << std::endl;
    }
    _sprite.setScale(3.0f, 3.0f);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, PLAYER_FRAME, PLAYER_FRAME));
    setPosition(position);

    setSkill(0, new Skill("Normal Attact", 0, 0, 10, 1.0f, 0));
    setSkill(1, new Skill("Stone Crush", 15, 2, 18, 1.0f, 0));
    setSkill(2, new Skill("Tidal Wave", 20, 3, 25, 1.0f, 0));
    setSkill(3, new Skill("Gale Strike", 12, 1, 15, 1.0f, 0));
    setSkill(4, new Skill("Inferno Blast", 24, 4, 45, 1.0f, 0));
}

// Set the player's position and update the sprite's position
void Player::setPosition(sf::Vector2f position) {
    this->_position = position;
    _sprite.setPosition(position);
}

// Set the player's experience points
void Player::increaseEXP(int amount) {
    _exp += amount;
    if (_exp >= _exp_to_level) {
        _exp -= _exp_to_level;

        // Increase the required EXP for next level
        _exp_to_level = 100 + ((getLevel() - 1) * 10);

        _state_point++;
        increaseLevel();
    }
}

const sf::FloatRect Player::getBounds() {
    sf::FloatRect bounds = _sprite.getGlobalBounds();
    int           width  = bounds.width / 6;
    int           height = bounds.height / 6;

    bounds.left   += width * 2;
    bounds.top    += bounds.height - height;
    bounds.width   = width * 2;
    bounds.height  = height;
    return bounds;
}

// Get the next bounds based on the current position and movement
void Player::movement() {
    // Movement logic (updating position and direction)
    bool up    = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool down  = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool left  = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    int          speed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 2 : 1;
    sf::Vector2f movement(0.f, 0.f);
    if (up) movement.y -= speed;
    if (down) movement.y += speed;
    if (left) movement.x -= speed;
    if (right) movement.x += speed;

    // Normalize for diagonal movement
    if (movement.x != 0.f && movement.y != 0.f) {
        movement *= 0.7071f;
    }

    // Apply speed and delta time
    movement *= PLAYER_SPEED * _dt;

    // Determine direction for animation (priority: horizontal over vertical)
    if (movement.x < 0) animation(Left);
    else if (movement.x > 0) animation(Right);
    else if (movement.y < 0) animation(Up);
    else if (movement.y > 0) animation(Down);

    _next_bounds       = getBounds();
    _next_bounds.left += movement.x;
    _next_bounds.top  += movement.y;
}

// Update the player's animation based on the current direction
void Player::animation(const Direction direction) {
    // Update animation frame if the player is moving
    _animation_timer += _dt;
    if (_animation_timer < ANIMATION_SPEED) return;
    _animation_timer = 0.0f;

    _current_frame = (_current_frame + 1) % 4; // Loop through 4 frames
    _sprite.setTextureRect(sf::IntRect(_current_frame * PLAYER_FRAME,
                                       direction * PLAYER_FRAME, PLAYER_FRAME,
                                       PLAYER_FRAME));
}

// Check if the player can warp to a new room
Room Player::warpTo() { return _collision.hitWarps(getBounds()); }

// Check for interactables and return the type of interaction
void Player::update() {
    sf::Time deltaTime = _clock.restart();
    _dt                = deltaTime.asSeconds();

    if (!_moveable) return;
    movement();

    bool hit_obstacles = _collision.hitObstacles(getNextBounds());
    if (!hit_obstacles) {
        sf::FloatRect bounds  = getBounds();
        _position.x          += _next_bounds.left - bounds.left;
        _position.y          += _next_bounds.top - bounds.top;
        _sprite.setPosition(_position);
    }
}

// Draw the player sprite and collision boxes
void Player::draw(sf::RenderWindow &window) {
    _interact = _collision.onInteractables(getBounds());
    _collision.draw(window, _interact, false);
    window.draw(_sprite);
}