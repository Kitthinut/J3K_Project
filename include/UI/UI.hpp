#pragma once

#include "Bar.hpp"
#include "Popup/CharacterInfo.hpp"
#include "Popup/Choice.hpp"
#include "Popup/DialogueBox.hpp"
#include "Popup/Upgrade.hpp"
#include "Text.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

class UI {
    private:
        sf::Font font;
        int      level;

        Text text_coin = {
            font, 24, sf::Color::Yellow, {20, 20}
        };
        Text text_level = {
            font, 20, sf::Color::White, {1640, 80}
        };

        // Quest
        std::vector<std::string> quest_lists = {"Quest 1", "Quest 2", "Quest 3"};
        std::vector<Text>        quest_texts;

        Bar bar_hp = {
            "assets/ui/hp_bar_bg.png",
            "assets/ui/hp_bar_fill.png",
            sf::Color::Red,
            {1700, 20}
        };
        Bar bar_mana = {
            "assets/ui/mana_bar_bg.png",
            "assets/ui/mana_bar_fill.png",
            sf::Color::Blue,
            {1700, 50}
        };
        Bar bar_exp = {
            "assets/ui/exp_bar_bg.png",
            "assets/ui/exp_bar_fill.png",
            sf::Color::Green,
            {1700, 80}
        };

    public:
        UI();

        Choice popup_choice = {
            font,
            {             600,               200},
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
        };

        CharacterInfo popup_character_info = {
            font,
            {             600,               400},
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
        };

        Upgrade popup_upgrade = {
            font,
            {             500,               300},
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
        };

        DialogueBox dialogue = {
            font,
            {            1720,                 180},
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 130},
        };

        void setCoins(const int coins);
        void setLevel(const int level);
        void setBarsVolume(const Volume &hp, const Volume &mana,
                           const Volume &exp);

        void render(sf::RenderWindow &window);
};