// Aaron Chien
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    // base case
    if (sr == er && sc == ec)
    {
        return true;
    }

    // not visited before so mark it 'C'
    maze[sr][sc] = 'C';
    // going north
    if (maze[sr + 1][sc] == '.')
    {
        if (pathExists(maze, sr + 1, sc, er, ec))
        // same pattern as every other movement, if there's a path return true, and recursively call the function
        // if the path is 'X' or 'C', you would not pass through the function
        // the function simultaneously checks all paths since we use 'if', not 'if else'
        {
            return true;
        }
    }
    
    // going south 
    if (maze[sr - 1][sc] == '.')
    {
        if (pathExists(maze, sr - 1, sc, er, ec))
        {
            return true;
        }
    }
    // going east 
    if (maze[sr][sc + 1] == '.')
    {
        if (pathExists(maze, sr, sc + 1, er, ec))
        {
            return true;
        }
    }
    // going west
    if (maze[sr][sc - 1] == '.')
    {
        if (pathExists(maze, sr, sc - 1, er, ec))
        {
            return true;
        }
    }
    
    return false;
}