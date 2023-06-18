#ifndef PLAYER
#define PLAYER
#include "Board.h"
#include "Side.h"
#include <string>
#include <vector>
#include <chrono>
// Aaron Chien

class Player
{
    public:
        Player(std::string name);
        std::string name() const;
        virtual bool isInteractive() const;
        virtual int chooseMove(const Board& b, Side s) const = 0;
        virtual ~Player();
    private:
        std::string m_name;
};

class HumanPlayer: public Player
{
    public:
        HumanPlayer(std::string name);
        virtual ~HumanPlayer();
        virtual bool isInteractive() const;
        virtual int chooseMove(const Board& b, Side s) const;
};

class BadPlayer: public Player
{
    public:
        BadPlayer(std::string name);
        virtual ~BadPlayer();
        virtual bool isInteractive() const;
        virtual int chooseMove(const Board& b, Side s) const;
};

class Timer;
class SmartPlayer: public Player
{
    public:
        SmartPlayer(std::string name);
        virtual ~SmartPlayer();
        virtual bool isInteractive() const;
        virtual int chooseMove(const Board& b, Side s) const;
        // check if you can make a move first
        // if depth == 5 return evaluate at each possible move 
        // create a new board object that is a copy of b 
        // sow it and evaluate the board 
        
        // currentMax = INT_MIN
        // loop through each hole and call the function :)
        // for (int i = 1; i <= holes(); i++)
            // first check if you can make a valid move
            // create new board object that is copy of b
            // sow the move
            // compare chooseMove(newb, side not s) to current max
                // if bigger or equal store i into current max, iterate through again 
                // if it returns 0, INT_MIN, or INT_MAX, return that value and stop function
                // else return the function again (and increment depth as well)
            // pass chooseMove(newb, side not s), store this into current max
        
        // return i


    private:
        // void helpChooseMove(Side s, Side original, int depth, const Board& b, int currentHole, int& currentValue, int& bestHole, int bestValue) const;
        // void helpChooseMove(Side s, Side original, int depth, const Board& b, int currentHole, int& currentValue, int& bestHole, int bestValue, double timeLimit, Timer timer) const;
        void helpChooseMove(Side s, Side original, const Board& b, int currentHole, int& currentValue, int& bestHole, int bestValue, double timeLimit, Timer timer) const;
        // void helpChooseMove(Side s, const Board& b, int& bestHole, int& value, int depth, Side original) const;
        void helpCheckCaptures(Side current, Side opp, Side& endSide, int& endHole, Board& b) const;
            // have extra parameter called depth
        int eval(Side s, const Board& b) const;
        // evaluation function here
        // takes in a side to evaluate which side it is on 
        // and a position to examine
        // void helpEval(Side current, Side& endSide, int& endHole, Board& b, int sowHole) const;
        // minimax algorithmn here
        // tree structure here 
};

class Timer
{
  public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {   
        std::chrono::duration<double, std::milli> diff =
                          std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
  private:
    std::chrono::high_resolution_clock::time_point m_time;
};

#endif