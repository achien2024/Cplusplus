#ifndef TESTNUM  // In case you haven't already defined the name TESTNUM
#define TESTNUM 6
#endif

#if TESTNUM == 1

#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doBoardTests()
{
	Board b(3, 2);
	assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
            b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
	b.setBeans(SOUTH, 1, 1);
	b.moveToPot(SOUTH, 2, SOUTH);
	assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
	        b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
	b.beansInPlay(SOUTH) == 3);
	Side es;
	int eh;
	b.sow(SOUTH, 3, es, eh);
	assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
	        b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
	b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
}

int main()
{
	doBoardTests();
	cout << "Passed all tests" << endl;
}

#elif TESTNUM == 2

#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    n = sp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
}

int main()
{
    doPlayerTests();
    cout << "Passed all tests" << endl;
}

#elif TESTNUM == 3

#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
        //    Homer
        //   0  1  2
        // 0         0
        //   2  0  0
        //    Bart
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
        //   0  1  0
        // 0         3
        //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(NORTH);
        //   1  0  0
        // 0         3
        //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
        //   1  0  0
        // 0         3
        //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

    cout << "move NORTH " << endl;
    g.move(NORTH);
        //   0  0  0
        // 1         4
        //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}

int main()
{
    doGameTests();
    cout << "Passed all tests" << endl;
}

#elif TESTNUM == 4

#include <iostream>
#include "Board.h"
#include "Side.h"
#include "Player.h"
#include "Game.h"

void SmartVsSmart()
{
    SmartPlayer south_side("Tamaya");
    SmartPlayer north_side("Chelsey");
    Board play_board(9, 5);
    Game playGame(play_board, &south_side, &north_side);
    playGame.play();
}

int main()
{
    SmartVsSmart();
}

#elif TESTNUM == 5

#include <iostream>
#include "Board.h"
#include "Side.h"
#include "Player.h"
#include "Game.h"

void SmartVsBad()
{
    SmartPlayer south_side("Tamaya");
    BadPlayer north_side("Bad");
    Board play_board(5, 10);
    Game smartGame(play_board, &south_side, &north_side);
    smartGame.play();
}

int main()
{
    SmartVsBad();
}

#elif TESTNUM == 6

#include <iostream>
#include "Board.h"
#include "Side.h"
#include "Player.h"
#include "Game.h"

void SmartVsHuman()
{
    HumanPlayer south_side("Human");
    SmartPlayer north_side("AI");
    Board play_board(5, 5);
    Game lonely(play_board, &north_side, &south_side);
    lonely.play();
}

int main()
{
    SmartVsHuman();
}

#elif TESTNUM == 7 // use original main.cpp

#include "Game.h"

#include <iostream>
#include "Board.h"
#include "Side.h"
#include "Player.h"
#include "Game.h"

void SmartVsDumb()
{
    HumanPlayer north_side("Human");
    BadPlayer south_side("AI");
    Board play_board(5, 5);
    Game lonelyD(play_board, &south_side, &north_side);
    lonelyD.play();
}

int main()
{
    SmartVsDumb();
}

# else 

#include "Game.h"

#include <iostream>
#include "Board.h"
#include "Side.h"
#include "Player.h"
#include "Game.h"

void ChelVsTam()
{
    SmartPlayer south_side("Chelsey");
    BadPlayer north_side("Tamaya");
    Board play_board(6, 2);
    play_board.setBeans(NORTH, 1, 1);
    play_board.setBeans(NORTH, 2, 0);
    play_board.setBeans(SOUTH, 1, 4);
    play_board.setBeans(SOUTH, 2, 1);
    Game finalGame(play_board, &south_side, &north_side);
    finalGame.play();
}

int main()
{
    ChelVsTam();
}
#endif