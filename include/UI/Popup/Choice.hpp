#pragma once

#include "Popup.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Choice: public Popup {
    protected:
        std::vector<std::string> choices;
        int                      selected = 0;

    public:
        Choice(const sf::Font &font, const sf::Vector2f &size, const sf::Vector2f &position): Popup(font, size, position) {}

        void open() override;

        void setChoices(const std::vector<std::string> choices);

        std::vector<std::string> getChoices() { return choices; }

        void moveSelection(int delta);

        const int getSelected() { return selected; }

        void render(sf::RenderWindow &window) override;
};