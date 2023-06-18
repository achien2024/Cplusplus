#include <iostream>
#include "Board.h"
#include "Side.h"
using namespace std;

// Aaron Chien
Board::Board(int nHoles, int nInitialBeansPerHole)
{
    // does not include pot
    // if nHoles is not positive, make m_holes 1, else make m_holes nHoles
    if (nHoles <= 0)
    {
        m_holes = 1;
    }
    else
    {
        m_holes = nHoles;
    }

    // if nInitialBeansPerHole is negative, make m_initialHoles  0
    if (nInitialBeansPerHole < 0)
    {
        m_initialBeans = 0;
    }
    else
    {
        m_initialBeans = nInitialBeansPerHole;
    }

    // initializing the pots 
    m_north.push_back(0);
    m_south.push_back(0);
    
    // adding in the beans for each hole 
    for (int i = 1; i <= m_holes; i++)
    {
        m_north.push_back(m_initialBeans);
        m_south.push_back(m_initialBeans);
    }
}

int Board::holes() const
{
    return m_holes;
}

int Board::beans(Side s, int hole) const
{
    // if the hole is invalidated, return -1
    if (hole > m_south.size() || hole > m_north.size() || hole < 0)
    {
        return -1;
    }
    else
    {
        vector<int>::const_iterator it;
        // create iterator
        // why do I need it to be const_iterator? Isn't that only for const containers? 
        int i = 0;
        // tracker for hole
        // point the iterator to either NORTH or SOUTH depending on s
        if (s == NORTH)
        {
            it = m_north.begin();
        }
        else
        {
            it = m_south.begin();
        }
        // increment the iterator until it hits hole
        while (i < hole)
        {
            it++;
            i++;
        }
        // dereference and return the iterator 
        return *it;
    }
}

int Board::beansInPlay(Side s) const
{
    // create iterator 
    vector<int>::const_iterator it;
    // set the number of beans to be returned to 0 
    int return_beans = 0;
    // if the side is NORTH or SOUTH, have the iterator point to the first hole, NOT the POT
        // then iterate through the vector, dereferencing each hole and adding it to the value to be returned 
        // advance the iterator 
    if (s == NORTH)
    {
        it = m_north.begin() + 1;
        while (it != m_north.end())
        {
            return_beans += *it;
            it++;
        }
    }
    else
    {
        it = m_south.begin() + 1;
        while (it != m_south.end())
        {
            return_beans += *it;
            it++;
        }
    }
    return return_beans;
}

int Board::totalBeans() const
{
    // create an iterator 
    vector<int>::const_iterator it;
    // first point it to the north vector
    it = m_north.begin();
    int return_totBeans = 0;
    // iterate through the vector, increasing return_totBeans for each hole you pass through
    while (it != m_north.end())
    {
        return_totBeans += *it;
        it++;
    }
    // then point the iterator to the south vector
    it = m_south.begin();
    // increase return_totBeans for each hole you pass through
    while (it != m_south.end())
    {
        return_totBeans += *it;
        it++;
    }

    return return_totBeans;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    if (hole <= 0 || hole > m_south.size() || hole > m_north.size())
    {
        return false;
    }
    int countRemains;
    // this is all fine 
    if (s == NORTH)
    {
        // take the total amount of beans in that hole 
        countRemains = m_north[hole];
        // set that hole to 0, everything is removed now 
        m_north[hole] = 0;
        helpSow(NORTH, SOUTH, hole - 1, countRemains - 1, endSide, endHole);
    }
    else if (s == SOUTH)
    {
        countRemains = m_south[hole];
        m_south[hole] = 0;
        helpSow(SOUTH, NORTH, hole + 1, countRemains - 1, endSide, endHole);
    }
    return true;
}

void Board::helpSow(Side s, Side opp, int hole, int remain, Side& endSide, int& endHole)
{
    // base case
    if (remain <= 0)
    {
        if (s == NORTH)
        {
            m_north[hole] += 1;
            // increase the last hole by one
            endSide = NORTH;
            endHole = hole;
            return;
            // set the right parameters
        }
        else if (s == SOUTH)
        {
            // if remain is 0 and we should be at the south pot
            if (hole > holes())
            {
                m_south[0] += 1;
                endSide = SOUTH;
                endHole = 0;
                return;
            }
            m_south[hole] += 1;
            endSide = SOUTH;
            endHole = hole;
            return;
        }
    }

    // increase hole, but check to make sure it is within vector, if not, take the s's 0 and increase it
    if (s == NORTH)
    {
        // on the north side, we are decrementing 
        // if the hole is lower than 0, move the incrementation to the south vector
        if (hole < 0 && remain != 0)
        {
            helpSow(SOUTH, opp, 1, remain, endSide, endHole);
        }
        else if (hole >= 0 && remain != 0)
        {
            // if the hole is at 0, this means that we might be adding to our own pot
            // if we are NORTH, if we are SOUTH, we do not touch this
            if (hole == 0 && opp != NORTH)
            {
                m_north[hole] += 1;
                remain--;
                // hole--;
                // if we are at the hole, it means we need to move to the south if it is not empty
                // we first check if remain is 0, then move to the south in the above if statement recursively
                helpSow(SOUTH, opp, 1, remain, endSide, endHole);
            }
            // hole is 0 and fails guard 
            else if (hole == 0)
            {
                helpSow(SOUTH, opp, 1, remain, endSide, endHole);
            }
            else
            {
                m_north[hole] += 1;
                remain--;
                hole--;
                helpSow(NORTH, opp, hole, remain, endSide, endHole);
            }
        }
    }
    else if (s == SOUTH)
    {
        // if the hole is greater than the entire number of holes for the south vector, move it to the north
        // south we are incrementing holes, we so check for pot in the case where the hole is greater than the number of holes 
        if (hole > holes() && remain != 0)
        {
            if (hole == holes() + 1 && opp != SOUTH)
            {
                m_south[0] += 1;
                remain--;
                // incrementing here so that it will not go down to previous holes in south 
                // hole++;

                // actually if there is still stuff remaining (0 would go to next hole), just go to the next vector
                helpSow(NORTH, opp, holes(), remain, endSide, endHole);
            }
            else if (hole == holes() + 1)
            {
                helpSow(NORTH, opp, holes(), remain, endSide, endHole);
            }
        }
        else if (hole <= holes() && remain != 0)
        {
            m_south[hole] += 1;
            remain--;
            hole++;
            helpSow(SOUTH, opp, hole, remain, endSide, endHole);
        }
    }
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    // I am assuming this function represents a capture 
    // testing for invalid holes
    // if it is negative, a pot, or greater than the size of vector 
    if (hole <= 0 || hole > m_south.size() || hole > m_north.size())
    {
        return false;
    }
    // if s is NORTH
    if (s == NORTH)
    {
        // if the hole's beans is 0, return false, else make SOUTH's hole increased by that value
        if (m_north[hole] != 0)
        {
            if (potOwner == NORTH)
            {
                m_north[0] += m_north[hole];
            }
            else if (potOwner == SOUTH)
            {
                m_south[0] += m_north[hole];
            }
            // empty the hole
            m_north[hole] = 0;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    // do the opposite 
    {
        if (m_south[hole] != 0)
        {
            if (potOwner == NORTH)
            {
                m_north[0] += m_south[hole];
            }
            else if (potOwner == SOUTH)
            {
                m_south[0] += m_south[hole];
            }
            m_south[hole] = 0;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
    if (hole < 0 || beans < 0 || hole > m_north.size())
    {
        return false;
    }
    if (s == NORTH)
    {
        m_north[hole] = beans;
    }
    if (s == SOUTH)
    {
        m_south[hole] = beans;
    }
    return true;
}