#ifndef PIECE_H
#define PIECE_H

#include "Types.h"

class Piece
{
public:
  // determine all possible options to place the given piece on the given board
  static std::vector<BoardPlacementEntry> determinePlaceableOptions(const BoardState& boardState, const Piece* piece, bool constrainToInitialPlaceableOptions);

  // further filter out options that lead to dead-ends w.r.t. yet unplaced pieces -> takes some time
  static std::vector<BoardPlacementEntry> reducePlaceableOptions(const std::vector<BoardPlacementEntry>& originalPlaceableOptions,
                                                                 const BoardState& boardState,
                                                                 const Piece* piece,
                                                                 const std::vector<Piece*>& unplacedPieces);

public:
  Piece(char id, Geometry baseGeometry);
  void postInit(const BoardState& boardState);
  void drawBaseOrientation() const;
  void drawAllOrientations() const;
  const Geometries& getGeometryOrientations() const;
  const std::vector<BoundingBox>& getGeometryOrientationBoundingBoxes() const;
  size_t getNumOrientations() const;
  std::vector<BoardPlacementEntry> getInitialPlaceableOptions() const;
  void setInitialPlaceableOptions(const std::vector<BoardPlacementEntry>& initialOptions);  // only if read from cache
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
  void obtainPlaceableOptions(const BoardState& boardState);

private:
  Geometries _geometryOrientations;
  std::vector<BoundingBox> _geometryOrientationsBoundingBoxes;
  std::vector<BoardPlacementEntry> _initialPlacableOptions;
};

#endif // PIECE_H
