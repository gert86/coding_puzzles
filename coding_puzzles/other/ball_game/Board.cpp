#include "Board.h"
#include "Piece.h"

bool Board::isPlaceable(Piece *piece, int orientation, const Coord &coord, const BoardState &boardBefore, BoardState &boardAfter)
{
  auto boardDirty = boardBefore;

  auto geometry = piece->getGeometryOrientations()[orientation];
  for (const auto& localCoord : geometry) {
    auto x = localCoord.x + coord.x;
    auto y = localCoord.y + coord.y;
    if ((int)boardBefore.size() <= y || (int)boardBefore[y].size() <= x || boardBefore[y][x] != FIELD_EMPTY_ID) {
      return false;
    }
    else {
      boardDirty[y][x] = piece->id();
    }
  }

  boardAfter = boardDirty;  // only on success, boardAfter will be updated
  return true;
}

Board::Board()
{
  initFields();
  initPieces();
}

void Board::initFields()
{
  _numFreeFields = 0;
  _numOccupiedFields = 0;
  _numUnavailableFields = 0;
  _fields.clear();

  auto column = std::vector<char>(9, FIELD_EMPTY_ID);
  _fields = BoardState(9, column);

  // Picaso couldn't have made it better
  std::vector<Coord> unavailableCoords = {                                    {6,0},{7,0},{8,0},
                                                                                    {7,1},{8,1},
                                                                                          {8,2},
                                                      {2,3},

                                                                                    {7,5},{8,5},
                                          {0,6},                              {6,6},{7,6},{8,6},
                                          {0,7},{1,7},                  {5,7},{6,7},{7,7},{8,7},
                                          {0,8},{1,8},{2,8},            {5,8},{6,8},{7,8},{8,8}
                                         };
  for (const auto &[x, y] : unavailableCoords) {
    _fields[y][x] = FIELD_UNAVAILABLE_ID;  // y=row, x=column
  }

  for (const auto& column : _fields) {
    for (const auto& field : column) {
      if (field == FIELD_EMPTY_ID) {
        _numFreeFields++;
      }
      else if (field == FIELD_UNAVAILABLE_ID) {
        _numUnavailableFields++;
      }
      else {
        _numOccupiedFields++;
      }
    }
  }
}

void Board::initPieces()
{
  _currPlacedPieces.clear();
  _currUnplacedPieces.clear();
  _currUnplacedPieces.push_back(new Piece('A', {{1,0}, {1,1}, {1,2}, {0,2}}));
  _currUnplacedPieces.push_back(new Piece('B', {{1,0}, {0,1}, {1,1}, {0,2}, {1,2}}));
  _currUnplacedPieces.push_back(new Piece('C', {{1,0}, {1,1}, {1,2}, {1,3}, {0,3}}));
  _currUnplacedPieces.push_back(new Piece('D', {{1,0}, {1,1}, {1,2}, {1,3}, {0,2}}));
  _currUnplacedPieces.push_back(new Piece('E', {{1,0}, {1,1}, {1,2}, {0,2}, {0,3}}));
  _currUnplacedPieces.push_back(new Piece('F', {{1,0}, {1,1}, {0,1}}));
  _currUnplacedPieces.push_back(new Piece('G', {{2,0}, {2,1}, {2,2}, {1,2}, {0,2}}));
  _currUnplacedPieces.push_back(new Piece('H', {{2,0}, {2,1}, {1,1}, {1,2}, {0,2}}));
  _currUnplacedPieces.push_back(new Piece('I', {{0,0}, {0,1}, {1,1}, {2,1}, {2,0}}));
  _currUnplacedPieces.push_back(new Piece('J', {{0,0}, {0,1}, {0,2}, {0,3}}));
  _currUnplacedPieces.push_back(new Piece('K', {{0,0}, {0,1}, {1,1}, {1,0}}));
  _currUnplacedPieces.push_back(new Piece('L', {{1,0}, {0,1}, {1,1}, {2,1}, {1,2}}));
  for (auto p : _currUnplacedPieces) {
    p->postInit(_fields);
  }
}

const std::map<Piece*, BoardPlacementEntry>& Board::getPlacedPieces() const
{
  return _currPlacedPieces;
}

const std::vector<Piece*>& Board::getUnplacedPieces() const
{
  return _currUnplacedPieces;
}

void Board::draw() const
{
  if (_fields.empty()) {
    cout << "ERROR: empty board" << endl;
    return;
  }

  auto numRows = _fields.size();
  auto numCols = _fields[0].size();  // TODO: Use max of all inner vectors to support irregular fields

  // header on x-axis: 0 1 2 3 ...
  cout << "  ";
  for (size_t c=0; c<numCols; c++) {
    cout << c << " ";
  }
  cout << endl;

  for (size_t r=0; r<numRows; r++) {
    const auto& row = _fields[r];

    cout << r << " ";  // header on y-axis
    for (size_t c=0; c<row.size(); c++) {
      const auto& field = row[c];
      cout << field << " ";
    }
    cout << endl;
  }
  cout << endl;
  cout << "Free Fields: "     << _numFreeFields     << endl;
  cout << "Occupied Fields: " << _numOccupiedFields << endl;
  cout << endl << endl;
}

void Board::showAllPieces() const
{
  cout << "UNPLACED: " << _currUnplacedPieces.size() << endl;
  cout << "----------------------------------------" << endl;
  size_t sumUnplacedExtents = 0;
  for (const auto& p : _currUnplacedPieces) {
    cout << p->id() << ": Supports " << p->getNumOrientations() << " orientations" << endl;
    p->drawBaseorientation();
    sumUnplacedExtents += p->getExtent();
  }

  cout << "PLACED: " << _currPlacedPieces.size() << endl;
  cout << "----------------------------------------" << endl;
  size_t sumPlacedExtents = 0;
  for (const auto& [p, placement] : _currPlacedPieces) {
    cout << p->id() << ": Placed in orientation " << placement._orientationIdx
         << " at position " << placement._topLeftOnBoard.x << "," << placement._topLeftOnBoard.y << endl;
    p->drawBaseorientation();
    sumPlacedExtents += p->getExtent();
  }

  cout << endl << endl;
  cout << "-----> " << _currUnplacedPieces.size() << " unplaced pieces can fill " << sumUnplacedExtents << " more fields" << endl;
  cout << "-----> " << _currPlacedPieces.size()   << " placed pieces currently fill " << sumPlacedExtents << " fields" << endl;

  if (_currUnplacedPieces.size() == 0)
    return;

  // print statistics
  getAndPrintRemainingPlacementOptions();
}

void Board::showPieceDetails(char pieceId) const
{
  Piece* piece = nullptr;
  bool placed = false;
  int placedorientation = -1;
  Coord placedPos;

  // check if placed
  for (const auto& [p, placement] : _currPlacedPieces) {
    if (p->id() == pieceId) {
      piece = p;
      placed = true;
      placedorientation = placement._orientationIdx;
      placedPos = placement._topLeftOnBoard;
      break;
    }
  }

  // check if unplaced
  if (!placed) {
    for (const auto& p : _currUnplacedPieces) {
      if (p->id() == pieceId) {
        piece = p;
        break;
      }
    }
  }

  // piece does not exist
  if (piece == nullptr) {
    cerr << "The piece " << pieceId << " does not exist" << endl;
    return;
  }

  cout << piece->id() << " is currently";
  if (placed) cout << " placed in orientation " << placedorientation << " at position " << placedPos.x << "," << placedPos.y;
  else        cout << " unplaced";
  cout << " and supports " << piece->getNumOrientations() << " orientations..." << endl;
  piece->drawAllorientations();
}

bool Board::tryPlacePiece(Piece *piece, int orientation, const Coord &coord)
{
  // note: it was already checked that there exists an unplaced piece that provides this orientation
  assert(piece && piece->id() != ' ');

  // adapt field states
  if (!isPlaceable(piece, orientation, coord, _fields, _fields))
    return false;

  // transition from unplaced(free) to placed(occupied)
  _currUnplacedPieces.erase(std::find(_currUnplacedPieces.begin(), _currUnplacedPieces.end(), piece));
  _numFreeFields -= piece->getExtent();
  _currPlacedPieces[piece] = BoardPlacementEntry(orientation, coord);
  _numOccupiedFields += piece->getExtent();
  return true;
}


bool Board::removePlacedPiece(Piece *piece)
{
  // note: it was already checked that there exists a placed piece
  assert(piece && piece->id() != ' ');
  assert(_currPlacedPieces.find(piece) != _currPlacedPieces.end());

  // get placement
  auto placement = _currPlacedPieces[piece];

  // adapt field states
  auto geometry = piece->getGeometryOrientations()[placement._orientationIdx];
  for (const auto& localCoord : geometry) {
    auto x = localCoord.x + placement._topLeftOnBoard.x;
    auto y = localCoord.y + placement._topLeftOnBoard.y;
    assert ((int)_fields.size() > y && (int)_fields[y].size() > x && _fields[y][x] != FIELD_EMPTY_ID && _fields[y][x] != FIELD_UNAVAILABLE_ID);
    _fields[y][x] = FIELD_EMPTY_ID;
  }

  // transition from placed(occupied) to unplaced(free)
  _currPlacedPieces.erase(_currPlacedPieces.find(piece));
  _numOccupiedFields -= piece->getExtent();
  _currUnplacedPieces.push_back(piece);
  _numFreeFields += piece->getExtent();
  return true;
}

bool Board::solveGame()
{
  // check if unplaced pieces can exactly fill up the unplaced spots
  int sumUnplacedExtents = 0;
  for (const auto& p : _currUnplacedPieces) {
    sumUnplacedExtents += p->getExtent();
  }
  if (sumUnplacedExtents != _numFreeFields) {
    cerr << "Can't find overall placement. Unplaced piece fields sum up to "
         << sumUnplacedExtents << " but there are " << _numFreeFields << " free fields." << endl;
    return false;
  }

  // are we done already?
  if (_currUnplacedPieces.empty()) {
    cout << "No more unplaced pieces, game is solved already!" << endl;
    return true;
  }

  // print pre-statistics and update remainig possibilities
  auto remainingPossibilities = getAndPrintRemainingPlacementOptions();
  _numRecursiveCalls = 0;

  // restore original state if solving was not successful
  auto startTime = std::chrono::steady_clock::now();
  Board backup(*this);
  if (solveRecursive(remainingPossibilities) == false) {
    *this = backup;
    cerr << "Error -> could not solve the board after " << _numRecursiveCalls << " of " << _remainingBruteForceOptions << " recursive steps" << endl;
    return false;
  }

  // print post-statistics
  std::chrono::duration<double> diff = std::chrono::steady_clock::now() - startTime;
  cout << "Success -> solved the board after " << _numRecursiveCalls << " of " << _remainingBruteForceOptions+1 << " recursive steps" << endl;
  cout << "Solving took " << diff.count() << " seconds (" << std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count()/(_numRecursiveCalls+1) << "ns/recursion)" << endl;
  return true;
}

bool Board::solveRecursive(std::map<Piece*, std::vector<BoardPlacementEntry>> &remainingPlacements)
{
  _numRecursiveCalls++;

  // ends the recursion
  if (_currUnplacedPieces.empty()) {
//    cout << spaceStr() << "#### We are done " << endl;
    return true;
  }

  // no more placement options - cannot solve
  auto currPiece = _currUnplacedPieces.back();
//  cout << spaceStr() << "#### 0. solveBoard called with " << _currUnplacedPieces.size() << " unplaced pieces -> CURR: "
//       << currPiece->id() << endl;
  if (remainingPlacements[currPiece].empty()) {
//    cout << spaceStr() << "#### 2. No more placement options for " << currPiece->id() << endl;
    return false;
  }

  // pop next available placement
  auto nextPlacementForPiece = remainingPlacements[currPiece].back();
  remainingPlacements[currPiece].pop_back();

  // does it work?
  if (!tryPlacePiece(currPiece, nextPlacementForPiece._orientationIdx, nextPlacementForPiece._topLeftOnBoard)) {
    // placement does not work in this step, maybe with the next placement...
//    cout << spaceStr() << "#### 3. placement option for "  << currPiece->id() << "@" << nextPlacementForPiece._orientationIndex
//         << " at " << nextPlacementForPiece._coordOnBoard.x << "/" << nextPlacementForPiece._coordOnBoard.y
//         << " NOT POSSIBLE. Recurse with " << remainingPlacements[currPiece].size()
//         << " alternative placements left..." << endl;
    return solveRecursive(remainingPlacements);
  }

  // piece was placed successfully (was therefore removed from _currUnplacedPieces in tryPlacePiece already)
//  cout << spaceStr() << "#### 4. placement option for " << currPiece->id() << "@" << nextPlacementForPiece._orientationIndex
//       << " at " << nextPlacementForPiece._coordOnBoard.x << "/" << nextPlacementForPiece._coordOnBoard.y
//       << " POSSIBLE. Remaining unplaced pieces: " << _currUnplacedPieces.size() << endl;

  // can it be solved like this?
  if (solveRecursive(remainingPlacements)) {
//    cout << spaceStr() << "#### 5. Awesome, we are done" << endl;
    return true;
  }

  // if not unplace it again (placement was a dead end) and restore placement options of all OTHER yet unplaced
  removePlacedPiece(currPiece);
  for (const auto& unplaced : _currUnplacedPieces) {
    if (unplaced != currPiece) {
      remainingPlacements[unplaced] = Piece::determinePlaceableOptions(_fields, unplaced);
    }
  }
//  cout << spaceStr() << "#### 6. Dammit, placing " << currPiece->id() << "@" << nextPlacementForPiece._orientationIndex
//       << " at " << nextPlacementForPiece._coordOnBoard.x << "/" << nextPlacementForPiece._coordOnBoard.y
//       << " was a DEAD END. Re-added it and recurse with " << remainingPlacements[currPiece].size()
//       << " options. Remaining unplaced pieces: " << _currUnplacedPieces.size() << endl;

  return solveRecursive(remainingPlacements);
}

std::map<Piece*, std::vector<BoardPlacementEntry>> Board::getAndPrintRemainingPlacementOptions() const
{
  std::map<Piece*, std::vector<BoardPlacementEntry>> remainingOptions;
  long long numPossibilitiesBruteForce = 1;
  long long numPossibilitiesCurrentBoard = 1;
  for (const auto& piece : _currUnplacedPieces) {
    numPossibilitiesBruteForce *= piece->getNumPlaceableOptions();
    auto remainingOptionsForPiece = Piece::determinePlaceableOptions(_fields, piece);
    remainingOptions[piece] = remainingOptionsForPiece;
    numPossibilitiesCurrentBoard *= remainingOptionsForPiece.size();
    cout << piece->id() << " had " << piece->getNumPlaceableOptions() << " initial placement options, "
         << remainingOptionsForPiece.size() << " remain with current board" << endl;
  }
  cout << "Brute-force: " << numPossibilitiesBruteForce << ", Current board: " << numPossibilitiesCurrentBoard << endl;
  _remainingBruteForceOptions = numPossibilitiesCurrentBoard;
  return remainingOptions;
}
