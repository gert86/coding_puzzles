#ifndef TYPES_H
#define TYPES_H

#include "base_header.h"

enum FieldState
{
  Free = 0,
  Occupied,
  Unavailable
};
using BoardState = std::vector<std::vector<FieldState>>;

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


struct BoardPlacementEntry
{
  int _geometryIndex{-1};
  Coord _coordOnBoard{-1,-1};

  BoardPlacementEntry() = default;
  BoardPlacementEntry(int g, const Coord& c) :
    _geometryIndex(g),
    _coordOnBoard(Coord(c.x, c.y))
  {}
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

#endif // TYPES_H
