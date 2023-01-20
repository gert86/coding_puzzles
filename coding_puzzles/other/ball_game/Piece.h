#ifndef PIECE_H
#define PIECE_H

#include "Types.h"

class Piece
{
// Helper functions
private:
  static void drawGeometry(const Geometry& geometry);

  static Geometry transformGeometry(const Geometry& geometry, GeometryModification modification);

  // adds up to 7 additional geometries through rotation and mirroring
  void obtainGeometriesFromBase();

  void obtainPlaceableOptions(const BoardState& boardState);

private:
  Geometries _geometryConfigurations;
  std::vector<BoardPlacementEntry> _placableOptions;

protected:
  virtual void init() = 0;         // defines base geometry

protected:
  char _id;
  Geometry _baseGeometry;

public:
  // TODO: make sure this is called from all derived ones before usage
  void postInit(const BoardState& boardState);

  void drawBaseConfiguration() const;

  void drawAllConfigurations() const;

  const Geometries& getGeometryConfigs() const;

  size_t getNumGeometries() const;

  const std::vector<BoardPlacementEntry>& getPlaceableOptions() const;

  size_t getNumPlaceableOptions() const;

  char id() const;

  size_t getExtent() const;
};

class PieceC : public Piece
{
public:
  PieceC();

private:
  void init() override;
};

class PieceJ : public Piece
{
public:
  PieceJ();

private:
  void init() override;
};



#endif // PIECE_H
