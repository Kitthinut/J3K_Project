#pragma once

#include "Skill.hpp"

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Dungeon {
    public:
        enum Turn { Player, Opponent };

        Dungeon();

        void handleEvent(const sf::Event &event, bool &exitDungeonTest);
        void update();
        void render(sf::RenderWindow &window);
        void setPlayerSkills(const std::vector<Skill> &skills);

        Turn getCurrentTurn() const;
        void reset();

    private:
        Turn        currentTurn;
        sf::Texture backgroundTexture;
        sf::Sprite  backgroundSprite;
        sf::Texture bossTexture;
        sf::Sprite  bossSprite;

        std::vector<Skill> playerSkills;
        std::string        lastActionMessage;
        int                selectedSkillIndex = -1;
        bool               waitingForContinue = false;

        // กูขี้เกียจทำ 55555+
        void centerText(sf::Text &text, float x, float y);
        void drawCenteredBoxWithText(sf::RenderWindow  &window,
                                     const std::string &message, float boxWidth,
                                     float boxHeight, float centerX, float centerY,
                                     const sf::Font &font, unsigned int charSize,
                                     sf::Color boxColor, sf::Color textColor);
        enum class BattlePhase {
            Opening,
            PlayerPick,
            PlayerConfirm,
            PlayerAttackAnim,
            OpponentPick,
            OpponentAttackAnim
        };

        BattlePhase phase = BattlePhase::PlayerPick;
        sf::Clock   animClock;
        float       animDuration   = 0.5f; // half a second for hit flash
        bool        bossHitFlash   = false;
        bool        playerHitFlash = false;

        sf::Clock opponentPickClock;
        float     opponentPickDelay = 0.7f; // seconds

        sf::Clock openingClock;
        float     openingDuration = 1.5f; // seconds

        int turnCount = 1;

        // Sound for boss intro
        // sf::SoundBuffer bossIntroBuffer;
        // sf::Sound       bossIntroSound;
        // bool            bossIntroPlayed = false;
};