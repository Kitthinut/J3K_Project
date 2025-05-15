#include "UI/Popup/Choice.hpp"

Choice::Choice(const sf::Vector2f &size, const sf::Vector2f &max_position)
    : size(size), max_position(max_position) {
    position = {
        (max_position.x - size.x) / 2,
        (max_position.y - size.y) / 2,
    };

    background.setSize(size);
    background.setFillColor(sf::Color(0, 0, 0, 220));
    background.setOutlineThickness(3);
    background.setOutlineColor(sf::Color::White);
    background.setPosition(position.x, position.y);
}

void Choice::open() {
    is_open  = true;
    selected = 0;
}

void Choice::setChoices(const std::vector<std::string> choices) {
    this->choices = choices;
    choice_texts.clear();

    for (int i = 0; i < choices.size(); ++i) {
        sf::Text choice_text(choices[i], *font, 24);
        choice_text.setPosition(position.x + PADDING, position.y + PADDING + i * 40);
        choice_text.setFillColor(sf::Color::White);
        choice_texts.push_back(choice_text);
    }
}

void Choice::render(sf::RenderWindow &window) {
    if (!is_open) return;

    window.draw(background);

    for (int i = 0; i < choice_texts.size(); ++i) {
        if (i == selected) {
            choice_texts[i].setFillColor(sf::Color::Yellow);
        } else {
            choice_texts[i].setFillColor(sf::Color::White);
        }
        window.draw(choice_texts[i]);
    }
}

void Choice::moveSelection(int delta) {
    if (choices.empty()) return;

    selected        += delta;
    int num_choices  = choices.size();
    if (selected < 0) selected = num_choices - 1;
    else if (selected >= num_choices) selected = 0;
}