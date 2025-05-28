#pragma once

#include "BattlePhase.hpp"
#include "UI/UI.hpp"

#include <SFML/Graphics.hpp>
#include <string>

#define BOSS_FACTOR 1.5 // Boss stats multiplier

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
        void setPhase(Phase newPhase);
        void triggerBossHitFlash();
        void triggerPlayerHitFlash();
        void updateHitFlash();

        // Getters for handlers
        Player *getPlayer() const { return player; }

        Entity *getBoss() { return &boss; }

        int getSelectedSkillIndex() const { return selectedSkillIndex; }

        int getPendingSkillIndex() const { return pendingSkillIndex; }

        int getManaRestoreAmount() const { return manaRestoreAmount; }

        // Setters
        void setPendingSkillIndex(int idx) { pendingSkillIndex = idx; }

        void setSelectedSkillIndex(int idx) { selectedSkillIndex = idx; }

        void setGameEnded(bool val) { gameEnded = val; }

        bool isGameEnded() const { return gameEnded; }

        // UI helpers
        void showMessage(const std::string &msg);
        void drawCenteredBoxWithText(sf::RenderWindow  &window,
                                     const std::string &message, float boxWidth,
                                     float boxHeight, float centerX, float centerY,
                                     unsigned int charSize, sf::Color boxColor,
                                     sf::Color textColor);

    private:
        // Game Config
        int manaRestoreAmount = 20;

        // Game state
        Turn  currentTurn        = Person;
        Phase phase              = Phase::Opening;
        int   turnCount          = 1;
        int   selectedSkillIndex = -1;
        int   pendingSkillIndex  = -1;
        bool  waitingForContinue = false;
        bool  gameEnded          = false;

        // Entities
        Player                  *player = nullptr;
        Entity                   boss   = {"Boss", 100, 100, 10, 10, 1};
        std::vector<std::string> bossImages = {};

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
        sf::Clock HitClock;
        sf::Clock openingClock;
        float     hitFlashDuration = 0.3f;
        bool      bossHitFlash     = false;
        bool      playerHitFlash   = false;
        float     openingDuration  = 1.5f;

        // Battle phase handler
        IBattlePhaseHandler *currentPhaseHandler = nullptr;
        PlayerPickPhase      playerPickPhase     = {this, player};
        PlayerAttackPhase    playerAttackPhase   = {this, player};
        OpponentPickPhase    opponentPickPhase   = {this, player};
        OpponentAttackPhase  opponentAttackPhase = {this, player};

        // Helpers
        void randomizeBoss();
        void centerText(sf::Text &text, float x, float y);
};