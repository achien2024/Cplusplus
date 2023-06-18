#include <iostream>
using namespace std;
#include "History.h"

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int r = 1; r <= m_rows; r++)
    // iterate through the rows
    {
        for (int c = 1; c <= m_cols; c++)
        // iterate through the columns
        {
            m_grid[r-1][c-1] = '.';
            // replace the random grid with char values of '.'
        }
    }
}

bool History::record(int r, int c)
{
    // notifies the history object that a rabbit has started its turn poisoned but alive
    // when a rabbit starts to become poisoned, the rabbit is poisoned
    // outputs a grid for each cell
    // called for each rabbit if it's posioned
    // check if it's 0 or less too 
    if (r <= 0  ||  c <= 0  ||  r > m_rows ||  c > m_cols)
    // checking boundaries, if violated, return false
    {
        return false;
    } else
    {
        if (m_grid[r-1][c-1] == '.')
        {
            m_grid[r-1][c-1] = 'A';
            // if it is the first time running if the rabbit is poisioned, make it A
        } 
        else if (m_grid[r-1][c-1] == 'Z')
        { // do not change it
        } 
        else
        {
            m_grid[r-1][c-1]++;
            // each point is technically a ASCII character, so we can just increment it like such to go through the alphabet
        }
        return true;
    }
}

void History::display() const
{
    clearScreen();
    for (int i = 0; i < m_rows; i++)
    {
        for (int n = 0; n < m_cols; n++)
        {
            cout << m_grid[i][n];
        }
        cout << endl;
    }

    cout << endl;
}