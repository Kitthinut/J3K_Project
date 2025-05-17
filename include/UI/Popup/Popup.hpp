#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define PADDING 20

class Popup {
    protected:
        sf::Vector2f size;
        sf::Vector2f position;
        sf::Vector2f mid_position;

        const sf::Font       *font;
        std::vector<sf::Text> texts;
        sf::RectangleShape    background;

        bool is_open = false;

    public:
        Popup(const sf::Font &font, const sf::Vector2f &size,
              const sf::Vector2f &position);

        virtual void open() { is_open = true; }

        virtual void close() { is_open = false; }

        const bool isOpen() { return is_open; }

        virtual void render(sf::RenderWindow &window) {
            if (!is_open) return;
            window.draw(background);
        }
};