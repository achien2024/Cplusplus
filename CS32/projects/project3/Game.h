#ifndef GAME
#define GAME
#include "Board.h"
#include "Player.h"
#include "Side.h"

class Game
{
    public:
        Game(const Board& b, Player* south, Player* north);
        void display() const;
        void status(bool& over, bool& hasWinner, Side& winner) const;
        bool move(Side s);
        void play();
        int beans(Side s, int hole) const;
    private:
        bool helpMove(int& chooseHole, Side current, Side opp, Side& endSide, int& endHole, Player* player);
        Board m_board;
        Player* s_player;
        Player* n_player;
};

#endif