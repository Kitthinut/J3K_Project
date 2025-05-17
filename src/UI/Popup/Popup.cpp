#include "UI/Popup/Popup.hpp"

Popup::Popup(const sf::Font &font, const sf::Vector2f &size,
             const sf::Vector2f &position)
    : font(&font), size(size), mid_position(position) {
    this->position = {
        mid_position.x - (size.x / 2),
        mid_position.y - (size.y / 2),
    };

    background.setSize(size);
    background.setFillColor(sf::Color(0, 0, 0, 220));
    background.setOutlineThickness(3);
    background.setOutlineColor(sf::Color::White);
    background.setPosition(this->position.x, this->position.y);
}