#include "Board.h"
#include "Piece.h"

bool Board::isPlaceable(Piece *piece, int configuration, const Coord &coord, const BoardState &boardBefore, BoardState &boardAfter)
{
  auto boardModified = boardBefore;

  auto geometry = piece->getGeometryConfigs()[configuration];
  for (const auto& localCoord : geometry) {
    auto x = localCoord.x + coord.x;
    auto y = localCoord.y + coord.y;
    if ((int)boardBefore.size() <= y || (int)boardBefore[y].size() <= x || boardBefore[y][x] != FieldState::Free) {
      return false;
    }
    else {
      boardModified[y][x] = FieldState::Occupied;
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


  auto column = std::vector<FieldState>(9, FieldState::Free);
  _fields = BoardState(9, column);

  _fields[0][6] = FieldState::Unavailable;
  _fields[0][7] = FieldState::Unavailable;
  _fields[0][8] = FieldState::Unavailable;
  _fields[1][7] = FieldState::Unavailable;
  _fields[1][8] = FieldState::Unavailable;
  _fields[2][3] = FieldState::Unavailable;
  _fields[2][8] = FieldState::Unavailable;
  _fields[5][7] = FieldState::Unavailable;
  _fields[5][8] = FieldState::Unavailable;
  _fields[6][0] = FieldState::Unavailable;
  _fields[6][6] = FieldState::Unavailable;
  _fields[6][7] = FieldState::Unavailable;
  _fields[6][8] = FieldState::Unavailable;
  _fields[7][0] = FieldState::Unavailable;
  _fields[7][1] = FieldState::Unavailable;
  _fields[7][5] = FieldState::Unavailable;
  _fields[7][5] = FieldState::Unavailable;
  _fields[7][7] = FieldState::Unavailable;
  _fields[7][8] = FieldState::Unavailable;
  _fields[8][0] = FieldState::Unavailable;
  _fields[8][1] = FieldState::Unavailable;
  _fields[8][2] = FieldState::Unavailable;
  _fields[8][5] = FieldState::Unavailable;
  _fields[8][6] = FieldState::Unavailable;
  _fields[8][7] = FieldState::Unavailable;
  _fields[8][8] = FieldState::Unavailable;

  for (const auto& column : _fields) {
    for (const auto& field : column) {
      if (field == FieldState::Free) {
        _numFreeFields++;
      }
      else if (field == FieldState::Occupied) {
        _numOccupiedFields++;
      }
      else if (field == FieldState::Unavailable) {
        _numUnavailableFields++;
      }
    }
  }
}

void Board::initPieces()
{
  _currPlacedPieces.clear();
  _currUnplacedPieces.clear();

  auto c = new PieceC();
  c->postInit(_fields);
  _currUnplacedPieces.push_back(c);

  auto j = new PieceJ();
  j->postInit(_fields);
  _currUnplacedPieces.push_back(j);

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
      if (field == FieldState::Free) {
        cout << " ";
      }
      else if (field == FieldState::Occupied) {
        cout << ".";
      }
      else if (field == FieldState::Unavailable) {
        cout << "X";
      }
      else {
        cout << "?";
      }
      cout << " ";
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

  cout << endl << endl << "-----> Unplaced pieces can fill " << sumUnplacedExtents << " more fields" << endl;
  cout << "-----> Placed pieces currently fill " << sumPlacedExtents << " fields" << endl;
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
    assert ((int)_fields.size() > y && (int)_fields[y].size() > x && _fields[y][x] == FieldState::Occupied);
    _fields[y][x] = FieldState::Free;
  }

  // from placed to unplaced
  _currPlacedPieces.erase(_currPlacedPieces.find(piece));
  _currUnplacedPieces.push_back(piece);
  _numOccupiedFields -= piece->getExtent();
  _numFreeFields += piece->getExtent();
  return true;
}

bool Board::findPlacementForAll()
{
  // TODO
  return false;
}
