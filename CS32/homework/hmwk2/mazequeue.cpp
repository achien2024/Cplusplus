#include <iostream>
#include <queue>
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
    queue<Coord> coordQueue;
    maze[sr][sc] = 'C';
    coordQueue.push(Coord(sr, sc));
    while (!coordQueue.empty())
    {
        Coord point = coordQueue.front();
        coordQueue.pop();
        if (point.c() == ec && point.r() == er)
        {
            return true;
        }
        int cp = point.c();
        int rp = point.r();
        if (maze[rp + 1][cp] != 'X' && maze[rp + 1][cp] != 'C')
        // checking south
        {
            coordQueue.push(Coord(rp + 1, cp));
            maze[rp + 1][cp] = 'C';
        }
        if (maze[rp][cp + 1] != 'X' && maze[rp][cp + 1] != 'C')
        // checking east 
        {
            coordQueue.push(Coord(rp, cp + 1));
            maze[rp][cp + 1] = 'C';
        }
        if (maze[rp -  1][cp] != 'X' && maze[rp - 1][cp] != 'C')
        // checking north
        {
            coordQueue.push(Coord(rp - 1, cp));
            maze[rp - 1][cp] = 'C';
        }
        if (maze[rp][cp - 1] != 'X' && maze[rp][cp - 1] != 'C')
        // checking west
        {
            coordQueue.push(Coord(rp, cp - 1));
            maze[rp][cp - 1] = 'C';
        }
    }
    return false;
}

int main()
        {
            char maze[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X' },
                { 'X','.','.','.','X','.','.','.','.','X' },
                { 'X','.','.','X','X','.','X','X','.','X' },
                { 'X','.','X','.','.','.','.','X','X','X' },
                { 'X','X','X','X','.','X','X','X','.','X' },
                { 'X','.','.','X','.','.','.','X','.','X' },
                { 'X','.','.','X','.','X','.','.','.','X' },
                { 'X','X','.','X','.','X','X','X','X','X' },
                { 'X','.','.','.','.','.','.','.','.','X' },
                { 'X','X','X','X','X','X','X','X','X','X' }
            };

            if (pathExists(maze, 3,4, 8,1))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;

            char maze1[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X' },
                { 'X','.','.','x','.','.','.','.','.','X' },
                { 'X','.','.','x','.','.','.','.','.','X' },
                { 'X','.','.','x','.','.','.','.','.','X' },
                { 'X','.','.','x','.','.','.','.','.','X' },
                { 'X','.','.','x','.','.','.','.','.','X' },
                { 'X','.','.','x','.','.','.','.','.','X' },
                { 'X','.','.','x','.','.','.','.','.','X' },
                { 'X','.','.','x','.','.','.','.','.','X' },
                { 'X','X','X','X','X','X','X','X','X','X' }
            };

            assert (!pathExists(maze1, 3,4, 8,1));

            char maze2[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X'},
                { 'X','.','.','.','.','.','.','.','.','X'},
                { 'X','X','.','X','.','X','X','X','X','X'},
                { 'X','.','.','X','.','X','.','.','.','X'},
                { 'X','.','.','X','.','.','.','X','.','X'},
                { 'X','X','X','X','.','X','X','X','.','X'},
                { 'X','.','.','X','.','.','.','X','X','X'},
                { 'X','.','.','X','X','.','X','X','.','X'},
                { 'X','.','.','.','X','.','.','.','.','X'},
                { 'X','X','X','X','X','X','X','X','X','X'}
            };

            assert(pathExists(maze2, 6,4, 1,1));
            char maze3[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X'},
                { 'X','.','X','.','.','X','.','.','.','X'},
                { 'X','.','X','X','.','X','.','X','X','X'},
                { 'X','.','.','.','.','X','.','X','.','X'},
                { 'X','X','.','X','.','X','.','.','.','X'},
                { 'X','X','X','.','.','X','.','X','.','X'},
                { 'X','.','.','.','X','.','.','.','X','X'},
                { 'X','.','X','X','.','.','X','.','X','X'},
                { 'X','.','.','.','.','X','.','.','.','X'},
                { 'X','X','X','X','X','X','X','X','X','X'}
            };
            assert(pathExists(maze3, 8, 6, 1, 1));
            char maze4[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X'},
                { 'X','.','X','.','.','X','.','.','.','X'},
                { 'X','X','X','X','.','X','.','X','X','X'},
                { 'X','.','.','.','.','X','.','X','.','X'},
                { 'X','X','.','X','.','X','.','.','.','X'},
                { 'X','X','X','.','.','X','.','X','.','X'},
                { 'X','.','.','.','X','.','.','.','X','X'},
                { 'X','.','X','X','.','.','X','.','X','X'},
                { 'X','.','.','.','.','X','.','.','.','X'},
                { 'X','X','X','X','X','X','X','X','X','X'}

            };
            assert(!pathExists(maze4, 8, 6, 1, 1));
            char maze5[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X'},
                { 'X','X','.','.','.','.','.','X','X','X'},
                { 'X','.','.','X','X','.','.','.','.','X'},
                { 'X','.','.','.','X','.','.','.','X','X'},
                { 'X','.','X','.','X','X','X','.','.','X'},
                { 'X','X','X','X','.','.','X','.','.','X'},
                { 'X','X','.','.','.','.','X','.','.','X'},
                { 'X','.','.','.','.','.','.','.','X','X'},
                { 'X','.','.','X','X','X','X','X','X','X'},
                { 'X','X','X','X','X','X','X','X','X','X'}

            };
            assert(pathExists(maze5, 4, 3, 7, 1));
            char maze6[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X'},
                { 'X','X','.','.','.','.','.','X','X','X'},
                { 'X','.','.','X','X','.','.','.','.','X'},
                { 'X','.','.','.','X','.','.','.','X','X'},
                { 'X','.','X','.','X','X','X','.','.','X'},
                { 'X','X','X','X','.','.','X','.','.','X'},
                { 'X','X','.','.','.','.','X','.','.','X'},
                { 'X','.','X','.','.','.','.','.','X','X'},
                { 'X','.','.','X','X','X','X','X','X','X'},
                { 'X','X','X','X','X','X','X','X','X','X'}
            };
            assert(!pathExists(maze6, 4, 3, 7, 1));
        

            char maze7[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X'},
                { 'X','.','.','X','.','.','.','X','X','X'},
                { 'X','X','.','X','X','.','.','.','.','X'},
                { 'X','X','.','.','X','.','.','.','X','X'},
                { 'X','X','.','X','X','X','X','.','.','X'},
                { 'X','X','.','X','.','.','X','.','.','X'},
                { 'X','X','.','.','.','.','X','.','.','X'},
                { 'X','.','X','.','.','.','.','.','X','X'},
                { 'X','.','.','X','X','X','X','X','X','X'},
                { 'X','X','X','X','X','X','X','X','X','X'}
            };
            assert(pathExists(maze7, 1, 1, 3, 3));
           

            char maze8[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X'},
                { 'X','.','.','X','.','.','.','X','X','X'},
                { 'X','X','.','X','X','.','.','.','.','X'},
                { 'X','X','.','.','X','.','.','.','X','X'},
                { 'X','X','.','X','X','X','X','.','.','X'},
                { 'X','X','.','X','.','.','X','.','.','X'},
                { 'X','X','.','.','.','.','X','.','.','X'},
                { 'X','.','X','.','.','.','.','.','X','X'},
                { 'X','.','.','X','X','X','X','X','X','X'},
                { 'X','X','X','X','X','X','X','X','X','X'}
            };
            assert(pathExists(maze8, 1, 1, 1, 4));
            

            char maze9[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X'},
                { 'X','.','.','X','.','.','.','X','X','X'},
                { 'X','X','.','X','X','.','.','.','.','X'},
                { 'X','X','.','.','X','.','.','.','X','X'},
                { 'X','X','.','X','X','X','X','.','.','X'},
                { 'X','X','.','X','.','.','X','.','.','X'},
                { 'X','X','.','.','.','.','X','.','.','X'},
                { 'X','.','X','.','.','.','X','.','X','X'},
                { 'X','.','.','X','X','X','X','X','X','X'},
                { 'X','X','X','X','X','X','X','X','X','X'}
            };
            assert(!pathExists(maze9, 1, 1, 1, 4));

            char maze10[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X'},
                { 'X','.','.','X','.','.','.','X','X','X'},
                { 'X','X','.','X','X','.','.','.','.','X'},
                { 'X','X','.','.','X','.','.','.','X','X'},
                { 'X','X','.','X','X','X','X','X','.','X'},
                { 'X','X','.','X','.','.','X','.','.','X'},
                { 'X','X','.','.','.','.','X','.','.','X'},
                { 'X','.','X','.','.','.','.','.','X','X'},
                { 'X','.','.','X','X','X','X','X','X','X'},
                { 'X','X','X','X','X','X','X','X','X','X'}
            };
            assert(pathExists(maze10, 1, 1, 4, 8));
            cerr << "pass all test!" << endl;
    
            char maze11[10][10] = {
                  { 'X','X','X','X','X','X','X','X','X','X' },
                  { 'X','.','X','.','.','X','.','.','.','X' },
                  { 'X','.','X','X','.','X','.','X','X','X' },
                  { 'X','.','.','.','.','X','.','X','.','X' },
                  { 'X','X','.','X','.','X','.','.','.','X' },
                  { 'X','X','X','.','.','X','.','X','.','X' },
                  { 'X','.','.','.','X','.','.','.','X','X' },
                  { 'X','.','X','X','.','.','X','.','X','X' },
                  { 'X','.','.','.','.','X','.','.','.','X' },
                  { 'X','X','X','X','X','X','X','X','X','X' },
                };
                
                char maze12[10][10] = {
                  { 'X','X','X','X','X','X','X','X','X','X' },
                  { 'X','.','X','.','.','X','.','.','.','X' },
                  { 'X','X','X','X','.','X','.','X','X','X' },
                  { 'X','.','.','.','.','X','.','X','.','X' },
                  { 'X','X','.','X','.','X','.','.','.','X' },
                  { 'X','X','X','.','.','X','.','X','.','X' },
                  { 'X','.','.','.','X','.','.','.','X','X' },
                  { 'X','.','X','X','.','.','X','.','X','X' },
                  { 'X','.','.','.','.','X','.','.','.','X' },
                  { 'X','X','X','X','X','X','X','X','X','X' },
                };
                
                char maze13[10][10] = {
                  { 'X','X','X','X','X','X','X','X','X','X' },
                  { 'X','X','.','.','.','.','.','X','X','X' },
                  { 'X','.','.','X','X','.','.','.','.','X' },
                  { 'X','.','.','.','X','.','.','.','X','X' },
                  { 'X','.','X','.','X','X','X','.','.','X' },
                  { 'X','X','X','X','.','.','X','.','.','X' },
                  { 'X','X','.','.','.','.','X','.','.','X' },
                  { 'X','.','.','.','.','.','.','.','X','X' },
                  { 'X','.','.','X','X','X','X','X','X','X' },
                  { 'X','X','X','X','X','X','X','X','X','X' },
                };
                
                char maze14[10][10] = {
                  { 'X','X','X','X','X','X','X','X','X','X' },
                  { 'X','X','.','.','.','.','.','X','X','X' },
                  { 'X','.','.','X','X','.','.','.','.','X' },
                  { 'X','.','.','.','X','.','.','.','X','X' },
                  { 'X','.','X','.','X','X','X','.','.','X' },
                  { 'X','X','X','X','.','.','X','.','.','X' },
                  { 'X','X','.','.','.','.','X','.','.','X' },
                  { 'X','.','X','.','.','.','.','.','X','X' },
                  { 'X','.','.','X','X','X','X','X','X','X' },
                  { 'X','X','X','X','X','X','X','X','X','X' },
                };

                assert(pathExists(maze11, 8, 6, 1, 1));
                assert(!pathExists(maze12, 8, 6, 1, 1));
                assert(pathExists(maze13, 4, 3, 7, 1));
                assert(!pathExists(maze14, 4, 3, 7, 1));
    }
