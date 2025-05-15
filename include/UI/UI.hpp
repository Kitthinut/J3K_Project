#pragma once

#include "Bar.hpp"
#include "Popup/Choice.hpp"
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
            24, sf::Color::Yellow, {20, 20}
        };
        Text text_level = {
            20, sf::Color::White, {1640, 80}
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
            {         600,           200},
            {WINDOW_WIDTH, WINDOW_HEIGHT},
        };

        void setCoins(const int coins);
        void setLevel(const int level);

        void render(sf::RenderWindow &window);
        void setBarVolume(const Volume &hp, const Volume &mana, const Volume &exp);
};