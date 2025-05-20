#include "UI/UI.hpp"

#include <iostream>

UI::UI() {
    if (!font.loadFromFile("assets/fonts/Electrolize-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    setCoins(0);
    setLevel(1);

    // Quest list display
    for (int i = 0; i < quest_lists.size(); ++i) {
        Text text_quest = {
            font, 20, sf::Color::White, {20.f, 60.f + i * 30}
        };
        text_quest.setText("- " + quest_lists[i]);
        quest_texts.push_back(text_quest);
    }
}

void UI::setCoins(const int coins) {
    text_coin.setText("Coins: " + std::to_string(coins));
}

void UI::setLevel(const int level) {
    this->level = level;
    text_level.setText("Lv " + std::to_string(level));
}

void UI::setBarsVolume(const Volume &hp, const Volume &mana, const Volume &exp) {
    bar_hp.setVolume(hp);
    bar_mana.setVolume(mana);
    bar_exp.setVolume(exp);
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

    // ==== Draw Coins ====
    text_coin.draw(window);

    // ==== Draw Level ====
    text_level.draw(window);

    // ==== Draw Quests ====
    for (Text &text_quest : quest_texts) {
        text_quest.draw(window);
    }

    // ==== Draw Bar ====
    bar_hp.draw(window);
    bar_mana.draw(window);
    bar_exp.draw(window);

    // ==== Draw Choice Popup ====
    popup_choice.render(window);

    // ==== Draw Character Info Popup ====
    popup_character_info.render(window);

    // ==== Draw Upgrade Stats Popup ====
    popup_upgrade.render(window);
}