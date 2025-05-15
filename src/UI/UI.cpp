#include "UI/UI.hpp"

#include <iostream>

UI::UI() {
    if (!font.loadFromFile("assets/fonts/Electrolize-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    text_coin.setFont(font);
    text_level.setFont(font);
    setCoins(0);
    setLevel(1);

    // Quest list display
    for (int i = 0; i < quest_lists.size(); ++i) {
        Text text_quest = {
            20, sf::Color::White, {20.f, 60.f + i * 30}
        };
        text_quest.setFont(font);
        text_quest.setText("- " + quest_lists[i]);
        quest_texts.push_back(text_quest);
    }

    popup_choice.setFont(font);
}

void UI::setCoins(const int coins) {
    text_coin.setText("Coins: " + std::to_string(coins));
}

void UI::setLevel(const int level) {
    this->level = level;
    text_level.setText("Lv " + std::to_string(level));
}

void UI::setBarVolume(const Volume &hp, const Volume &mana, const Volume &exp) {
    bar_hp.setVolume(hp);
    bar_mana.setVolume(mana);
    bar_exp.setVolume(exp);
}

void UI::render(sf::RenderWindow &window) {
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
}