#ifndef BOARD_H
#define BOARD_H

#include "Types.h"

class Piece;

class Board
{
private:
  int _numFreeFields{-1};
  int _numOccupiedFields{-1};
  int _numUnavailableFields{-1};
  BoardState _fields;

  std::map<Piece*, BoardPlacementEntry> _currPlacedPieces;
  std::vector<Piece*> _currUnplacedPieces;

  // recursive function
  bool solveBoard(std::map<Piece*, std::vector<BoardPlacementEntry>> &remainingPossibilities);
public:
  static bool isPlaceable(Piece* piece, int configuration, const Coord& coord,
                          const BoardState& boardBefore, BoardState& boardAfter);
public:
  Board();
  const std::map<Piece*, BoardPlacementEntry> getPlacedPieces() const;
  const std::vector<Piece*> getUnplacedPieces() const;

  void initFields();
  void initPieces();
  void draw() const;
  bool allFieldsOccupied() const;
  void showAllPieces();
  void showPieceDetails(char pieceId);

  bool tryPlacePiece(Piece* piece, int configuration, const Coord& coord);
  std::pair<bool, BoardPlacementEntry> tryPlacePieceAnywhere(Piece* piece);
  bool removePlacedPiece(Piece* piece);
  bool findPlacementForAll();
};


#endif // BOARD_H
