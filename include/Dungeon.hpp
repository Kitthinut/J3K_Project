#pragma once

#include "BattlePhase.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "UI/UI.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class Dungeon {
    public:
        enum Turn { Person, Opponent };
        enum class Phase {
            Opening,
            PlayerPick,
            PlayerAttack,
            OpponentPick,
            OpponentAttack,
            End
        };

        Dungeon();
        void handleEvent(const sf::Event &event, bool &exitDungeonTest);
        void update();
        void render(sf::RenderWindow &window);
        void reset();

        // Getters for handlers
        Player *getPlayer() const { return player; }

        Entity *getBoss() { return &boss; }

        int getSelectedSkillIndex() const { return selectedSkillIndex; }

        int getPendingSkillIndex() const { return pendingSkillIndex; }

        int getManaRestoreAmount() const { return manaRestoreAmount; }

        bool isWaitingForContinue() const { return waitingForContinue; }

        bool isConfirmNormalAtFullMana() const { return confirmNormalAtFullMana; }

        // Setters
        void setPlayer(Player *p);
        void setPhase(Phase newPhase);

        void setPendingSkillIndex(int idx) { pendingSkillIndex = idx; }

        void setSelectedSkillIndex(int idx) { selectedSkillIndex = idx; }

        void setWaitingForContinue(bool value) { waitingForContinue = value; }

        void setConfirmNormalAtFullMana(bool val) {
            confirmNormalAtFullMana = val;
        }

        void triggerBossHitFlash() {
            bossHitFlash = true;
            bossHitClock.restart();
        }

        void updateBossHitFlash() {
            if (bossHitFlash &&
                bossHitClock.getElapsedTime().asSeconds() > bossHitFlashDuration)
                bossHitFlash = false;
        }

        // UI helpers

        void showMessage(const std::string &msg);
        void drawCenteredBoxWithText(sf::RenderWindow  &window,
                                     const std::string &message, float boxWidth,
                                     float boxHeight, float centerX, float centerY,
                                     const sf::Font &font, unsigned int charSize,
                                     sf::Color boxColor, sf::Color textColor);

    private:
        // Game Config
        int manaRestoreAmount = 20;

        // Game state
        sf::Clock bossHitClock;
        Turn      currentTurn;
        Phase     phase;
        int       turnCount;
        int       selectedSkillIndex;
        int       pendingSkillIndex       = -1;
        float     bossHitFlashDuration    = 0.3f;
        bool      waitingForContinue      = false;
        bool      confirmNormalAtFullMana = false;

        // Entities
        Player *player;
        Entity  boss;

        // UI
        UI ui;

        // Graphics
        sf::Texture backgroundTexture;
        sf::Sprite  backgroundSprite;
        sf::Texture bossTexture;
        sf::Sprite  bossSprite;

        // Animation & effects
        bool      bossHitFlash;
        bool      playerHitFlash;
        sf::Clock openingClock;
        float     openingDuration;

        // Battle phase handler
        IBattlePhaseHandler *currentPhaseHandler;
        PlayerPickPhase      playerPickPhase;
        PlayerAttackPhase    playerAttackPhase;
        OpponentPickPhase    opponentPickPhase;
        OpponentAttackPhase  opponentAttackPhase;

        // Helpers
        void randomizeBossImage();
        void centerText(sf::Text &text, float x, float y);
};