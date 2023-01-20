#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Piece.h"

class Game
{
private:
  Board* _board;
  void showPrompt() const;
  bool parsePieceId(const std::string& inputStr, char& pieceId);
  bool parseIdsAndCoordinate(const std::string& inputStr,
                             char& pieceId, int& configId, Coord& coord);
public:
  void init();
  int mainLoop();
};


#endif // GAME_H
