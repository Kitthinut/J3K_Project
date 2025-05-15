#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class DialogueBox {
    private:
        sf::Font                 font;
        sf::RectangleShape       box;
        sf::Text                 displayedText;
        std::vector<std::string> lines;
        size_t                   currentLine = 0;

    public:
        DialogueBox();
        void setText(const std::string &text);
        void advance();
        void draw(sf::RenderWindow &window);
        void setBoxSizeAndPosition(const sf::Vector2f &size,
                                   const sf::Vector2f &position);
        bool isFinished() const;
        bool visible = true;
};
