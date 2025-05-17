#include "UI/Bar.hpp"

#include <iostream>

Bar::Bar(const std::string &bg, const std::string &fill, const sf::Color &color,
         const sf::Vector2f &pos) {
    if (!bgTexture.loadFromFile(bg)) {
        return;
    }
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(pos);
    // fillSprite.setTexture(fillTexture);
    // fillSprite.setPosition(pos);

    // Initialize bar
    frontBar.setFillColor(color);
    frontBar.setPosition(pos);
}

void Bar::setVolume(const Volume &volume) {
    frontBar.setSize(sf::Vector2f(size.x * volume.current / volume.max, size.y));
}

void Bar::draw(sf::RenderWindow &window) {
    if (bgSprite.getTexture() == nullptr) return;

    window.draw(frontBar);
    window.draw(fillSprite);
    window.draw(bgSprite);
}