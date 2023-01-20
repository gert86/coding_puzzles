#pragma once

#define CLASSNAME Ball_Game

#include "base_header.h"

using namespace std;


class CLASSNAME
{
public:
    CLASSNAME()
    {
        cout << "Running " << VERSION_STRING(CLASSNAME) << "..." << endl;
    }
};


struct Coord
{
  int x;
  int y;

  Coord(int x_, int y_) :
    x(x_),
    y(y_)
  {}

  bool operator<(const Coord& rhs ) const {
    return std::tie(x,y) < std::tie(rhs.x, rhs.y);
  }
};

static bool operator==(const Coord& lhs, const Coord& rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y;
}

enum FieldState
{
  Free = 0,
  Occupied,
  Unavailable
};

struct BoardPlacement
{
  int _geometryIndex{-1};
  Coord _coordOnBoard{0,0};
};

enum GeometryModification
{
  Original = 0,
  Rotated90,
  Rotated180,
  Rotated270,
  Mirrored,
  MirroredRotated90,
  MirroredRotated180,
  MirroredRotated270
};


using Geometry = std::vector<Coord>;
using Geometries = std::vector<Geometry>;
class Piece
{
// Helper functions
private:
  static void drawGeometry(const Geometry& geometry)
  {
    int maxXPlus1 = 0;
    int maxYPlus1 = 0;
    for (const auto &entry : geometry) {
      maxXPlus1 = std::max(maxXPlus1, entry.x + 1);
      maxYPlus1 = std::max(maxYPlus1, entry.y + 1);
    }

    // note: col=x, row=y
    for (int r=0; r<maxYPlus1; r++) {
      for (int c=0; c<maxXPlus1; c++) {
        if(std::find(geometry.begin(), geometry.end(), Coord(c, r)) == geometry.end()) {
          cout << " ";
        }
        else {
          cout << "*";
        }
      }
      cout << endl;
    }
  }

  static Geometry transformGeometry(const Geometry& geometry, GeometryModification modification)
  {
    Geometry transformed;

    Geometry mirrored;
    for (const auto& entry : geometry) {
      mirrored.push_back({-entry.x, entry.y});
    }

    if (modification == GeometryModification::Original) {
      transformed = geometry;
    }
    else if (modification == GeometryModification::Rotated90) {
      for (const auto& entry : geometry) {
        transformed.push_back({-entry.y, entry.x});
      }
    }
    else if (modification == GeometryModification::Rotated180) {
      for (const auto& entry : geometry) {
        transformed.push_back({-entry.x, -entry.y});
      }
    }
    else if (modification == GeometryModification::Rotated270) {
      for (const auto& entry : geometry) {
        transformed.push_back({entry.y, -entry.x});
      }
    }
    else if (modification == GeometryModification::Mirrored) {
      transformed = mirrored;
    }
    else if (modification == GeometryModification::MirroredRotated90) {
      transformed = transformGeometry(mirrored, GeometryModification::Rotated90);
    }
    else if (modification == GeometryModification::MirroredRotated180) {
      transformed = transformGeometry(mirrored, GeometryModification::Rotated180);
    }
    else if (modification == GeometryModification::MirroredRotated270) {
      transformed = transformGeometry(mirrored, GeometryModification::Rotated270);
    }


    // move to positive coords
    int minX = 0;
    int minY = 0;
    for (const auto &entry : transformed) {
      minX = std::min(minX, entry.x);
      minY = std::min(minY, entry.y);
    }
    for (auto &entry : transformed) {
      entry.x += abs(minX);
      entry.y += abs(minY);
    }

    return transformed;
  }

  // adds up to 7 additional geometries through rotation and mirroring
  void obtainGeometriesFromBase()
  {
    using SortedGeometry = std::set<Coord>;

    std::set<SortedGeometry> knownConfigurationsSorted;
    _geometryConfigurations.clear();

    // insert base
    SortedGeometry baseSorted;
    for (const auto &entry : _baseGeometry) {
      baseSorted.insert(entry);
    }
    knownConfigurationsSorted.insert(baseSorted);
    _geometryConfigurations.push_back(_baseGeometry);

    // check other possible configuration (avoid duplicates)
    for (const auto& t : {GeometryModification::Rotated90, GeometryModification::Rotated180, GeometryModification::Rotated270,
                          GeometryModification::Mirrored, GeometryModification::MirroredRotated90,
                          GeometryModification::MirroredRotated180, GeometryModification::MirroredRotated270})
    {
      auto transformed = Piece::transformGeometry(_baseGeometry, t);
      SortedGeometry transformedSorted;
      for (const auto &entry : transformed) {
        transformedSorted.insert(entry);
      }
      if (knownConfigurationsSorted.find(transformedSorted) == knownConfigurationsSorted.end()) {
        knownConfigurationsSorted.insert(transformedSorted);
        _geometryConfigurations.push_back(transformed);
      }
    }

    cout << "Piece " << _id << " has " << getGeometryConfigs().size() << " configurations" << endl;
  }

  void obtainPlaceableOptions()
  {
    // TODO
    cout << "Piece " << _id << " has " << getPlaceableOptions().size() << " placeable options on the board" << endl;
  }

private:
  Geometries _geometryConfigurations;
  std::vector<BoardPlacement> _placableOptions;

protected:
  virtual void init() = 0;         // defines base geometry

protected:
  char _id;
  Geometry _baseGeometry;

public:
  // TODO: make sure this is called from all derived ones before usage
  void postInit()
  {
    obtainGeometriesFromBase();
    obtainPlaceableOptions();
  }

  void drawBaseConfiguration() const
  {
    Piece::drawGeometry(_baseGeometry);
    cout << endl;
  }

  void drawAllConfigurations() const
  {
    for (size_t i=0; i<_geometryConfigurations.size(); i++) {
      cout << "Configuration " << i << ": " << endl;
      Piece::drawGeometry(_geometryConfigurations[i]);
      cout << endl;
    }
  }

  const Geometries& getGeometryConfigs() const
  {
    return _geometryConfigurations;
  }

  const std::vector<BoardPlacement>& getPlaceableOptions() const
  {
    return _placableOptions;
  }

  char id() const
  {
    return _id;
  }
};

class PieceC : public Piece
{
private:
  void init() override
  {
    _id = 'C';
    _baseGeometry = {{1,0}, {1,1}, {1,2}, {1,3}, {0,3}};
  }

public:
  PieceC()
  {
    init();
  }
};

class PieceJ : public Piece
{
private:
  void init() override
  {
    _id = 'J';
    _baseGeometry = {{0,0}, {0,1}, {0,2}, {0,3}};
  }

public:
  PieceJ()
  {
    init();
  }
};



class Board
{
private:
  int _numFreeFields{-1};
  int _numOccupiedFields{-1};
  int _numUnavailableFields{-1};
  std::vector<std::vector<FieldState>> _fields;

  std::map<Piece*, BoardPlacement> _currPlacedPieces;
  std::vector<Piece*> _currUnplacedPieces;

public:
  Board()
  {
    initFields();
    initPieces();
  }

  const std::map<Piece*, BoardPlacement> getPlacedPieces() const
  {
    return _currPlacedPieces;
  }

  const std::vector<Piece*> getUnplacedPieces() const
  {
    return _currUnplacedPieces;
  }


  void initFields()
  {
    _numFreeFields = 0;
    _numOccupiedFields = 0;
    _numUnavailableFields = 0;
    _fields.clear();


    auto column = std::vector<FieldState>(9, FieldState::Free);
    _fields = std::vector<std::vector<FieldState>>(9, column);

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

  void initPieces()
  {
    _currPlacedPieces.clear();
    _currUnplacedPieces.clear();

    auto c = new PieceC();
    c->postInit();
    _currUnplacedPieces.push_back(c);

    auto j = new PieceJ();
    j->postInit();
    _currUnplacedPieces.push_back(j);

    cout << "After initPieces the _currUnplacedPieces has size: " << _currUnplacedPieces.size() << endl;
  }

  void draw() const
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
    cout << endl << endl;
  }

  bool allFieldsOccupied() const
  {
    return _numFreeFields == 0;
  }

  void showAllPieces()
  {
    cout << "UNPLACED: " << _currUnplacedPieces.size() << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& p : _currUnplacedPieces) {
      cout << p->id() << ": Supports " << p->getGeometryConfigs().size() << " configurations" << endl;
      p->drawBaseConfiguration();
    }

    cout << "PLACED: " << _currPlacedPieces.size() << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& [p, placement] : _currPlacedPieces) {
      cout << p->id() << ": Placed in configuration " << placement._geometryIndex
           << " at position " << placement._coordOnBoard.x << "," << placement._coordOnBoard.y << endl;
      p->drawBaseConfiguration();
    }
  }

  void showPieceDetails(char pieceId)
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
    cout << " and supports " << piece->getGeometryConfigs().size() << " configurations..." << endl;
    piece->drawAllConfigurations();
  }

  bool tryPlacePiece(Piece* piece, int configuration, Coord coord)
  {
    // note: it was already checked that there exists an unplaced piece that provides this configuration
    assert(piece && piece->id() != ' ');

    // adapt field states
    auto geometry = piece->getGeometryConfigs()[configuration];
    auto fieldsCopy = _fields;
    for (const auto& localCoord : geometry) {
      auto x = localCoord.x + coord.x;
      auto y = localCoord.y + coord.y;
      if ((int)_fields.size() <= y || (int)_fields[y].size() <= x || _fields[y][x] != FieldState::Free) {
        return false;
      }
      else {
        fieldsCopy[y][x] = FieldState::Occupied;
      }
    }

    // from unplaced to placed
    BoardPlacement newPlacement;
    newPlacement._geometryIndex = configuration;
    newPlacement._coordOnBoard = coord;
    _currPlacedPieces[piece] = newPlacement;
    _currUnplacedPieces.erase(std::find(_currUnplacedPieces.begin(), _currUnplacedPieces.end(), piece));
    _fields = fieldsCopy;
    return true;
  }

  std::pair<bool, BoardPlacement> tryPlacePieceAnywhere(Piece* piece)
  {
    // TODO
    BoardPlacement dummy;
    return std::make_pair(false, dummy);
  }

  bool removePlacedPiece(Piece* piece)
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
    return true;
  }

  bool findPlacementForAll()
  {
    // TODO
    return false;
  }
};

class Game
{
private:
  Board* _board;
  // we might need them...
  //std::stack<Piece*> _placedPieces;
  //std::vector<Piece*> _unplacedPieces;

  void showPrompt() const
  {
    cout << "Enter a command: " << endl;
    cout << "h ... show this help text" << endl;
    cout << "d ... draw board" << endl;
    cout << "r ... reset board to empty" << endl;
    cout << "s ... show all pieces (in base configuration)" << endl;
    cout << "s <piece_id> ... show details for piece" << endl;
    cout << "p <piece_id> <config_id> <x> <y> ... place a piece" << endl;
    cout << "x <piece_id> ... unplace a piece" << endl;
    cout << "f ... find a placment for all unplaced pieces" << endl;
    cout << "q...quit" << endl;
  }

  bool parsePieceId(const std::string& inputStr, char& pieceId)
  {
    istringstream ss(inputStr);
    bool success = false;
    if(ss >> pieceId) {
      //cout << "Parsed: pieceId=" << pieceId << endl;
      success = true;
    }
    return (success==true && pieceId!=' ');
  }

  bool parseIdsAndCoordinate(const std::string& inputStr,
                             char& pieceId, int& configId, Coord& coord)
  {
    istringstream ss(inputStr);
    bool success = false;
    if(ss >> pieceId >> configId >> coord.x >> coord.y) {
      success = true;
      //cout << "Parsed: pieceId=" << pieceId
      //     << "; configId=" << configId
      //     << "; xBoard=" << coord.x
      //     << "; yBoard=" << coord.y << endl;
    }

    return (success==true && pieceId!=' ' && configId!=-1 && coord.x!=-1 && coord.y!=-1);
  }

public:
  void init()
  {
    _board = new Board();
  }

  int mainLoop()
  {
    showPrompt();
    std::string input;
    while (true) {
      getline(cin, input);

      if (input.empty()) {  // allow scrolling
        cout << endl;
        continue;
      }
      else if (input == "h") {
        // HELP
        showPrompt();
      }
      else if (input == "d") {
        // DRAW BOARD
        _board->draw();
      }
      else if (input == "r") {
        // RESET BOARD
        delete _board;
        _board = new Board();
        cout << "Success: Reset board" << endl;
      }
      else if (input == "s") {
        // SHOW ALL PIECES
        _board->showAllPieces();
        cout << endl;
      }
      else if (input.size() > 2 && input.substr(0, 2) == "s ") {
        // SHOW DETAILS OF 1 PIECE
        char pieceId = ' ';
        bool success = parsePieceId(input.substr(2), pieceId);
        if (!success) {
          cerr << "Error: Usage is: " << endl << "s <piece_id>" << endl;
          continue;
        }
        _board->showPieceDetails(pieceId);
        cout << endl;
      }
      else if (input.size() > 2 && input.substr(0, 2) == "p ") {
        // PLACE 1 PIECE
        char pieceId = ' ';
        int configId = -1;
        Coord coordToPlace(-1, -1);
        bool success = parseIdsAndCoordinate(input.substr(2), pieceId, configId, coordToPlace);
        if (!success) {
          cerr << "Error: Usage is: " << endl << "p <piece_id> <config_id> <x> <y>" << endl;
          continue;
        }

        // check if piece still unplaced
        Piece* piece = nullptr;
        for (const auto& p : _board->getUnplacedPieces()) {
          if (p->id() == pieceId) {
            piece = p;
            break;
          }
        }
        if (!piece) {
          cerr << "Error: There is no unplaced piece with id " << pieceId << " among the "
               << _board->getUnplacedPieces().size() << " unplaced pieces" << endl;
          continue;
        }

        // check if piece has allows this configuration
        if (configId >= (int)piece->getGeometryConfigs().size()) {
          cerr << "Error: The piece with id " << pieceId << " has only " << piece->getGeometryConfigs().size()
               << " configurations, but index " << configId << " was requested!" << endl;
          continue;
        }

        // try to place it there
        auto result = _board->tryPlacePiece(piece, configId, coordToPlace);
        if (result) {
          cout << "Success -> placed " << pieceId << "@" << configId << " at pos" << coordToPlace.x << "/" << coordToPlace.y << endl;
        }
        else {
          cerr << "Error -> unable to place " << pieceId << "@" << configId << " at pos" << coordToPlace.x << "/" << coordToPlace.y << endl;
        }
      }
      else if (input.size() > 2 && input.substr(0, 2) == "x ") {
        // REMOVE 1 PIECE
        char pieceId = ' ';
        bool success = parsePieceId(input.substr(2), pieceId);
        if (!success) {
          cerr << "Error: Usage is: " << endl << "s <piece_id>" << endl;
          continue;
        }

        // check if piece is placed
        Piece* piece = nullptr;
        for (const auto& [p, coord] : _board->getPlacedPieces()) {
          if (p->id() == pieceId) {
            piece = p;
            break;
          }
        }
        if (!piece) {
          cerr << "Error: There is no placed piece with id " << pieceId << " among the "
               << _board->getPlacedPieces().size() << " placed pieces" << endl;          continue;
        }


        if(_board->removePlacedPiece(piece)) {
          cout << "Success -> removed piece " << piece->id() << " from board" << std::endl;
        }
        else {
          cout << "Error -> could not remove piece " << piece->id() << " from board " << std::endl;
        }
      }
      else if (input == "f") {
        // FIND A SOLUTION FOR ALL UNPLACED PIECES
        if (_board->findPlacementForAll()) {
          cout << "Success -> solved the board" << std::endl;
        }
        else {
          cerr << "Error -> could not solve the board" << std::endl;
        }
        cout << endl;
      }
      else if (input == "q") {
        cout << "Quit!" << endl;
        return 0;
      }
      else {
        cerr << "Error: unknown command: " << input << endl;
      }
      cout << endl;
    }

    return -1;
  }
};

TEST(CLASSNAME, Test1)
{    
    Game g;
    g.init();
    int ret = g.mainLoop();

    cout << "Program exited " << (ret==0 ? "normally" : "with failure") << " -> return code: " << ret << endl;
}

#undef CLASSNAME
