#ifndef TYPES_H
#define TYPES_H

#include "base_header.h"

constexpr char FIELD_EMPTY_ID = ' ';
constexpr char FIELD_UNAVAILABLE_ID = '.';

using BoardState = std::vector<std::vector<char>>;

struct Coord
{
  int x{-1};
  int y{-1};

  Coord() = default;
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
    return std::tie(lhs.x,lhs.y) == std::tie(rhs.x, rhs.y);
}

struct BoardPlacementEntry
{
  int _orientationIdx{-1};
  Coord _topLeftOnBoard{-1,-1};

  BoardPlacementEntry() = default;
  BoardPlacementEntry(int g, const Coord& c) :
    _orientationIdx(g),
    _topLeftOnBoard(Coord(c.x, c.y))
  {}
};

using Geometry = std::vector<Coord>;
using Geometries = std::vector<Geometry>;

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

#endif // TYPES_H
