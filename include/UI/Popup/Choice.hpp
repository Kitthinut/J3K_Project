#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Choice {
    private:
        sf::Vector2f size;
        sf::Vector2f position;
        sf::Vector2f max_position;

        const sf::Font          *font;
        std::vector<std::string> choices;
        std::vector<sf::Text>    choice_texts;
        sf::RectangleShape       background;

        const int PADDING = 20;

        bool is_open  = false;
        int  selected = 0;

    public:
        Choice(const sf::Vector2f &size, const sf::Vector2f &max_position);

        void open();

        void close() { is_open = false; }

        const bool isOpen() { return is_open; }

        void setFont(const sf::Font &font) { this->font = &font; }

        void setChoices(const std::vector<std::string> choices);

        std::vector<std::string> getChoices() { return choices; }

        void moveSelection(int delta);

        const int getSelected() { return selected; }

        void render(sf::RenderWindow &window);
};