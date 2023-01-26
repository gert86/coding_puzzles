#ifndef PIECE_H
#define PIECE_H

#include "Types.h"

class Piece
{
public:
  // Note: Providing unplaced pieces filters out some more options, but is much slower
  static std::vector<BoardPlacementEntry> determinePlaceableOptions(const BoardState& boardState, const Piece* piece, const std::vector<Piece*>& unplacedPieces = {});

public:
  Piece(char id, Geometry baseGeometry);
  void postInit(const BoardState& boardState, const std::vector<Piece*>& unplacedPieces);
  void drawBaseOrientation() const;
  void drawAllOrientations() const;
  const Geometries& getGeometryOrientations() const;
  const std::vector<BoundingBox>& getGeometryOrientationBoundingBoxes() const;
  size_t getNumOrientations() const;
  size_t getNumInitialPlaceableOptions() const;
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
  void obtainPlaceableOptions(const BoardState& boardState, const std::vector<Piece*>& unplacedPieces);

private:
  Geometries _geometryOrientations;
  std::vector<BoundingBox> _geometryOrientationsBoundingBoxes;
  std::vector<BoardPlacementEntry> _initialPlacableOptions;
};

#endif // PIECE_H
