#include "UI/UI.hpp"

#include <iostream>

UI::UI() {
    if (!_font.loadFromFile("assets/fonts/Electrolize-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    setLevel(1);
}

void UI::setLevel(const int level) {
    _text_level.setText("Lv " + std::to_string(level));
}

void UI::setDays(const int days) {
    _text_Day.setText("Day " + std::to_string(days));
}

void UI::setBarsVolume(const Volume &hp, const Volume &mana, const Volume &exp) {
    _bar_hp.setVolume(hp);
    _bar_mana.setVolume(mana);
    _bar_exp.setVolume(exp);
}

bool UI::popUpIsOpen() {
    return popup_character_info.isOpen() || popup_choice.isOpen() ||
           popup_upgrade.isOpen();
}

void UI::closePopUp() {
    popup_character_info.close();
    popup_choice.close();
    popup_upgrade.close();
}

void UI::render(sf::RenderWindow &window) {

    // ==== Draw Dialogue Box ====
    dialogue.render(window);

    if (_dungeon) return;

    // ==== Draw Level ====
    _text_level.draw(window);

    // ==== Draw Day ====
    _text_Day.draw(window);

    // ==== Draw Bar ====
    _bar_hp.draw(window);
    _bar_mana.draw(window);
    _bar_exp.draw(window);

    // ==== Draw Choice Popup ====
    popup_choice.render(window);

    // ==== Draw Character Info Popup ====
    popup_character_info.render(window);

    // ==== Draw Upgrade Stats Popup ====
    popup_upgrade.render(window);
}