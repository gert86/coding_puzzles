#include "Board.h"
#include "Piece.h"

#include <fstream>

const std::string Board::INIT_OPTIONS_CACHE_FILE = "/tmp/initPlaceableOptionsCache.txt";

bool Board::isPlaceable(const Piece *piece, int orientation, const Coord &coord,
                        const BoardState &boardBefore, BoardState &boardAfter)
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

  // Read from cache file if possible and exit
  if (readReducedInitOptionsFromCache(_fields, _currUnplacedPieces))
    return;

  // Need to calculate them, but storing in cache for later
  cout << endl << "Reducing initially placeable options for " << _currUnplacedPieces.size() << " pieces (this could take a while) ... " << flush;
  for (auto p : _currUnplacedPieces) {
    auto reducedOptions = Piece::reducePlaceableOptions(p->getInitialPlaceableOptions(), _fields, p, _currUnplacedPieces);
    p->setInitialPlaceableOptions(reducedOptions);
  }
  std::cout << "DONE" << endl << endl;
  writeReducedInitOptionsToCache(_fields, _currUnplacedPieces);
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
  auto numCols = _fields[0].size();

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
    p->drawBaseOrientation();
    sumUnplacedExtents += p->getExtent();
  }

  cout << "PLACED: " << _currPlacedPieces.size() << endl;
  cout << "----------------------------------------" << endl;
  size_t sumPlacedExtents = 0;
  for (const auto& [p, placement] : _currPlacedPieces) {
    cout << p->id() << ": Placed in orientation " << placement._orientationIdx
         << " at position " << placement._topLeftOnBoard.x << "," << placement._topLeftOnBoard.y << endl;
    p->drawBaseOrientation();
    sumPlacedExtents += p->getExtent();
  }

  cout << endl << endl;
  cout << "-----> " << _currUnplacedPieces.size() << " unplaced pieces can fill " << sumUnplacedExtents << " more fields" << endl;
  cout << "-----> " << _currPlacedPieces.size()   << " placed pieces currently fill " << sumPlacedExtents << " fields" << endl;

  if (_currUnplacedPieces.size() == 0)
    return;

  // print statistics
  getRemainingPlacementOptions(false, true);
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
  piece->drawAllOrientations();
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
  const auto& geometry = piece->getGeometryOrientations()[placement._orientationIdx];
  for (const auto& localCoord : geometry) {
    auto x = localCoord.x + placement._topLeftOnBoard.x;
    auto y = localCoord.y + placement._topLeftOnBoard.y;
    //assert ((int)_fields.size() > y && (int)_fields[y].size() > x && _fields[y][x] != FIELD_EMPTY_ID && _fields[y][x] != FIELD_UNAVAILABLE_ID);
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



  // sort by num. initial placement options
  // since we insert and remove from the back, we want it in decreasing order
  // Note: It makes almost no difference whether we sort by INITIAL or REMAINING placement options (usually same ordering)
  std::sort(_currUnplacedPieces.begin(), _currUnplacedPieces.end(),
            [](const Piece* l, const Piece* r) { return l->getNumInitialPlaceableOptions() >= r->getNumInitialPlaceableOptions(); } );  // initial
            //[remainingPossibilities](Piece* l, Piece* r) { return remainingPossibilities.at(l).size() >= remainingPossibilities.at(r).size(); } );  // remaining

  // print pre-statistics and update remaining possibilities
  auto remainingPossibilities = getRemainingPlacementOptions(true, true);
  _numRecursiveCalls = 0;

  // restore original state if solving was not successful
  auto startTime = std::chrono::steady_clock::now();
  Board backup(*this);
  if (solveRecursive(remainingPossibilities) == false) {
    *this = backup;
    cerr << "Error -> could not solve the board after " << _numRecursiveCalls << " of " << _remainingBruteForceOptions+1 << " recursive steps" << endl;
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
  // include=true means only the given piece, include=false means all except the given  piece
  auto updateRemainingPlacementFor = [this, &remainingPlacements](Piece* piece)
  {
    for (const auto& unplaced : _currUnplacedPieces) {
      if (piece==unplaced) {
        remainingPlacements[unplaced] = Piece::determinePlaceableOptions(_fields, unplaced, true);
      }
    }
  };

  auto updateRemainingPlacementExceptFor = [this, &remainingPlacements](Piece* excludePiece)
  {
    for (const auto& unplaced : _currUnplacedPieces) {
      if (excludePiece!=unplaced) {
        remainingPlacements[unplaced] = Piece::determinePlaceableOptions(_fields, unplaced, true);
      }
    }
  };

  _numRecursiveCalls++;

  // ends the recursion
  if (_currUnplacedPieces.empty()) {
    return true;
  }

  // no more placement options - cannot solve
  auto currPiece = _currUnplacedPieces.back();
  if (remainingPlacements[currPiece].empty()) {
    return false;
  }

  // pop next available placement
  auto nextPlacementForPiece = remainingPlacements[currPiece].back();
  remainingPlacements[currPiece].pop_back();

  // does it work?
  if (!tryPlacePiece(currPiece, nextPlacementForPiece._orientationIdx, nextPlacementForPiece._topLeftOnBoard)) {
    // placement does not work in this step, maybe with the next placement...
    return solveRecursive(remainingPlacements);
  }
  // piece was placed successfully (was removed from _currUnplacedPieces in tryPlacePiece already)
  if (!_currUnplacedPieces.empty()) {
    auto nextToBeProcessed = _currUnplacedPieces.back();
    updateRemainingPlacementFor(nextToBeProcessed);
  }

  // can it be solved like this?
  if (solveRecursive(remainingPlacements)) {
    return true;
  }

  // if not unplace it again (placement was a dead end) and restore placement options of all OTHER yet unplaced
  removePlacedPiece(currPiece);
  updateRemainingPlacementExceptFor(currPiece);

  return solveRecursive(remainingPlacements);
}

std::map<Piece*, std::vector<BoardPlacementEntry>> Board::getRemainingPlacementOptions(bool reduce, bool printLog) const
{
  std::string reduceInfo = reduce ? "(reduced)" : "(unreduced)";
  std::map<Piece*, std::vector<BoardPlacementEntry>> remainingOptions;
  long long numPossibilitiesBruteForce = 1;
  long long numPossibilitiesCurrentBoard = 1;
  for (const auto& piece : _currUnplacedPieces) {
    numPossibilitiesBruteForce *= piece->getNumInitialPlaceableOptions();
    auto remainingOptionsForPiece = Piece::determinePlaceableOptions(_fields, piece, true);
    if (reduce) {
      remainingOptionsForPiece = Piece::reducePlaceableOptions(remainingOptionsForPiece, _fields, piece, _currUnplacedPieces);
    }
    remainingOptions[piece] = remainingOptionsForPiece;
    numPossibilitiesCurrentBoard *= remainingOptionsForPiece.size();
    if (printLog) {
      cout << piece->id() << " had " << piece->getNumInitialPlaceableOptions() << " initial placement options, "
           << remainingOptionsForPiece.size() << " remain with current board " << reduceInfo << endl;
    }
  }
  if (printLog) {
    cout << "Brute-force: " << numPossibilitiesBruteForce
         << ", Current board " << reduceInfo << ": " << numPossibilitiesCurrentBoard << endl;
  }
  _remainingBruteForceOptions = numPossibilitiesCurrentBoard;
  return remainingOptions;
}

std::string magicValue(const BoardState &boardState, const std::vector<Piece *> &unplacedPieces)
{
  stringstream ss;
  ss << boardState.size();
  if (boardState.empty())
    return ss.str();

  ss << "_" << boardState.size();
  ss << "__" << unplacedPieces.size();
  for (const auto& p : unplacedPieces) {
    ss << "_" << p->id() << "_" << p->getNumOrientations() << "_" << p->getExtent();
  }
  return ss.str();
}

bool Board::writeReducedInitOptionsToCache(const BoardState &boardState, const std::vector<Piece *> &unplacedPieces)
{
  ofstream file;
  file.open(INIT_OPTIONS_CACHE_FILE, ios::out | ios::trunc);
  if (!file.is_open()) {
    cerr << "Error: cannot write to cache file: " << INIT_OPTIONS_CACHE_FILE << endl;
    return false;
  }

  // header
  file << magicValue(boardState, unplacedPieces) << endl;

  // data
  file << unplacedPieces.size() << endl;
  for (const auto& p : unplacedPieces) {
    file << p->id() << endl;
    file << p->getNumInitialPlaceableOptions() << endl;
    for (const auto& option : p->getInitialPlaceableOptions())
      file << option._orientationIdx << " " << option._topLeftOnBoard.x << " " << option._topLeftOnBoard.y << endl;
  }


  cout << "Wrote cache file: " << INIT_OPTIONS_CACHE_FILE << endl;
  return true;
}

bool Board::readReducedInitOptionsFromCache(const BoardState &boardState, const std::vector<Piece *> &unplacedPieces)
{
  ifstream file;
  file.open(INIT_OPTIONS_CACHE_FILE);
  if (!file.is_open()) {
    cout << "cannot read from cache: " << INIT_OPTIONS_CACHE_FILE << endl;
    return false;
  }

  // read header
  auto magicValueCurr = magicValue(boardState, unplacedPieces);

  std::string magicValueFromCache;
  getline(file, magicValueFromCache);
  if (magicValueFromCache != magicValueCurr) {
    cout << "cannot use cache file because board/piece configuration seems different" << endl;
    cout << "magic values differ: '" << magicValueFromCache << "' vs. '" << magicValueCurr << "'" << endl;
    return false;
  }

  // read data
  std::string line;

  size_t numUnplaced;
  getline(file, line);
  istringstream in(line);
  in >> numUnplaced;
  assert(numUnplaced == unplacedPieces.size());

  for (size_t i=0; i<numUnplaced; i++) {
    std::vector<BoardPlacementEntry> cachedOptions;

    auto piece = unplacedPieces[i];
    getline(file, line);
    assert(line.size()==1 && line[0] == piece->id());

    size_t numPlacementsForPiece;
    getline(file, line);
    istringstream in(line);
    in >> numPlacementsForPiece;

    for (size_t placement=0; placement<numPlacementsForPiece; placement++) {
      int orientationIndex;
      Coord topLeftOnBoard;
      getline(file, line);
      istringstream in(line);
      in >> orientationIndex >> topLeftOnBoard.x >> topLeftOnBoard.y;
      cachedOptions.emplace_back(orientationIndex, topLeftOnBoard);
    }
    piece->setInitialPlaceableOptions(cachedOptions);
  }

  cout << "Read and applied cache file: " << INIT_OPTIONS_CACHE_FILE << endl;
  return true;
}
