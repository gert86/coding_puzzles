#ifndef PIECE_H
#define PIECE_H

#include "Types.h"

class Piece
{
public:
  static std::vector<BoardPlacementEntry> determinePlaceableOptions(const BoardState& boardState, Piece* piece);

public:
  Piece(char id, Geometry baseGeometry);
  void postInit(const BoardState& boardState);
  void drawBaseOrientation() const;
  void drawAllOrientations() const;
  const Geometries& getGeometryOrientations() const;
  const std::vector<BoundingBox>& getGeometryOrientationBoundingBoxes() const;
  size_t getNumOrientations() const;
  const std::vector<BoardPlacementEntry>& getPlaceableOptions() const;
  size_t getNumPlaceableOptions() const;
  char id() const;
  size_t getExtent() const;

protected:
  char _id;
  Geometry _baseGeometry;

private:
  static void drawGeometry(const Geometry& geometry);
  static Geometry transformGeometry(const Geometry& geometry, GeometryModification modification);

private:
  //! adds up to 7 additional geometries through rotation and mirroring
  void obtainOrientationsFromBase();
  void obtainPlaceableOptions(const BoardState& boardState);

private:
  Geometries _geometryOrientations;
  std::vector<BoundingBox> _geometryOrientationsBoundingBoxes;
  std::vector<BoardPlacementEntry> _placableOptions;
};

#endif // PIECE_H
