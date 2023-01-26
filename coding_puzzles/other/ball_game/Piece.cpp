#include "Piece.h"
#include "Board.h"

// Helper functions
namespace {

std::vector<Coord> getFieldsWithId(const BoardState &boardState, char id)
{
  std::set<Coord> matchingFields;
  for (size_t r=0; r<boardState.size(); r++) {
    for (size_t c=0; c<boardState[r].size(); c++) {
      if (boardState[r][c] == id) {
        matchingFields.insert(Coord(c,r));
      }
    }
  }

  std::vector<Coord> ret(matchingFields.begin(), matchingFields.end());
  return ret;
}
}

std::vector<BoardPlacementEntry> Piece::determinePlaceableOptions(const BoardState &boardState, const Piece *piece, const std::vector<Piece*>& unplacedPieces)
{
  std::vector<BoardPlacementEntry> options;
  auto bbxes = piece->getGeometryOrientationBoundingBoxes();
  BoardState dummy;
  for(size_t o=0; o < piece->getNumOrientations(); o++) {    
    for(size_t y=0; y < boardState.size() - bbxes[o].second.y; y++) {
      for(size_t x=0; x < boardState[0].size() - bbxes[o].second.x; x++) {
        Coord coord(x, y);
        if (Board::isPlaceable(piece, o, coord, boardState, dummy)) {
          options.emplace_back(o, coord);
        }
      }
    }
  }

  if (unplacedPieces.empty()) {
    return options;
  }

  // further filter the options that lead to dead-ends w.r.t. unplaced pieces
  std::vector<BoardPlacementEntry> reducedOptions;
  BoardState boardStatePlusPiece;
  for (const auto& option : options) {

    // pretend that piece is placed in this option
    assert(Board::isPlaceable(piece, option._orientationIdx, option._topLeftOnBoard, boardState, boardStatePlusPiece));
    const auto freeFieldsAfterPiece = getFieldsWithId(boardStatePlusPiece, FIELD_EMPTY_ID);
    auto notCoverableFields = freeFieldsAfterPiece;  // will get empty for valid options
    bool optionPossible = true;    


    for (const auto& unplacedPiece : unplacedPieces) {
      if (unplacedPiece == piece)
        continue;

      // A. check if this placement makes placing any other piece impossible
      auto remainingOptionsForUnplaced = Piece::determinePlaceableOptions(boardStatePlusPiece, unplacedPiece);
      if (remainingOptionsForUnplaced.empty()) {
        optionPossible = false;
        break;
      }

      // B. ...or causes any free field to be not coverable
      if (!notCoverableFields.empty()) {
        for (const auto& otherOption : remainingOptionsForUnplaced) {
          BoardState boardStatePlusPiecePlusCurrent;
          if(Board::isPlaceable(unplacedPiece, otherOption._orientationIdx, otherOption._topLeftOnBoard,
                                boardStatePlusPiece, boardStatePlusPiecePlusCurrent))
          {
            auto freeFieldsAfterPiecePlusCurrent = getFieldsWithId(boardStatePlusPiecePlusCurrent, FIELD_EMPTY_ID);
            std::vector<Coord> temp;
            std::set_intersection(notCoverableFields.begin(), notCoverableFields.end(),
                                  freeFieldsAfterPiecePlusCurrent.begin(), freeFieldsAfterPiecePlusCurrent.end(),
                                  std::back_inserter(temp));
            notCoverableFields = temp;
            if (notCoverableFields.empty())
              break;
          }
        }
      }
    }


    // valid option
    if (optionPossible && notCoverableFields.empty())
      reducedOptions.push_back(option);
  }

  cout << "Reduced options for " << piece->id() << " from " << options.size() << " to " << reducedOptions.size() << endl;
  return reducedOptions;
}

Piece::Piece(char id, Geometry baseGeometry) :
  _id(id),
  _baseGeometry(baseGeometry)
{
}

void Piece::postInit(const BoardState &boardState, const std::vector<Piece*>& unplacedPieces)
{
  obtainOrientationsFromBase();
  obtainPlaceableOptions(boardState, unplacedPieces);
}

void Piece::drawBaseOrientation() const
{
  Piece::drawGeometry(_baseGeometry);
  cout << endl;
}

void Piece::drawAllOrientations() const
{
  for (size_t i=0; i<_geometryOrientations.size(); i++) {
    cout << "orientation " << i << ": " << endl;
    Piece::drawGeometry(_geometryOrientations[i]);
    cout << endl;
  }
}

const Geometries& Piece::getGeometryOrientations() const
{
  return _geometryOrientations;
}

const std::vector<BoundingBox> &Piece::getGeometryOrientationBoundingBoxes() const
{
  return _geometryOrientationsBoundingBoxes;
}

size_t Piece::getNumOrientations() const
{
  return _geometryOrientations.size();
}

size_t Piece::getNumInitialPlaceableOptions() const
{
  return _initialPlacableOptions.size();
}

char Piece::id() const
{
  return _id;
}

size_t Piece::getExtent() const
{
  return _baseGeometry.size();
}

void Piece::drawGeometry(const Geometry &geometry)
{
  int maxX = 0;
  int maxY = 0;
  for (const auto &entry : geometry) {
    maxX = std::max(maxX, entry.x);
    maxY = std::max(maxY, entry.y);
  }

  // note: col=x, row=y
  for (int r=0; r<=maxY; r++) {
    for (int c=0; c<=maxX; c++) {
      bool found = std::find(geometry.begin(), geometry.end(), Coord(c, r)) != geometry.end();
      cout << (found ? "*" : " ");
    }
    cout << endl;
  }
}

Geometry Piece::transformGeometry(const Geometry &geometry, GeometryModification modification)
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

void Piece::obtainOrientationsFromBase()
{
  auto getBBX = [](const Geometry& geometry)
  {
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();
    for (const auto& entry : geometry) {
      if (entry.x < minX)
        minX = entry.x;
      if (entry.y < minY)
        minY = entry.y;
      if (entry.x > maxX)
        maxX = entry.x;
      if (entry.y > maxY)
        maxY = entry.y;
    }
    return std::make_pair(Coord(minX, minY), Coord(maxX, maxY));
  };
  using SortedGeometry = std::set<Coord>;

  std::set<SortedGeometry> knownOrientationsSorted;
  _geometryOrientations.clear();
  _geometryOrientationsBoundingBoxes.clear();

  // insert base
  SortedGeometry baseSorted;
  for (const auto &entry : _baseGeometry) {
    baseSorted.insert(entry);
  }
  knownOrientationsSorted.insert(baseSorted);
  _geometryOrientations.push_back(_baseGeometry);
  _geometryOrientationsBoundingBoxes.push_back(getBBX(_baseGeometry));

  // check other possible orientation (avoid duplicates)
  for (const auto& t : {GeometryModification::Rotated90,
                        GeometryModification::Rotated180,
                        GeometryModification::Rotated270,
                        GeometryModification::Mirrored,
                        GeometryModification::MirroredRotated90,
                        GeometryModification::MirroredRotated180,
                        GeometryModification::MirroredRotated270})
  {
    auto transformed = Piece::transformGeometry(_baseGeometry, t);
    SortedGeometry transformedSorted;
    for (const auto &entry : transformed) {
      transformedSorted.insert(entry);
    }
    if (knownOrientationsSorted.find(transformedSorted) == knownOrientationsSorted.end()) {
      knownOrientationsSorted.insert(transformedSorted);
      _geometryOrientations.push_back(transformed);
        _geometryOrientationsBoundingBoxes.push_back(getBBX(transformed));
    }
  }
  //cout << "Piece " << _id << " has " << getNumGeometries() << " orientations" << endl;
}

void Piece::obtainPlaceableOptions(const BoardState &boardState, const std::vector<Piece*>& unplacedPieces)
{
  _initialPlacableOptions = determinePlaceableOptions(boardState, this, unplacedPieces);
  cout << "Piece " << _id << " has " << getNumInitialPlaceableOptions() << " placeable options on the board" << endl;
}
