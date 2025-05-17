#pragma once

class Dungeon {
public:
    enum Turn { Player, Opponent };
    Dungeon();
    void startTurn();
    void endTurn();
    Turn getCurrentTurn() const;
    void reset();
private:
    Turn currentTurn;
};