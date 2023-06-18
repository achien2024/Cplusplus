#include <iostream>
#include <climits>
#include "Player.h"
#include "Side.h"
#include "Game.h"
using namespace std;

// Aaron Chien
Player::Player(string name)
{
    m_name = name;
}

string Player::name() const
{
    return m_name;
}

bool Player::isInteractive() const
{
    return true;
}

Player::~Player(){}

// Human Player
HumanPlayer::HumanPlayer(string name):Player(name)
{

}

bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(s) == 0)
    {
        cout << name() << " has no beans left to sow." << endl;
        return -1;
    }
    else
    {
        int m_move;
        bool loop = true;
        while (loop)
        {
            cout << "Select a hole, " << name() << ": ";
            cin >> m_move;
            cin.ignore();
            
            if (m_move > b.holes() || m_move  <= 0)
            {
                // invalid move
                cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
            }
            else if (b.beans(s, m_move) == 0)
            {
                // no beans in that hole
                cout << "There are no beans in that hole." << endl;
            }
            else if (m_move <= b.holes() && m_move > 0)
            {
                // cout << "pass " << endl;
                // valid move 
                loop = false;
            }
        }
        return m_move;
    }
}

HumanPlayer::~HumanPlayer(){}

// Bad Player
BadPlayer::BadPlayer(string name):Player(name)
{

}

bool BadPlayer::isInteractive() const
{
    return false;
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(s) == 0)
    {
        cout << name() << " has no beans left to sow." << endl;
        return -1;
    }

    int m_move = -99;
    // initalize it so the warnings will go away
    // iterate through the side, and just pick the hole with something in it 
    for (int i = 1; i <= b.holes(); i++)
    {
        if (b.beans(s, i) > 0)
        {
            m_move = i;
            i = b.holes() + 1;
            // break out of loop once you find a valid hole
        }
    }
    cout << name() << " chooses hole " << m_move << endl;
    return m_move;
}

BadPlayer::~BadPlayer(){}

// Smart Player
SmartPlayer::SmartPlayer(string name):Player(name)
{
    // every move is a node
    // best score for picking an x 
    // what you can do is evaluate every possible move 
    // each move, give it a score to some value 0 if tie, +1 if you won, -1 if you lost 
    // best move for
    // max for you, min for opponent 

    // set heuristic first
    // then set recursion 

    // when doing the recursion
        // assign the node value with the heuristic 

}

bool SmartPlayer::isInteractive() const
{
    return false;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(s) == 0)
    {
        cout << name() << " has no beans left to sow." << endl;
        return -1;
    }
    else
    {
        double timeLimit = 4990;  // 4.99 seconds; allow 10 ms for wrapping up
        Timer timer;
        // do we need a player parameter 
        int bHole, cHole, bValue, cValue;
        cHole = -99;
        bValue = INT_MIN;
        // helpChooseMove(s, s, 1, b, cHole, cValue, bHole, bValue); //, timerLimit, timer;
        // helpChooseMove(s, s, 1, b, cHole, cValue, bHole, bValue, timeLimit, timer);
        helpChooseMove(s, s, b, cHole, cValue, bHole, bValue, timeLimit, timer);
        cout << name() << " chooses hole " << bHole << endl;
        return bHole;
    }
}

// this evaluation function will be called for the last leaf (fifth leaf)
// idea is to return the max value for the side 
int SmartPlayer::eval(Side s, const Board& b) const
{
    if (s == NORTH)
    {
        if (b.beansInPlay(NORTH) > 0 && b.beansInPlay(SOUTH) > 0)
        {
            return b.beans(NORTH, 0) - b.beans(SOUTH, 0);
        }
        else
        {
            if (b.beans(NORTH, 0) > b.beans(SOUTH, 0))
            {
                return INT_MAX;
            }
            else if (b.beans(NORTH, 0) < b.beans(SOUTH, 0))
            {
                return INT_MIN;
            }
            else if (b.beans(NORTH, 0) == b.beans(SOUTH, 0))
            {
                return 0;
            }
        }
    }
    else if (s == SOUTH)
    {
        if (b.beansInPlay(SOUTH) > 0 && b.beansInPlay(NORTH) > 0)
        {
            return b.beans(SOUTH, 0) - b.beans(NORTH, 0);
        }
        else
        {
            if (b.beans(SOUTH, 0) > b.beans(NORTH, 0))
            {
                return INT_MAX;
            }
            else if (b.beans(SOUTH, 0) < b.beans(NORTH, 0))
            {
                return INT_MIN;
            }
            else if (b.beans(SOUTH, 0) == b.beans(NORTH, 0))
            {
                return 0;
            }
        }        
    }
    // get rid of warning
    return -1;
}

void SmartPlayer::helpCheckCaptures(Side current, Side opp, Side& endSide, int& endHole, Board& b) const
{
    if (endHole != 0 && current == endSide && b.beans(current, endHole) == 1 && b.beans(opp, endHole) != 0)
    {
        b.moveToPot(opp, endHole, current);
        b.moveToPot(current, endHole, current);
    }
}

// void SmartPlayer::helpChooseMove(Side s, Side original, int depth, const Board& b, int currentHole, int& currentValue, int& bestHole, int bestValue, double timeLimit, Timer timer) const
void SmartPlayer::helpChooseMove(Side s, Side original, const Board& b, int currentHole, int& currentValue, int& bestHole, int bestValue, double timeLimit, Timer timer) const
//, timerLimit, timer
{
    // cout << "timer: " << timeLimit << endl;
    Side endSide, opp;
    int endHole;

    // make opposite sides for switching turns 
    if (s == NORTH)
    {
        opp = SOUTH;
    }
    else if (s == SOUTH)
    {
        opp = NORTH;
    }

    // the b will be passed in as a board copy of the original board 
    // determinats, setting up conditions
    // base cases
    // when the game is over
    if (b.beansInPlay(s) == 0)
    {
        Board endBoardCopy = b;
        for (int i = 1; i <= endBoardCopy.holes(); i++)
        {
            endBoardCopy.moveToPot(opp, i, opp);
        }
        currentValue = eval(original, endBoardCopy);
        return;
    }
    // when the time limit dits 
    if (timeLimit <= 0.003) 
    { 
        // cout << "timeLimit is " << timeLimit << endl;
        currentValue = eval(original, b);
        return;
    };

    // for every hole in the board
    for (int i = 1; i <= b.holes(); i++)
    {
        // check if the side can make a move 
        if (b.beans(s, i) > 0)
        {
            // start the time for checking moves recursively 
            double startTime = timer.elapsed();
            // timer.elapsed()
            // when you sow, make a copy of the original board for each stimulation
            Board copyBoard = b; 
            currentHole = i;
            // sow the board 
            copyBoard.sow(s, i, endSide, endHole);

            // check captures 
            helpCheckCaptures(s, opp, endSide, endHole, copyBoard); 
            // now let the opponent do its move

            // if we are currently the player, we want to maximize our winnings
            // so when we switch into the other player, we would be maxiziming from what they will choose
            // the value for best value is int min as that not a possible winning number from maximizing 

            timeLimit = timer.elapsed() - startTime;
            // cout << "amount of time reamining: " << timeLimit << endl;
            // if you sow again 
            if (endSide == s && endHole == 0)
            {
                helpChooseMove(s, original, copyBoard, currentHole, currentValue, bestHole, bestValue, timeLimit, timer);
            }
            if (original == s)
            {
                bestValue = INT_MIN;
                helpChooseMove(opp, original, copyBoard, currentHole, currentValue, bestHole, bestValue, timeLimit, timer);
                if (bestValue <= currentValue)
                {
                    bestValue = currentValue;
                    bestHole = currentHole;
                }
            }
            // if we are currently the opponent, we want to minimize our losses
            // so when we switch into the other player, we would see what they would do and take the minimum of winnings they can get
            // the minimum of their winnings is our maximum 
            else if (original != s)
            {
                bestValue = INT_MAX;
                helpChooseMove(opp, original, copyBoard, currentHole, currentValue, bestHole, bestValue, timeLimit, timer);
                if (bestValue >= currentValue)
                {
                    bestValue = currentValue;
                    bestHole = currentHole;
                }
            }
        }
    }
    return;
}

SmartPlayer::~SmartPlayer(){}






