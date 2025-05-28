#include "UI/Popup/Choice.hpp"

void Choice::open() {
    is_open  = true;
    selected = 0;
}

void Choice::setChoices(const std::vector<std::string> choices) {
    this->choices = choices;
    texts.clear();

    for (int i = 0; i < choices.size(); ++i) {
        sf::Text text(choices[i], *font, 24);
        text.setPosition(position.x + PADDING, position.y + PADDING + i * 40);
        text.setFillColor(sf::Color::White);
        texts.push_back(text);
    }
}

void Choice::render(sf::RenderWindow &window) {
    if (!is_open) return;
    window.draw(background);

    for (int i = 0; i < texts.size(); ++i) {
        if (i == selected) {
            texts[i].setFillColor(sf::Color::Yellow);
        } else {
            texts[i].setFillColor(sf::Color::White);
        }
        window.draw(texts[i]);
    }
}

void Choice::moveSelection(int delta) {
    if (choices.empty()) return;

    selected        += delta;
    int num_choices  = choices.size();
    if (selected < 0) selected = num_choices - 1;
    else if (selected >= num_choices) selected = 0;
}