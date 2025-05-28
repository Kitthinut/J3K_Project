#pragma once

#include "Choice.hpp"
#include "Struct/Volume.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Upgrade: public Choice {
    private:
        const sf::Vector2f              BUTTON_SIZE = {30, 30};
        std::vector<sf::RectangleShape> button_shapes;
        std::vector<sf::Text>           button_texts;
        sf::Text                        points;

    public:
        Upgrade(const sf::Font &font, const sf::Vector2f &size,
                const sf::Vector2f &position);

        void createButton(const char sign, const sf::Color &color, const float x,
                          const float y);

        void update(const int point, const Volume &hp, const Volume &mana,
                    const int atk, const int def);

        void render(sf::RenderWindow &window) override;
};