#ifndef GAME_H
#define GAME_H

#include "Types.h"

class Board;

class Game
{
public:
  void init();
  int mainLoop();

private:
  void showPrompt() const;
  bool parsePieceId(const std::string& inputStr, char& pieceId);
  bool parseIdsAndCoordinate(const std::string& inputStr,
                             char& pieceId, int& configId, Coord& coord);

private:
  Board* _board;
};


#endif // GAME_H
