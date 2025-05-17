#pragma once

#include "Popup.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class DialogueBox: public Popup {
    private:
        sf::Text                 displayed_text;
        std::vector<std::string> lines;
        int                      current_line = 0;

    public:
        DialogueBox(const sf::Font &font, const sf::Vector2f &size,
                    const sf::Vector2f &max_position);

        void setText(const std::string &text);
        void continues();

        void render(sf::RenderWindow &window) override;
};
