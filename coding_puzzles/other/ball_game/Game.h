#ifndef GAME_H
#define GAME_H

#include "Types.h"
#include <iostream>

class Board;

class Game
{
public:
  void init();
  int mainLoop(string localFile = "");

private:
  void showPrompt() const;
  bool parsePieceId(const std::string& inputStr, char& pieceId);
  bool parseIdsAndCoordinate(const std::string& inputStr,
                             char& pieceId, int& orientationId, Coord& coord);

private:
  Board* _board;
};


#endif // GAME_H
