#ifndef BOARD_H
#define BOARD_H

#include "Types.h"

class Piece;

class Board
{
public:
  static bool isPlaceable(const Piece* piece, int orientation, const Coord& coord,
                          const BoardState& boardBefore, BoardState& boardAfter);
public:
  Board();
  void initFields();
  void initPieces();

  const std::map<Piece*, BoardPlacementEntry>& getPlacedPieces() const;
  const std::vector<Piece*>& getUnplacedPieces() const;

  void draw() const;
  void showAllPieces() const;
  void showPieceDetails(char pieceId) const;

  bool tryPlacePiece(Piece* piece, int orientation, const Coord& coord);
  bool removePlacedPiece(Piece* piece);
  bool solveGame();

private:
  bool solveRecursive(std::map<Piece*, std::vector<BoardPlacementEntry>> &remainingPossibilities);
  std::map<Piece*, std::vector<BoardPlacementEntry>>  getRemainingPlacementOptions(bool print=false) const;

private:
  int _numFreeFields{-1};
  int _numOccupiedFields{-1};
  int _numUnavailableFields{-1};
  BoardState _fields;

  std::map<Piece*, BoardPlacementEntry> _currPlacedPieces;
  std::vector<Piece*> _currUnplacedPieces;

  // only for statistics
  mutable long long _remainingBruteForceOptions{0};
  mutable long long _numRecursiveCalls{0};
};


#endif // BOARD_H
