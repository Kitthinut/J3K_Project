#pragma once

#include "Dungeon/Dungeon.hpp"
#include "Enum/Direction.hpp"
#include "Enum/Room.hpp"
#include "Story.hpp"

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

        // Background
        sf::Texture backgroundTexture;
        sf::Sprite  background;

        // playerInfo
        std::string playerName = "Hero";

        // Player
        Player player = {
            {800, 600},
            "Hero", 100, 50, 50, 30, 10, 5, 1
        };

        // Dungeon
        Dungeon dungeon       = {ui, player};
        bool    inDungeonTest = false;

        // Game state
        int day            = 1; // Current day in the game
        int slot_remaining = 5; // Remaining skill points

        void changeRoomTo(Room room, std::string path, sf::Vector2f spawn_pos);
        void modifyStat(int direction);
        void handleChoiceSelection();
        void openPopupForInteraction();
        void NextDay();

        // Game loop helpers
        void processEvents();
        void update();
        void render();

    public:
        Game();
        void run();
};