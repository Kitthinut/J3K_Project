#include "UI/Popup/DialogueBox.hpp"

#include <sstream>

DialogueBox::DialogueBox(const sf::Font &font, const sf::Vector2f &size,
                         const sf::Vector2f &max_position)
    : Popup(font, size, max_position) {

    displayed_text.setFont(font);
    displayed_text.setCharacterSize(32);
    displayed_text.setFillColor(sf::Color::White);
    displayed_text.setPosition(position.x + PADDING, position.y + PADDING);
}

void DialogueBox::setText(const std::string &text) {
    std::stringstream ss(text);
    std::string       line;
    lines.clear();
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    current_line = 0;
    displayed_text.setString(lines.empty() ? "" : lines[0]);
    open();
}

void DialogueBox::continues() {
    if (current_line + 1 < lines.size()) {
        current_line++;
        displayed_text.setString(lines[current_line]);
        return;
    }
    close();
}

void DialogueBox::render(sf::RenderWindow &window) {
    if (!is_open) return;
    window.draw(background);
    window.draw(displayed_text);
}