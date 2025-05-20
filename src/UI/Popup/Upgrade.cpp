#include "UI/Popup/Upgrade.hpp"

#include <iostream>

Upgrade::Upgrade(const sf::Font &font, const sf::Vector2f &size,
                 const sf::Vector2f &position)
    : Choice(font, size, position) {
    choices = {"HP: ", "Mana: ", "ATK: ", "DEF: "};

    int plus_positon  = position.x + (size.x / 2) - BUTTON_SIZE.x - PADDING;
    int minus_positon = plus_positon - 15 - BUTTON_SIZE.x;

    for (int i = 0; i < choices.size(); ++i) {
        float offset_x = this->position.x + PADDING;
        float offset_y = this->position.y + PADDING + i * 40;

        sf::Text text(choices[i], font, 24);
        text.setPosition(offset_x, offset_y);
        text.setFillColor(sf::Color::White);
        texts.push_back(text);

        createButton('-', sf::Color::Red, minus_positon, offset_y);
        createButton('+', sf::Color(70, 187, 31, 255), plus_positon, offset_y);
    }
}

void Upgrade::createButton(const char sign, const sf::Color &color, const float x,
                           const float y) {
    sf::RectangleShape button(BUTTON_SIZE);
    button.setPosition(x, y);
    button.setFillColor(color);
    button_shapes.push_back(button);

    sf::Text text(sign, *font, 24);
    text.setPosition(x + 9, y - 1);
    text.setFillColor(sf::Color::White);
    button_texts.push_back(text);
}

void Upgrade::update(const Volume &hp, const Volume &mana, const int atk, const int def) {
    texts[0].setString(choices[0] + std::to_string(hp.current) + " / " + std::to_string(hp.max));
    texts[1].setString(choices[1] + std::to_string(mana.current) + " / " + std::to_string(mana.max));
    texts[2].setString(choices[2] + std::to_string(atk));
    texts[3].setString(choices[3] + std::to_string(def));
}

void Upgrade::render(sf::RenderWindow &window) {
    if (!is_open) return;
    window.draw(background);

    for (int i = 0; i < texts.size(); ++i) {
        if (i == selected) {
            texts[i].setFillColor(sf::Color::Yellow);
        } else {
            texts[i].setFillColor(sf::Color::White);
        }
        window.draw(texts[i]);

        int j = i * 2;
        window.draw(button_shapes[j]);
        window.draw(button_shapes[j + 1]);
        window.draw(button_texts[j]);
        window.draw(button_texts[j + 1]);
    }
}