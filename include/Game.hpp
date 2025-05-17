#pragma once

#include "Enum/Direction.hpp"
#include "Enum/Room.hpp"
#include "Player.hpp"
#include "UI/UI.hpp"
#include "Struct/CollisionManager.hpp"

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

        // Player
        Player player = {
            {800, 600}
        };

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
        int currentEXP  = 0;
        int maxEXP      = 100;

        // playerInfo
        std::string playerName = "Hero";

        void changeRoomTo(Room room, std::string path, sf::Vector2f spawn_pos);

        CollisionManager collisionManager;

        // Game loop helpers
        void processEvents();
        void update();
        void render();

    public:
        Game();
        void run();
};