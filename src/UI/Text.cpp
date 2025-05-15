#include "UI/Text.hpp"

#include <iostream>

Text::Text(const unsigned int size, const sf::Color &color,
           const sf::Vector2f &position) {
    text.setCharacterSize(size);
    text.setFillColor(color);
    setPosition(position);
}

void Text::setPosition(const sf::Vector2f &position) { text.setPosition(position); }

void Text::setText(const std::string &text) { this->text.setString(text); }

void Text::draw(sf::RenderWindow &window) { window.draw(text); }