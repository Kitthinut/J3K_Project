#pragma once

#include "DialogueBox.hpp"
#include "Enum/Direction.hpp"
#include "Enum/Room.hpp"
#include "Dungeon.hpp"
#include "Struct/Interactable.hpp"
#include "UI/UI.hpp"

#include <functional>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define PLAYER_FRAME  64

class Game {
    private:
        // Core SFML
        sf::RenderWindow window = {sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                                   "FIBO XI DUNGEON"};
        sf::Clock        clock;

        // UI
        UI ui;

        // Player
        sf::Sprite   playerSprite;
        sf::Texture  spriteSheet;
        sf::Vector2f playerPosition  = sf::Vector2f(800, 600);
        Direction    playerDirection = Down;
        int          currentFrame    = 0;
        const float  playerSpeed     = 200.0f;

        // Background
        sf::Texture backgroundTexture;
        sf::Sprite  background;

        // Portrait
        sf::Sprite  portrait;
        sf::Texture portraitTexture;

        // Dialogue
        DialogueBox dialogueBox;

        // Rooms and Transitions
        Room                       currentRoom = Dorm;
        std::vector<sf::FloatRect> obstacles;

        // Interactables
        std::vector<Interactable> interactables;
        

        // Dungeon
        Dungeon dungeon;

        // Stats Popup
        bool showStatsPopup = false;

        // Upgrade Stats Popup
        bool showUpgradeStatsPopup = false;
        int  upgradePoints         = 5;
        int  selectedStat          = 0;

        // Player Stats
        int currentHP   = 50;
        int maxHP       = 100;
        int currentMana = 30;
        int maxMana     = 50;
        int currentEXP  = 0;
        int maxEXP      = 100;

        // playerInfo
        std::string playerName        = "Hero";
        bool        showCharacterInfo = false;

        // Game loop helpers
        void processEvents();
        void update();
        void render();

        //Dungeon Test
        bool inDungeonTest = false;

    public:
        Game();
        void run();
};