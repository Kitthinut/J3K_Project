#pragma once

#include <SFML/Graphics.hpp>

class Story {
    private:
        sf::Font font;

    public:
        Story();

        void introduction(sf::RenderWindow &window);
        void showCredits(sf::RenderWindow &window);
        void showEnding(sf::RenderWindow &window);
};
