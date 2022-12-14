#ifndef COMPUTE_REZ_HPP
#define COMPUTE_REZ_HPP

#include "grid.hpp"
#include "cellField.hpp"

template <typename var>
void compute_rez(const CellField<var>& w, const Grid& g, CellField<var>& rez) {
  // vynulovani rezidua
  for (int i=rez.Imin(); i<rez.Imax(); i++) {
    for (int j=rez.Jmin(); j<rez.Jmax(); j++) {
      rez[i][j].zero();
    }
  }

  // vypocet toku stenami ve smeru i
  for (int i=0; i<w.M(); i++) {
    for (int j=0; j<w.N()+1; j++) {
      const var& wl = w[i][j];
      const var& wr = w[i][j-1];

      const Vector2d& s = g.faceI(i,j);

      var flx = var::flux(wl, wr, s);

      rez[i][j] += flx;
      rez[i][j-1] -= flx;
    }
  }

  // vypocet toku stenami ve smeru j
  for (int i=0; i<w.M()+1; i++) {
    for (int j=0; j<w.N(); j++) {
      const var& wl = w[i-1][j];
      const var& wr = w[i][j];

      const Vector2d& s = g.faceJ(i,j);

      var flx = var::flux(wl, wr, s);

      rez[i-1][j] += flx;
      rez[i][j] -= flx;
    }
  }

  // vydeleni objemem bunky a prenasobeni minus 1
  for (int i=0; i<rez.M(); i++) {
    for (int j=0; j<rez.N(); j++) {
      rez[i][j] = -1. * rez[i][j] / g.volume(i,j);
    }
  }
  
}

#endif
