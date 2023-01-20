#include "Piece.h"
#include "Board.h"

std::vector<BoardPlacementEntry> Piece::determinePlaceableOptions(const BoardState &boardState, Piece *piece)
{
  std::vector<BoardPlacementEntry> options;
  BoardState dummy;
  for(size_t c=0; c < piece->getNumGeometries(); c++) {
    for(size_t y=0; y < boardState.size(); y++) {
      for(size_t x=0; x < boardState[0].size(); x++) {
        Coord coord(x, y);
        if (Board::isPlaceable(piece, c, coord, boardState, dummy)) {
          options.emplace_back(c, coord);
        }
      }
    }
  }
  return options;
}

void Piece::postInit(const BoardState &boardState)
{
  obtainGeometriesFromBase();
  obtainPlaceableOptions(boardState);
}

void Piece::drawBaseConfiguration() const
{
  Piece::drawGeometry(_baseGeometry);
  cout << endl;
}

void Piece::drawAllConfigurations() const
{
  for (size_t i=0; i<_geometryConfigurations.size(); i++) {
    cout << "Configuration " << i << ": " << endl;
    Piece::drawGeometry(_geometryConfigurations[i]);
    cout << endl;
  }
}

const Geometries& Piece::getGeometryConfigs() const
{
  return _geometryConfigurations;
}

size_t Piece::getNumGeometries() const
{
  return _geometryConfigurations.size();
}

const std::vector<BoardPlacementEntry>& Piece::getPlaceableOptions() const
{
  return _placableOptions;
}

size_t Piece::getNumPlaceableOptions() const
{
  return _placableOptions.size();
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

void Piece::obtainGeometriesFromBase()
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
  //cout << "Piece " << _id << " has " << getNumGeometries() << " configurations" << endl;
}

void Piece::obtainPlaceableOptions(const BoardState &boardState)
{
  _placableOptions = determinePlaceableOptions(boardState, this);
  //cout << "Piece " << _id << " has " << getPlaceableOptions().size() << " placeable options on the board" << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PieceA::init()
{
  _id = 'A';
  _baseGeometry = {{1,0}, {1,1}, {1,2}, {0,2}};
}

void PieceB::init()
{
  _id = 'B';
  _baseGeometry = {{1,0}, {0,1}, {1,1}, {0,2}, {1,2}};
}

void PieceC::init()
{
  _id = 'C';
  _baseGeometry = {{1,0}, {1,1}, {1,2}, {1,3}, {0,3}};
}

void PieceD::init()
{
  _id = 'D';
  _baseGeometry = {{1,0}, {1,1}, {1,2}, {1,3}, {0,2}};
}

void PieceE::init()
{
  _id = 'E';
  _baseGeometry = {{1,0}, {1,1}, {1,2}, {0,2}, {0,3}};
}

void PieceF::init()
{
  _id = 'F';
  _baseGeometry = {{1,0}, {1,1}, {0,1}};
}

void PieceG::init()
{
  _id = 'G';
  _baseGeometry = {{2,0}, {2,1}, {2,2}, {1,2}, {0,2}};
}

void PieceH::init()
{
  _id = 'H';
  _baseGeometry = {{2,0}, {2,1}, {1,1}, {1,2}, {0,2}};
}

void PieceI::init()
{
  _id = 'I';
  _baseGeometry = {{0,0}, {0,1}, {1,1}, {2,1}, {2,0}};
}

void PieceJ::init()
{
  _id = 'J';
  _baseGeometry = {{0,0}, {0,1}, {0,2}, {0,3}};
}

void PieceK::init()
{
  _id = 'K';
  _baseGeometry = {{0,0}, {0,1}, {1,1}, {1,0}};
}

void PieceL::init()
{
  _id = 'L';
  _baseGeometry = {{1,0}, {0,1}, {1,1}, {2,1}, {1,2}};
}
