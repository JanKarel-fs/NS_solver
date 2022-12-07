#ifndef CELLFIELD_HPP
#define CELLFIELD_HPP

#include <iostream>
#include <cstdlib>
#include "../geometry/field.hpp"
#include "grid.hpp"

using namespace std;

template <typename T>
class CellField {
  Field2<T> data;

  int m;        // pocet bunek ve smeru i
  int n;        // pocet bunek ve smeru j
  int ghost;    // pocet pomocnych vrstev

public:
  CellField() {};

  CellField(const int M, const int N, const int gh): m(M), n(N), ghost(gh) {
    data.allocate(-ghost, m+ghost, -ghost, n+ghost);
  };

  CellField(const Grid& g) {
    m = g.Mvol();
    n = g.Nvol();
    ghost = g.GhNum();

    data.allocate(-ghost, m+ghost, -ghost, n+ghost);
  };

  ~CellField() {};

  inline T* operator[](const int& i) const {
    return data[i];
  }

  int M() const {return m;}
  int N() const {return n;}
  int GhNum() const {return ghost;}
  int Imin() const {return data.Imin();}
  int Imax() const {return data.Imax();}
  int Jmin() const {return data.Jmin();}
  int Jmax() const {return data.Jmax();}

  Cellfield& operator=(const CellField& cf) {
    if (m != cf.M() || n != cf.N() || ghost != cf.GhNum()) {
      cout << "Nelze priradit hodnoty z pole CellField jine velikosti!" << endl;
      exit(2);
    }

    for (int i=-ghost; i<m+ghost; i++) {
      for (int j=-ghost; j<n+ghost; j++) {
	data[i][j] = cf[i][j];
      }
    }

    return *this;
  }
};

template <typename T>
CellField<T> operator+(const CellField<T>& a, const CellField<T>& b) {
  if (a.M() != b.M() || a.N() != b.N() || a.GhNum() != b.GhNum()) {
    cout << "Nelze scitat pole CellField ruznych velikosti!" << endl;
    exit(3);
  }

  CellField<T> c(a.M(), a.N(), a.GhNum());

  for (int i=a.Imin(); i<a.Imax(); i++) {
    for (int j=a.Jmin(); j, a.Jmax(); j++) {
      c[i][j] = a[i][j] + b[i][j];
    }
  }

  return c;
}

template <typename T>
CellField<T> operator-(const CellField<T>& a, const CellField<T>& b) {
  if (a.M() != b.M() || a.N() != b.N() || a.GhNum() != b.GhNum()) {
    cout << "Nelze odecitat pole CellField ruznych velikosti!" << endl;
    exit(3);
  }

  CellField<T> c(a.M(), a.N(), a.GhNum());

  for (int i=a.Imin(); i<a.Imax(); i++) {
    for (int j=a.Jmin(); j, a.Jmax(); j++) {
      c[i][j] = a[i][j] - b[i][j];
    }
  }

  return c;
}

template <typename T, typename S>
CellField<T> operator*(const CellField<T>& a, const S& b) {
  CellField<T> c(a.M(), a.N(), a.GhNum());

  for (int i=a.Imin(); i<a.Imax(); i++) {
    for (int j=a.Jmin(); j<a.Jmax(); j++) {
      c[i][j] = a[i][j] * b;
    }
  }

  return c;
}

template <typename T, typename S>
CellField<T> operator*(const S& b, const CellField<T>& a) {
  CellField<T> c(a.M(), a.N(), a.GhNum());

  for (int i=a.Imin(); i<a.Imax(); i++) {
    for (int j=a.Jmin(); j<a.Jmax(); j++) {
      c[i][j] = a[i][j] * b;
    }
  }

  return c;
}

template <typename T, typename S>
CellField<T> operator/(const CellField<T>& a, const S& b) {
  CellField<T> c(a.M(), a.N(), a.GhNum());

  for (int i=a.Imin(); i<a.Imax(); i++) {
    for (int j=a.Jmin(); j<a.Jmax(); j++) {
      c[i][j] = a[i][j] / b;
    }
  }

  return c;
}

#endif
