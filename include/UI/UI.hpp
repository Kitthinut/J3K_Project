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
        sf::Font _font;
        bool     _dungeon = false;

        Text _text_level = {
            _font, 20, sf::Color::White, {1640, 80}
        };

        Bar _bar_hp = {
            "assets/ui/HpBar.png",
            "assets/ui/hp_bar_fill.png",
            sf::Color::Red,
            {1700, 20}
        };
        Bar _bar_mana = {
            "assets/ui/ManaBar.png",
            "assets/ui/mana_bar_fill.png",
            sf::Color::Blue,
            {1700, 50}
        };
        Bar _bar_exp = {
            "assets/ui/ExpBar.png",
            "assets/ui/exp_bar_fill.png",
            sf::Color::Green,
            {1700, 80}
        };

    public:
        UI();

        Choice popup_choice = {
            _font,
            {             600,               200},
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
        };

        CharacterInfo popup_character_info = {
            _font,
            {             600,               400},
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
        };

        Upgrade popup_upgrade = {
            _font,
            {             500,               300},
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
        };

        DialogueBox dialogue = {
            _font,
            {            1720,                 180},
            {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 130},
        };

        sf::Font& getFont() { return _font; }

        void setLevel(const int level);
        void setBarsVolume(const Volume &hp, const Volume &mana,
                           const Volume &exp);

        void setDungeon(bool dungeon) { _dungeon = dungeon; }

        bool popUpIsOpen();
        void closePopUp();

        void render(sf::RenderWindow &window);
};