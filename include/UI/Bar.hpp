#pragma once

#include "Struct/Volume.hpp"

#include <SFML/Graphics.hpp>

class Bar {
    private:
        sf::Texture        bgTexture;
        sf::Texture        fillTexture;
        sf::Sprite         bgSprite;
        sf::Sprite         fillSprite;
        sf::RectangleShape frontBar;

        sf::Vector2f size = {200, 20};

    public:
        Bar(const std::string &bg, const std::string &fill, const sf::Color &color,
            const sf::Vector2f &pos);

        void setSize(const sf::Vector2f &size) { this->size = size; }

        void setVolume(const Volume &volume);
        void draw(sf::RenderWindow &window);
};
