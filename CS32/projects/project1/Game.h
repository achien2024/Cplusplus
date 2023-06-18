#ifndef Game_H
#define Game_H

#include <string>
class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;
    std::string takePlayerTurn();
};

#endif