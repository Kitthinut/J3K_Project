#pragma once

class Dungeon; // Forward declaration of the Dungeon class

#include <SFML/Graphics.hpp>
#include <string>

// Handler interface
struct IBattlePhaseHandler {
        virtual void handleEvent(Dungeon *, const sf::Event &, bool &) = 0;
        virtual void update(Dungeon *)                                 = 0;
        virtual void render(Dungeon *, sf::RenderWindow &)             = 0;
        virtual ~IBattlePhaseHandler()                                 = default;
};

// Player selects a skill
struct PlayerPickPhase: public IBattlePhaseHandler {
        void handleEvent(Dungeon *dungeon, const sf::Event &event,
                         bool &exit) override;
        void update(Dungeon *dungeon) override;
        void render(Dungeon *dungeon, sf::RenderWindow &window) override;
};

// Player attacks with selected skill
struct PlayerAttackPhase: public IBattlePhaseHandler {
        void handleEvent(Dungeon *dungeon, const sf::Event &, bool &) override;
        void update(Dungeon *dungeon) override;
        void render(Dungeon *dungeon, sf::RenderWindow &window) override;
};

// Opponent picks and attacks
struct OpponentPickPhase: public IBattlePhaseHandler {
        void handleEvent(Dungeon *, const sf::Event &, bool &) override;
        void update(Dungeon *) override;
        void render(Dungeon *, sf::RenderWindow &) override;

        virtual ~OpponentPickPhase() override {}
};

struct OpponentAttackPhase: public IBattlePhaseHandler {
        void handleEvent(Dungeon *dungeon, const sf::Event &, bool &) override;
        void update(Dungeon *dungeon) override;
        void render(Dungeon *dungeon, sf::RenderWindow &window) override;

        virtual ~OpponentAttackPhase() override {}
};

#include "Dungeon/Dungeon.hpp"