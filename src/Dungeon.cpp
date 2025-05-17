#include "Dungeon.hpp"

Dungeon::Dungeon() : currentTurn(Player) {}

void Dungeon::startTurn() {
    // Logic for starting a turn (if needed)
}

void Dungeon::endTurn() {
    // Switch turn
    if (currentTurn == Player)
        currentTurn = Opponent;
    else
        currentTurn = Player;
}

Dungeon::Turn Dungeon::getCurrentTurn() const {
    return currentTurn;
}

void Dungeon::reset() {
    currentTurn = Player;
}