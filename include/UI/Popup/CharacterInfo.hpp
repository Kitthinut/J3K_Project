#pragma once

#include "Popup.hpp"
#include "Struct/Volume.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class CharacterInfo: public Popup {
    private:
    public:
        CharacterInfo(const sf::Font &font, const sf::Vector2f &size,
                      const sf::Vector2f &position)
            : Popup(font, size, position) {}

        void update(const std::string name, const int level, const Volume &hp,
                        const Volume &mana, const Volume &exp);

        void render(sf::RenderWindow &window) override;
};