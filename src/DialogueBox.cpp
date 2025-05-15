#include "DialogueBox.hpp"

#include <sstream>

DialogueBox::DialogueBox() {
    font.loadFromFile("assets/fonts/Electrolize-Regular.ttf");

    displayedText.setFont(font);
    displayedText.setCharacterSize(32);
    displayedText.setFillColor(sf::Color::White);
    displayedText.setPosition(100, 880);

    box.setSize(sf::Vector2f(1720, 180));
    box.setFillColor(sf::Color(0, 0, 0, 200));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2);
    box.setPosition(100, 860);
}

void DialogueBox::setText(const std::string &text) {
    std::stringstream ss(text);
    std::string       line;
    lines.clear();
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    currentLine = 0;
    displayedText.setString(lines.empty() ? "" : lines[0]);
    visible = true;
}

void DialogueBox::advance() {
    if (currentLine + 1 < lines.size()) {
        currentLine++;
        displayedText.setString(lines[currentLine]);
    } else {
        visible = false;
    }
}

void DialogueBox::draw(sf::RenderWindow &window) {
    if (!visible) return;
    window.draw(box);
    window.draw(displayedText);
}

void DialogueBox::setBoxSizeAndPosition(const sf::Vector2f &size,
                                        const sf::Vector2f &position) {
    box.setSize(size);
    box.setPosition(position);
    displayedText.setPosition(position.x + 20,
                              position.y + 20); // Padding inside box
}

bool DialogueBox::isFinished() const {
    return !visible || (currentLine + 1 >= lines.size());
}
