#pragma once

class Dungeon; // Forward declaration of the Dungeon class

#include "Entity/Player.hpp"

#include <SFML/Graphics.hpp>
#include <string>

// Handler interface
class IBattlePhaseHandler {
    protected:
        Dungeon *dungeon = nullptr;
        Player  *player  = nullptr;

    public:
        IBattlePhaseHandler(Dungeon *dungeon, Player *player)
            : dungeon(dungeon), player(player) {}

        virtual void handleEvent(const sf::Keyboard::Key &, bool &) {}

        virtual void update() {}

        virtual void render(sf::RenderWindow &) {}
};

// Player selects a skill
class PlayerPickPhase: public IBattlePhaseHandler {
    public:
        PlayerPickPhase(Dungeon *dungeon, Player *player)
            : IBattlePhaseHandler(dungeon, player) {}

        void handleEvent(const sf::Keyboard::Key &event, bool &exit) override;
        void render(sf::RenderWindow &window) override;
};

// Player attacks with selected skill
class PlayerAttackPhase: public IBattlePhaseHandler {
    public:
        PlayerAttackPhase(Dungeon *dungeon, Player *player)
            : IBattlePhaseHandler(dungeon, player) {}

        void handleEvent(const sf::Keyboard::Key &, bool &) override;
        void render(sf::RenderWindow &window) override;
};

// Opponent picks and attacks
class OpponentPickPhase: public IBattlePhaseHandler {
    public:
        OpponentPickPhase(Dungeon *dungeon, Player *player)
            : IBattlePhaseHandler(dungeon, player) {}

        void handleEvent(const sf::Keyboard::Key &, bool &) override;
        void render(sf::RenderWindow &) override;
};

// Opponent attacks the player
class OpponentAttackPhase: public IBattlePhaseHandler {
    public:
        OpponentAttackPhase(Dungeon *dungeon, Player *player)
            : IBattlePhaseHandler(dungeon, player) {}

        void update() override;
};

#include "Dungeon/Dungeon.hpp"