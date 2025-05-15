#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Text {
    private:
        sf::Text text;

    public:
        Text(const unsigned int size, const sf::Color &color,
             const sf::Vector2f &position);

        void setFont(const sf::Font &font) { text.setFont(font); }

        void setText(const std::string &text);
        void setPosition(const sf::Vector2f &position);
        void draw(sf::RenderWindow &window);
};