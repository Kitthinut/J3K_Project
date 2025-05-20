#include "Player.hpp"

#include <iostream>

Player::Player(sf::Vector2f position, std::string name, int maxHP, int currentHP,
               int maxMana, int currentMana, int attackPower, int defensePower,
               int level)
    : Entity(name, maxHP, currentHP, maxMana, currentMana, attackPower,
             defensePower, level) {
    // Load player sprite
    if (!_texture.loadFromFile("assets/characters/Spritesheet.png")) {
        std::cerr << "Failed to load sprite sheet!" << std::endl;
    }
    _sprite.setScale(3.0f, 3.0f);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, PLAYER_FRAME, PLAYER_FRAME));
    setPosition(position);

    _inventory.setMaxSize(20); // Set the maximum size of the inventory

    setSkill(0, new Skill("Normal Attact", 0, 0, 30, 1.0f, 0));
    setSkill(1, new Skill("Ice Spike", 8, 0, 20, 1.0f, 0));
    setSkill(2, new Skill("Thunder", 12, 0, 35, 1.0f, 0));
    setSkill(3, new Skill("Heal", 15, 0, -25, 1.0f, 0));
    setSkill(4, new Skill("Slash", 5, 0, 15, 1.0f, 0));
}

void Player::setPosition(sf::Vector2f position) {
    this->_position = position;
    _sprite.setPosition(position);
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

void Player::movement() {
    // Movement logic (updating position and direction)
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= PLAYER_SPEED * _dt;
        animation(Up);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += PLAYER_SPEED * _dt;
        animation(Down);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= PLAYER_SPEED * _dt;
        animation(Left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += PLAYER_SPEED * _dt;
        animation(Right);
    }

    _next_bounds       = getBounds();
    _next_bounds.left += movement.x;
    _next_bounds.top  += movement.y;
}

void Player::animation(Direction direction) {
    // Update animation frame if the player is moving
    _animation_timer += _dt;
    if (_animation_timer < ANIMATION_SPEED) return;
    _animation_timer = 0.0f;
    _current_frame  = (_current_frame + 1) % 4; // Loop through 4 frames
    _sprite.setTextureRect(sf::IntRect(_current_frame * PLAYER_FRAME,
                                       direction * PLAYER_FRAME, PLAYER_FRAME,
                                       PLAYER_FRAME));
}

Room Player::warpTo() { return _collision.hitWarps(getBounds()); }

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

void Player::draw(sf::RenderWindow &window) {
    interact = _collision.onInteractables(getBounds());
    _collision.draw(window, interact, false);
    window.draw(_sprite);
}