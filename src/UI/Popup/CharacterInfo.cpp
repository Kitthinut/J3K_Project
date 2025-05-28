#include "UI/Popup/CharacterInfo.hpp"

void CharacterInfo::update(const std::string name, const int level,
                           const Volume &hp, const Volume &mana, const Volume &exp,
                           const int &atk, const int &def) {
    std::vector<std::string> lines = {
        "Character Info",
        "Name: " + name,
        "Level: " + std::to_string(level),
        "EXP: " + std::to_string(exp.current) + " / " + std::to_string(exp.max),
        "HP: " + std::to_string(hp.current) + " / " + std::to_string(hp.max),
        "Mana: " + std::to_string(mana.current) + " / " + std::to_string(mana.max),
        "Attack Power: " + std::to_string(atk),
        "Defense Power: " + std::to_string(def)};
    texts.clear();

    for (int i = 0; i < lines.size(); ++i) {
        sf::Text text(lines[i], *font, 24);
        text.setPosition(position.x + PADDING, position.y + PADDING + i * 40);
        text.setFillColor(sf::Color::White);
        texts.push_back(text);
    }
}

void CharacterInfo::render(sf::RenderWindow &window) {
    if (!is_open) return;
    window.draw(background);

    for (sf::Text &text : texts) {
        window.draw(text);
    }
}
