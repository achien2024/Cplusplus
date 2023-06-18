#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"
class History
{
    public:
        History(int nRows, int nCols);
        // use the constructor and have it in a shape
        // take the oibject and set it in the way you want it 
        bool record(int r, int c);
        void display() const;
    
    private:
        char    m_grid[MAXROWS][MAXCOLS];
        // create grid of chars
        // these will be '.' soon
        int     m_rows;
        int     m_cols;
};

#endif