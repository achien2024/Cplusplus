#include <iostream>
#include <stack>
using namespace std;

class Coord
{
    public:
        Coord(int rr, int cc): m_r(rr), m_c(cc) {}
        int r() const
        {
            return m_r;
        }
        int c() const
        {
            return m_c;
        }
    private:
        int m_r;
        int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    maze[sr][sc] = 'C';
    coordStack.push(Coord(sr, sc));
    while (!coordStack.empty())
    {
        Coord point = coordStack.top();
        coordStack.pop();
        if (point.c() == ec && point.r() == er)
        {
            return true;
        }
        int cp = point.c();
        int rp = point.r();
        if (maze[rp + 1][cp] != 'X' && maze[rp + 1][cp] != 'C')
        // checking south
        {
            coordStack.push(Coord(rp + 1, cp));
            maze[rp + 1][cp] = 'C';
        }
        if (maze[rp][cp + 1] != 'X' && maze[rp][cp + 1] != 'C')
        // checking east 
        {
            coordStack.push(Coord(rp, cp + 1));
            maze[rp][cp + 1] = 'C';
        }
        if (maze[rp -  1][cp] != 'X' && maze[rp - 1][cp] != 'C')
        // checking north
        {
            coordStack.push(Coord(rp - 1, cp));
            maze[rp - 1][cp] = 'C';
        }
        if (maze[rp][cp - 1] != 'X' && maze[rp][cp - 1] != 'C')
        // checking west
        {
            coordStack.push(Coord(rp, cp - 1));
            maze[rp][cp - 1] = 'C';
        }
    }
    return false;
}

int main()
{
    char maze[10][10] = {
        // 0   1   2   3   4   5   6   7   8   9 
        { 'X','X','X','X','X','X','X','X','X','X' }, // 0
        { 'X','.','.','.','X','.','.','.','.','X' }, // 1
        { 'X','.','.','X','X','.','X','X','.','X' }, // 2
        { 'X','.','X','.','.','.','.','X','X','X' }, // 3
        { 'X','X','X','X','.','X','X','X','.','X' }, // 4
        { 'X','.','.','X','.','.','.','X','.','X' }, // 5
        { 'X','.','.','X','.','X','.','.','.','X' }, // 6
        { 'X','X','.','X','.','X','X','X','X','X' }, // 7
        { 'X','.','.','.','.','.','.','.','.','X' }, // 8
        { 'X','X','X','X','X','X','X','X','X','X' }  // 9
    };

    if (pathExists(maze, 3,4, 8,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}