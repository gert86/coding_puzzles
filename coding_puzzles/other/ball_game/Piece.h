#ifndef PIECE_H
#define PIECE_H

#include "Types.h"

class Piece
{
public:
  static std::vector<BoardPlacementEntry> determinePlaceableOptions(const BoardState& boardState, Piece* piece);

public:
  void postInit(const BoardState& boardState);  // TODO: make sure this is called from all derived instances before usage
  void drawBaseorientation() const;
  void drawAllorientations() const;
  const Geometries& getGeometryOrientations() const;
  size_t getNumOrientations() const;
  const std::vector<BoardPlacementEntry>& getPlaceableOptions() const;
  size_t getNumPlaceableOptions() const;
  char id() const;
  size_t getExtent() const;

protected:
  //! defines base geometry
  virtual void init() = 0;

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
  std::vector<BoardPlacementEntry> _placableOptions;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO: Use templates

class PieceA : public Piece
{
public:
  PieceA()
  {
    init();
  }
private:
  void init() override;
};

class PieceB : public Piece
{
public:
  PieceB()
  {
    init();
  }
private:
  void init() override;
};

class PieceC : public Piece
{
public:
  PieceC()
  {
    init();
  }
private:
  void init() override;
};

class PieceD : public Piece
{
public:
  PieceD()
  {
    init();
  }
private:
  void init() override;
};

class PieceE : public Piece
{
public:
  PieceE()
  {
    init();
  }
private:
  void init() override;
};

class PieceF : public Piece
{
public:
  PieceF()
  {
    init();
  }
private:
  void init() override;
};

class PieceG : public Piece
{
public:
  PieceG()
  {
    init();
  }
private:
  void init() override;
};

class PieceH : public Piece
{
public:
  PieceH()
  {
    init();
  }
private:
  void init() override;
};

class PieceI : public Piece
{
public:
  PieceI()
  {
    init();
  }
private:
  void init() override;
};

class PieceJ : public Piece
{
public:
  PieceJ()
  {
    init();
  }
private:
  void init() override;
};

class PieceK : public Piece
{
public:
  PieceK()
  {
    init();
  }
private:
  void init() override;
};

class PieceL : public Piece
{
public:
  PieceL()
  {
    init();
  }
private:
  void init() override;
};


#endif // PIECE_H
