#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Side.h"
#include "Game.h"
using namespace std;
// Aaron Chien

Game::Game(const Board& b, Player* south, Player* north): m_board(b), s_player(south), n_player(north)
{
}

void Game::display() const
{
    // display the north's player name
    cout << "\t\t" << n_player->name() << endl;

    // create an iterator to iterate the number of holes we should output
    int n_holes = m_board.holes();

    // output the number of beans in each hole
    for (int i = 1; i <= n_holes; i++)
    {
        cout << "\t" << m_board.beans(NORTH, i);
    }

    // make a new line to display the north side pot
    cout << endl;

    // displaying the north pot
    cout << m_board.beans(NORTH, 0);

    // tabbing it down to make space for south po t
    for (int i = 1; i <= n_holes; i++)
    {
        cout << "\t";
    }

    // display the south pot
    cout << "\t" << m_board.beans(SOUTH, 0) << endl;

    // display the holes for the south side 
    for (int i = 1; i <= n_holes; i++)
    {
        cout << "\t" << m_board.beans(SOUTH, i);
    }

    // make a new line for make space for the south player
    cout << endl;

    // display the south player 
    cout << "\t\t" << s_player->name() << endl;
}

// 
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{

    // if there are still beans in the game, return false 
    if (m_board.beansInPlay(NORTH) > 0 && m_board.beansInPlay(SOUTH) > 0)
    {
        over = false;
        return;
    }

    // if the north wins
    if (m_board.beans(NORTH, 0) > m_board.beans(SOUTH, 0))
    {
        over = true;
        hasWinner = true;
        winner = NORTH;
        return;
    }
    
    // if the south wins
    if (m_board.beans(SOUTH, 0) > m_board.beans(NORTH, 0))
    {
        over = true;
        hasWinner = true;
        winner = SOUTH;
        return;
    }

    // if there is a tie 
    if (m_board.beans(SOUTH, 0) == m_board.beans(NORTH, 0))
    {
        over = true;
        hasWinner = false;
    }
}

bool Game::helpMove(int& chooseHole, Side current, Side opp, Side& endSide, int& endHole, Player* player)
{
    if (chooseHole == -1)
    {
        if (opp == SOUTH)
        {
            cout << "Sweeping remaining holes into " << s_player->name() << "'s pot" << endl;
            for (int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(opp, i, opp);
            }
            cout << "End of game results: " << endl;
            // display();
            return false;
        }
        else if (opp == NORTH)
        {
            cout << "Sweeping remaining holes into " << n_player->name() << "'s pot" << endl;
            for (int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(opp, i, opp);
            }
            cout << "End of game results: " << endl;
            // display();
            return false;
        }
    }
    // 2. if we are in the case of a capture, your turn would end
    // check to make sure the bean was last placed into our side
    // check to make sure the bean in that hole is 1 aka it was empty before
    // and check the oppsing side for the hole 
    // move the beans in the opposing hole if not empty into your own pot and end the turn 
    
    if (endHole != 0 && current == endSide && m_board.beans(current, endHole) == 1 && m_board.beans(opp, endHole) != 0)
    {
        m_board.moveToPot(opp, endHole, current);
        m_board.moveToPot(current, endHole, current);
        cout << "A capture has occured!" << endl;
        // display();
        return true;
    }
    // 1.
    // as long as you do not end in your own pot, you do not take another turn
    // return true and end the turn
    if (endHole == 0 && endSide == current)
    {
        display();
        cout << player->name() << " gets another turn." << endl;
        chooseHole = player->chooseMove(m_board, current);
        m_board.sow(current, chooseHole, endSide, endHole);
        // display();
        return helpMove(chooseHole, current, opp, endSide, endHole, player);
    }

    return true;
}

bool Game::move(Side s)
{
    // prep the proper data variables we would need for the move function
    Side endSide;
    int endHole;
    int choose_hole;
    // display();
    if (s == NORTH)
    // if we are choosing NORTH, it means we would have NORTH's side complete a turn
    { 
        // display();
        // first make a move 
        choose_hole = n_player->chooseMove(m_board, NORTH);
        // return helpMove(choose_hole, NORTH, SOUTH, endSide, endHole, n_player);
        // chooseMove ensures you choose a valid hole by checking the board
        if (choose_hole == -1)
        {
            cout << "Sweeping remaining holes into " << s_player->name() << "'s pot" << endl;
            for (int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(SOUTH, i, SOUTH);
            }
            cout << "End of game results: " << endl;
            return false;
        }
        else 
        {
            m_board.sow(NORTH, choose_hole, endSide, endHole);
            // this first move should always be valid 
            return helpMove(choose_hole, NORTH, SOUTH, endSide, endHole, n_player);
        }
    }
    else if (s == SOUTH)
    {
        // first move
        choose_hole = s_player->chooseMove(m_board, SOUTH);
        // return helpMove(choose_hole, SOUTH, NORTH, endSide, endHole, s_player);
        if (choose_hole == -1)
        {
            cout << "Sweeping remaining holes into " << n_player->name() << "'s pot" << endl;
            for (int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(NORTH, i, NORTH);
            }
            cout << "End of game results: " << endl;
            // display();
            return false;
        }
        else 
        {
            m_board.sow(SOUTH, choose_hole, endSide, endHole);
            // this first move should always be valid 
            return helpMove(choose_hole, SOUTH, NORTH, endSide, endHole, s_player);
        }
        // m_board.sow(SOUTH, choose_hole, endSide, endHole);
        // return helpMove(choose_hole, SOUTH, NORTH, endSide, endHole, s_player);  
    }
    // get rid of warning
    return false;
}

void Game::play()
{
    // setting up gameplay
    bool over = false;
    bool hasWinner = false;
    Side winner;

    // set interaction
    bool pressEnter = false;
    if (!n_player->isInteractive() && !s_player->isInteractive())
    {
        pressEnter = true;
    }

    // now we play
    display();
    bool moveStatus;
    while (!over)
    {
        // display();
        // move(SOUTH);
        // display();
        // move(NORTH);
        moveStatus = move(SOUTH);
        display();
        if (!moveStatus)
        {
            status(over, hasWinner, winner);
        }
        // if (!move(NORTH))
        // {
        //     cout << "passed North fail" << endl;
        //     status(over, hasWinner, winner);
        // }
        //status(over, hasWinner, winner);
        if (pressEnter)
        {
            std::cout << "Press ENTER to continue ";
            std::cin.ignore();
        }

        moveStatus = move(NORTH);
        display();
        if (!moveStatus)
        {
            status(over, hasWinner, winner);
        }
        
        if (pressEnter)
        {
            std::cout << "Press ENTER to continue ";
            std::cin.ignore();
        }
    }

    // after the game is over, if there is a winner...
    if (hasWinner)
    {
        std::string winner_name;
        if (winner == NORTH)
        {
            winner_name = n_player->name();
        }
        else if (winner == SOUTH)
        {
            winner_name = s_player->name();
        }
        std::cout << "The winner is " << winner_name << "." << std::endl;
    }
    else
    {
        std::cout << "The game resulted in a tie." << std::endl;
    }

}

int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}