#include "Board.h"
#include "Piece.h"

bool Board::isPlaceable(Piece *piece, int configuration, const Coord &coord, const BoardState &boardBefore, BoardState &boardAfter)
{
  auto boardModified = boardBefore;

  auto geometry = piece->getGeometryConfigs()[configuration];
  for (const auto& localCoord : geometry) {
    auto x = localCoord.x + coord.x;
    auto y = localCoord.y + coord.y;
    if ((int)boardBefore.size() <= y || (int)boardBefore[y].size() <= x || boardBefore[y][x] != FIELD_EMPTY_ID) {
      return false;
    }
    else {
      boardModified[y][x] = piece->id();
    }
  }

  boardAfter = boardModified;  // only on success, boardAfter will be updated
  return true;
}

Board::Board()
{
  initFields();
  initPieces();
}

const std::map<Piece *, BoardPlacementEntry> Board::getPlacedPieces() const
{
  return _currPlacedPieces;
}

const std::vector<Piece *> Board::getUnplacedPieces() const
{
  return _currUnplacedPieces;
}

void Board::initFields()
{
  _numFreeFields = 0;
  _numOccupiedFields = 0;
  _numUnavailableFields = 0;
  _fields.clear();


  auto column = std::vector<char>(9, FIELD_EMPTY_ID);
  _fields = BoardState(9, column);
  _fields[0][6] = FIELD_UNAVAILABLE_ID;
  _fields[0][7] = FIELD_UNAVAILABLE_ID;
  _fields[0][8] = FIELD_UNAVAILABLE_ID;
  _fields[1][7] = FIELD_UNAVAILABLE_ID;
  _fields[1][8] = FIELD_UNAVAILABLE_ID;
  _fields[2][8] = FIELD_UNAVAILABLE_ID;
  _fields[3][2] = FIELD_UNAVAILABLE_ID;
  _fields[5][7] = FIELD_UNAVAILABLE_ID;
  _fields[5][8] = FIELD_UNAVAILABLE_ID;
  _fields[6][0] = FIELD_UNAVAILABLE_ID;
  _fields[6][6] = FIELD_UNAVAILABLE_ID;
  _fields[6][7] = FIELD_UNAVAILABLE_ID;
  _fields[6][8] = FIELD_UNAVAILABLE_ID;
  _fields[7][0] = FIELD_UNAVAILABLE_ID;
  _fields[7][1] = FIELD_UNAVAILABLE_ID;
  _fields[7][5] = FIELD_UNAVAILABLE_ID;
  _fields[7][6] = FIELD_UNAVAILABLE_ID;
  _fields[7][7] = FIELD_UNAVAILABLE_ID;
  _fields[7][8] = FIELD_UNAVAILABLE_ID;
  _fields[8][0] = FIELD_UNAVAILABLE_ID;
  _fields[8][1] = FIELD_UNAVAILABLE_ID;
  _fields[8][2] = FIELD_UNAVAILABLE_ID;
  _fields[8][5] = FIELD_UNAVAILABLE_ID;
  _fields[8][6] = FIELD_UNAVAILABLE_ID;
  _fields[8][7] = FIELD_UNAVAILABLE_ID;
  _fields[8][8] = FIELD_UNAVAILABLE_ID;

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

  auto a = new PieceA();
  a->postInit(_fields);
  _currUnplacedPieces.push_back(a);

  auto b = new PieceB();
  b->postInit(_fields);
  _currUnplacedPieces.push_back(b);

  auto c = new PieceC();
  c->postInit(_fields);
  _currUnplacedPieces.push_back(c);

  auto d = new PieceD();
  d->postInit(_fields);
  _currUnplacedPieces.push_back(d);

  auto e = new PieceE();
  e->postInit(_fields);
  _currUnplacedPieces.push_back(e);

  auto f = new PieceF();
  f->postInit(_fields);
  _currUnplacedPieces.push_back(f);

  auto g = new PieceG();
  g->postInit(_fields);
  _currUnplacedPieces.push_back(g);

  auto h = new PieceH();
  h->postInit(_fields);
  _currUnplacedPieces.push_back(h);

  auto i = new PieceI();
  i->postInit(_fields);
  _currUnplacedPieces.push_back(i);

  auto j = new PieceJ();
  j->postInit(_fields);
  _currUnplacedPieces.push_back(j);

  auto k = new PieceK();
  k->postInit(_fields);
  _currUnplacedPieces.push_back(k);

  auto l = new PieceL();
  l->postInit(_fields);
  _currUnplacedPieces.push_back(l);

  cout << "After initPieces the _currUnplacedPieces has size: " << _currUnplacedPieces.size() << endl;
}

void Board::draw() const
{
  if (_fields.empty()) {
    cout << "ERROR: empty board" << endl;
    return;
  }

  auto numRows = _fields.size();
  auto numCols = _fields[0].size();  // TODO: Use max of all inner vectors to support irregular fields

  // header 0 1 2 3 ...
  cout << "  ";
  for (size_t c=0; c<numCols; c++) {
    cout << c << " ";
  }
  cout << endl;

  for (size_t r=0; r<numRows; r++) {
    const auto& row = _fields[r];

    cout << r << " ";
    for (size_t c=0; c<row.size(); c++) {
      const auto& field = row[c];
      cout << field << " ";
    }
    cout << endl;
  }
  cout << "Free Fields: " << _numFreeFields << endl;
  cout << "Occupied Fields: " << _numOccupiedFields << endl;
  cout << endl << endl;
}

bool Board::allFieldsOccupied() const
{
  return _numFreeFields == 0;
}

void Board::showAllPieces()
{  
  cout << "UNPLACED: " << _currUnplacedPieces.size() << endl;
  cout << "----------------------------------------" << endl;
  size_t sumUnplacedExtents = 0;
  for (const auto& p : _currUnplacedPieces) {
    cout << p->id() << ": Supports " << p->getNumGeometries() << " configurations" << endl;
    p->drawBaseConfiguration();
    sumUnplacedExtents += p->getExtent();
  }  

  cout << "PLACED: " << _currPlacedPieces.size() << endl;
  cout << "----------------------------------------" << endl;
  size_t sumPlacedExtents = 0;
  for (const auto& [p, placement] : _currPlacedPieces) {
    cout << p->id() << ": Placed in configuration " << placement._geometryIndex
         << " at position " << placement._coordOnBoard.x << "," << placement._coordOnBoard.y << endl;
    p->drawBaseConfiguration();
    sumPlacedExtents += p->getExtent();
  }

  cout << endl << endl;
  cout << "-----> " << _currUnplacedPieces.size() << " unplaced pieces can fill " << sumUnplacedExtents << " more fields" << endl;
  cout << "-----> " << _currPlacedPieces.size() << "  placed pieces currently fill " << sumPlacedExtents << " fields" << endl;

  if (_currUnplacedPieces.size() == 0)
    return;

//  long long numPossibilitiesBruteForce = 1;
//  for (const auto &p : _currUnplacedPieces) {
//    numPossibilitiesBruteForce *= p->getNumPlaceableOptions();
//  }
//  cout << "-----> " << numPossibilitiesBruteForce << "  possibilities for brute-force attempt!" << endl;

  // statistics
  std::map<Piece* , std::vector<BoardPlacementEntry>> remainingPossibilities;
  long long numPossibilitiesBruteForce = 1;
  long long numPossibilitiesCurrentBoard = 1;
  for (const auto& piece : _currUnplacedPieces) {
    numPossibilitiesBruteForce *= piece->getNumPlaceableOptions();
    auto remainingOptionsForPiece = Piece::determinePlaceableOptions(_fields, piece);
    remainingPossibilities[piece] = remainingOptionsForPiece;
    numPossibilitiesCurrentBoard *= remainingOptionsForPiece.size();
    cout << piece->id() << " had " << piece->getNumPlaceableOptions() << " initial placement options, "
         << remainingOptionsForPiece.size() << " remain with current board" << endl;
  }
  cout << "Brute-force: " << numPossibilitiesBruteForce << ", Current board: " << numPossibilitiesCurrentBoard << endl;
}

void Board::showPieceDetails(char pieceId)
{
  Piece* piece = nullptr;
  bool placed = false;
  int placedConfiguration = -1;
  Coord placedPos(-1,-1);

  // check if placed
  for (const auto& [p, placement] : _currPlacedPieces) {
    if (p->id() == pieceId) {
      piece = p;
      placed = true;
      placedConfiguration = placement._geometryIndex;
      placedPos = placement._coordOnBoard;
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
  if (placed) cout << " placed in configuration " << placedConfiguration << " at position " << placedPos.x << "," << placedPos.y;
  else        cout << " unplaced";
  cout << " and supports " << piece->getNumGeometries() << " configurations..." << endl;
  piece->drawAllConfigurations();
}

bool Board::tryPlacePiece(Piece *piece, int configuration, const Coord &coord)
{
  // note: it was already checked that there exists an unplaced piece that provides this configuration
  assert(piece && piece->id() != ' ');

  // adapt field states
  if (!isPlaceable(piece, configuration, coord, _fields, _fields))
    return false;

  // from unplaced to placed
  BoardPlacementEntry newPlacement(configuration, coord);
  _currPlacedPieces[piece] = newPlacement;
  _currUnplacedPieces.erase(std::find(_currUnplacedPieces.begin(), _currUnplacedPieces.end(), piece));
  _numOccupiedFields += piece->getExtent();
  _numFreeFields -= piece->getExtent();

  if (_numFreeFields == 0) {
    cout << "CONGRATULATIONS!" << endl;
  }
  return true;
}

std::pair<bool, BoardPlacementEntry> Board::tryPlacePieceAnywhere(Piece *piece)
{
  // TODO
  BoardPlacementEntry dummy;
  return std::make_pair(false, dummy);
}

bool Board::removePlacedPiece(Piece *piece)
{
  // note: it was already checked that there exists a placed piece
  assert(piece && piece->id() != ' ');
  assert(_currPlacedPieces.find(piece) != _currPlacedPieces.end());

  // get placment
  auto placement = _currPlacedPieces[piece];

  // adapt field states
  auto geometry = piece->getGeometryConfigs()[placement._geometryIndex];
  for (const auto& localCoord : geometry) {
    auto x = localCoord.x + placement._coordOnBoard.x;
    auto y = localCoord.y + placement._coordOnBoard.y;
    assert ((int)_fields.size() > y && (int)_fields[y].size() > x && _fields[y][x] != FIELD_EMPTY_ID && _fields[y][x] != FIELD_UNAVAILABLE_ID);
    _fields[y][x] = FIELD_EMPTY_ID;
  }

  // from placed to unplaced
  _currPlacedPieces.erase(_currPlacedPieces.find(piece));
  _currUnplacedPieces.push_back(piece);
  _numOccupiedFields -= piece->getExtent();
  _numFreeFields += piece->getExtent();
  return true;
}


bool Board::solveBoard(std::map<Piece*, std::vector<BoardPlacementEntry>> &remainingPlacements)
{
  size_t atBegin = _currUnplacedPieces.size();
  auto spaceStr = [atBegin]()
  {
    std::stringstream ss;
    for (size_t i=0; i < atBegin; i++)
      ss << " ";
    return ss.str();
  };


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
  if (!tryPlacePiece(currPiece, nextPlacementForPiece._geometryIndex, nextPlacementForPiece._coordOnBoard)) {
    // placement does not work in this step, maybe with the next placement...
//    cout << spaceStr() << "#### 3. placement option for "  << currPiece->id() << "@" << nextPlacementForPiece._geometryIndex
//         << " at " << nextPlacementForPiece._coordOnBoard.x << "/" << nextPlacementForPiece._coordOnBoard.y
//         << " NOT POSSIBLE. Recurse with " << remainingPlacements[currPiece].size()
//         << " alternative placements left..." << endl;
    return solveBoard(remainingPlacements);
  }

  // piece was placed successfully (was therefore removed from _currUnplacedPieces in tryPlacePiece already)
//  cout << spaceStr() << "#### 4. placement option for " << currPiece->id() << "@" << nextPlacementForPiece._geometryIndex
//       << " at " << nextPlacementForPiece._coordOnBoard.x << "/" << nextPlacementForPiece._coordOnBoard.y
//       << " POSSIBLE. Remaining unplaced pieces: " << _currUnplacedPieces.size() << endl;

  // can it be solved like this?
  if (solveBoard(remainingPlacements)) {
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
//  cout << spaceStr() << "#### 6. Dammit, placing " << currPiece->id() << "@" << nextPlacementForPiece._geometryIndex
//       << " at " << nextPlacementForPiece._coordOnBoard.x << "/" << nextPlacementForPiece._coordOnBoard.y
//       << " was a DEAD END. Re-added it and recurse with " << remainingPlacements[currPiece].size()
//       << " options. Remaining unplaced pieces: " << _currUnplacedPieces.size() << endl;

  return solveBoard(remainingPlacements);
}

bool Board::findPlacementForAll()
{
  // check if we have the exact amount of pieces and free fields
  int sumUnplacedExtents = 0;
  for (const auto& p : _currUnplacedPieces) {
    sumUnplacedExtents += p->getExtent();
  }
  if (sumUnplacedExtents != _numFreeFields) {
    cerr << "Can't find overall placment. Unplaced piece fields sum up to "
         << sumUnplacedExtents << " but there are " << _numFreeFields << " free fields." << endl;
    return false;
  }

  // are we done already
  if (_currUnplacedPieces.empty()) {
    cout << "No more unplaced pieces, game is solved already!" << endl;
    return true;
  }

  // statistics
  std::map<Piece* , std::vector<BoardPlacementEntry>> remainingPossibilities;
  long long numPossibilitiesBruteForce = 1;
  long long numPossibilitiesCurrentBoard = 1;
  for (const auto& piece : _currUnplacedPieces) {
    numPossibilitiesBruteForce *= piece->getNumPlaceableOptions();

    auto remainingOptionsForPiece = Piece::determinePlaceableOptions(_fields, piece);
    remainingPossibilities[piece] = remainingOptionsForPiece;
    numPossibilitiesCurrentBoard *= remainingOptionsForPiece.size();

    cout << piece->id() << " had " << piece->getNumPlaceableOptions() << " initial placement options, "
         << remainingOptionsForPiece.size() << " remain with current board" << endl;
  }
  cout << "Brute-force: " << numPossibilitiesBruteForce << ", Current board: " << numPossibilitiesCurrentBoard << endl;

  Board backup(*this);
  if (solveBoard(remainingPossibilities) == false) {
    // restore original state
    *this = backup;
    return false;
  }

  return true;
}
