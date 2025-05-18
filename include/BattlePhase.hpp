#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Dungeon;

// Handler interface
struct IBattlePhaseHandler {
        virtual void handleEvent(Dungeon *dungeon, const sf::Event &, bool &) = 0;
        virtual void update(Dungeon *dungeon)                                 = 0;
        virtual void render(Dungeon *dungeon, sf::RenderWindow &, sf::Font &) = 0;
        virtual ~IBattlePhaseHandler() = default;
};

// Player selects a skill
struct PlayerPickPhase: IBattlePhaseHandler {
        void handleEvent(Dungeon *dungeon, const sf::Event &event,
                         bool &exit) override;
        void update(Dungeon *dungeon) override;
        void render(Dungeon *dungeon, sf::RenderWindow &window,
                    sf::Font &font) override;
};

// Player attacks with selected skill
struct PlayerAttackPhase: IBattlePhaseHandler {
        void handleEvent(Dungeon *dungeon, const sf::Event &, bool &) override;
        void update(Dungeon *dungeon) override;
        void render(Dungeon *dungeon, sf::RenderWindow &window,
                    sf::Font &font) override;
};

// Opponent picks and attacks
struct OpponentPickPhase: IBattlePhaseHandler {
        void handleEvent(Dungeon *dungeon, const sf::Event &, bool &) override;
        void update(Dungeon *dungeon) override;
        void render(Dungeon *dungeon, sf::RenderWindow &window,
                    sf::Font &font) override;
};

struct OpponentAttackPhase: IBattlePhaseHandler {
        void handleEvent(Dungeon *dungeon, const sf::Event &, bool &) override;
        void update(Dungeon *dungeon) override;
        void render(Dungeon *dungeon, sf::RenderWindow &window,
                    sf::Font &font) override;
};