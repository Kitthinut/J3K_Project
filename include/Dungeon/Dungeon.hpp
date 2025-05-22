#pragma once

#include "BattlePhase.hpp"
#include "Entity/Player.hpp"
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

        Dungeon(UI &ui, Player &player);
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

        void setGameEnded(bool val) { gameEnded = val; }

        bool isGameEnded() const { return gameEnded; }

        // UI helpers

        void showMessage(const std::string &msg);
        void drawCenteredBoxWithText(sf::RenderWindow  &window,
                                     const std::string &message, float boxWidth,
                                     float boxHeight, float centerX, float centerY, unsigned int charSize,
                                     sf::Color boxColor, sf::Color textColor);

    private:
        // Game Config
        int manaRestoreAmount = 20;

        // Game state
        sf::Clock bossHitClock;
        Turn      currentTurn             = Person;
        Phase     phase                   = Phase::Opening;
        int       turnCount               = 1;
        int       selectedSkillIndex      = -1;
        int       pendingSkillIndex       = -1;
        float     bossHitFlashDuration    = 0.3f;
        bool      waitingForContinue      = false;
        bool      confirmNormalAtFullMana = false;
        bool      gameEnded               = false;

        // Entities
        Player *player = nullptr;
        Entity  boss   = {"Boss", 200, 200, 100, 100, 30, 10, 1};

        // UI
        UI *ui = nullptr;

        // Fonts
        sf::Font *font;

        // Graphics
        sf::Texture backgroundTexture;
        sf::Sprite  backgroundSprite;
        sf::Texture bossTexture;
        sf::Sprite  bossSprite;

        // Animation & effects
        sf::Clock openingClock;
        bool      bossHitFlash    = false;
        bool      playerHitFlash  = false;
        float     openingDuration = 1.5f;

        // Battle phase handler
        IBattlePhaseHandler *currentPhaseHandler = nullptr;
        PlayerPickPhase      playerPickPhase;
        PlayerAttackPhase    playerAttackPhase;
        OpponentPickPhase    opponentPickPhase;
        OpponentAttackPhase  opponentAttackPhase;

        // Helpers
        void randomizeBossImage();
        void centerText(sf::Text &text, float x, float y);
};