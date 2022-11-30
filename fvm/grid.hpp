#ifndef GRID_HPP
#define GRID_HPP

#include "../geometry/point.hpp"
#include "../geometry/vector.hpp"
#include "../geometry/field.hpp"

class Grid;

class Node {
  Point2d vertex;
};

class Face {
  Point2d center;
  Vector2d s;      // normalovy vektor vynasobeny velikosti steny

  void updateI(Grid& g, int i, int j);
  void updateJ(Grid& g, int i, int j);
};

class Grid {
protected:
  int Mnodes;   // pocet uzlu ve smeru i
  int Nnodes;   // pocet uzlu ve smeru j
  int Mvolumes; // pocet bunek ve smeru i
  int Nvolumes; // pocet bunek ve smeru j

  int ghost;    // pocet pomocnych vrstev bunek

  Field2<Node> nodes;
  Field2<Face> facesI;
  Field2<Face> facesJ;
  Field2<double> volumes;
  Field2<Point2d> centers;

public:
  int Mnd() const {return Mnodes;};
  int Nnd() const {return Nnodes;};
  int Mvol() const {return Mvolumes;};
  int Nvol() const {return Nvolumes;};
  int GhNum() const {return ghost;};

  double x(const int& i, const int& j) const;
  double y(const int& i, const int& j) const;
  Point2d node(const int& i, const int& j) const;
  Face faceI(const int& i, const int& j) const;
  Face faceJ(const int& i, const int& j) const;
  double volume(const int& i, const int& j) const;
  Point2d center(const int& i, const int& j) const;

  void update();
};

#endif
