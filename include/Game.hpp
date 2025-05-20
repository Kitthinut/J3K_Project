#pragma once

#include "Dungeon.hpp"
#include "Enum/Direction.hpp"
#include "Enum/Room.hpp"
#include "Player.hpp"
#include "Story.hpp"
#include "UI/UI.hpp"

#include <functional>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Game {
    private:
        // Core SFML
        sf::RenderWindow window = {sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                                   "FIBO XI DUNGEON"};

        // UI
        UI ui;

        // Story Trailer
        Story story;

        // Player
        // Player player = {
        //     {800, 600}
        // };

        // Background
        sf::Texture backgroundTexture;
        sf::Sprite  background;

        // Upgrade Stats Popup
        int upgradePoints = 5;

        // Player Stats
        int currentHP   = 50;
        int maxHP       = 100;
        int currentMana = 30;
        int maxMana     = 50;
        int currentAtk  = 10;
        int currentDef  = 5;
        int currentExp  = 0;
        int maxExp      = 100;

        // playerInfo
        std::string playerName = "Hero";

        // Player
        Player player = {
            {800, 600}, playerName, maxHP, currentHP, maxMana, currentMana,
            currentAtk, currentDef, 1
        };


        // Dungeon
        Dungeon dungeon;
        bool    inDungeonTest = false;

        void changeRoomTo(Room room, std::string path, sf::Vector2f spawn_pos);
        void statsCap();
        void modifyStat(int direction);
        void handleChoiceSelection();
        void openPopupForInteraction();

        // Game loop helpers
        void processEvents();
        void update();
        void render();

    public:
        Game();
        void run();
};