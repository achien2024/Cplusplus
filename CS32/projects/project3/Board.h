#ifndef BOARD
#define BOARD
#include "Side.h"
#include <vector>
// Aaron Chien 
class Board
{
    public: 
        Board(int nHoles, int nInitialBeansPerHole);
        int holes() const;
        int beans(Side s, int hole) const;
        int beansInPlay(Side s) const;
        int totalBeans() const;
        bool sow(Side s, int hole, Side& endSide, int& endHole);
        // recursive helper function for sow
        bool moveToPot(Side s, int hole, Side potOwner);
        bool setBeans(Side s, int hole, int beans);
    private:
        void helpSow(Side s, Side opp, int hole, int remain, Side& endSide, int &endHole);
        int m_holes;
        int m_initialBeans;
        std::vector <int> m_north;
        std::vector <int> m_south;
};

#endif