#include "grid_gamm.hpp"

Grid_gamm::Grid_gamm(int M, int N, int gh) {
  // M pocet bunek ve smeru i
  // N pocet bunek ve smeru j
  // gh pocet pomocnyxh vrstev

  Mvolumes = M;
  Nvolumes = N;
  Mnodes = M+1;
  Nnodes = N+1;
  ghost = gh;

  nodes.allocate(-ghost, Mnodes+ghost, -ghost, Nnodes+ghost);
  facesI.allocate(-ghost, Mvolumes+ghost, -ghost, Nnodes+ghost);
  facesJ.allocate(-ghost, Mnodes+ghost, -ghost, Nvolumes+ghost);
  volumes.allocate(-ghost, Mvolumes+ghost, -ghost, Nvolumes+ghost);

  // generovani souradnic
  double dx = 3./Mvolumes;

  for (i=0; i<Mnodes; i++) {
    double x = i*dx;
    
    for (int j=0; j<Nnodes; j++) {
      double y1 = 1.;
      double y0 = 0;

      if (x >= 1. && x <= 2.) y0 = sqrt(1.3*1.3 - pow(x-1.5, 2)) - 1.2;

      double dy = (y1 - y0) / Nnodes;
      double y = y0 + i*dy;

      nodes[i][j].vertex = Point2d(x, y);
    }
  }

  // pomocne vrcholy ve smeru i

  for (int j=0; j<Nnodes; j++) {
    Vector2d s(node[1][j], node[0][j]);
    for (int k=1; k<=ghost; k++) {
      nodes[-k][j].vertex = node[0][j] + k*s;
    }

    s = Vector2d(node[Mnodes-2][j], node[Mnodes-1][j]);
    for (int k=1; k<=ghost; k++) {
      nodes[Mnodes-1+k].vertex = node[Mnodes-1][j] + k*s;
    }
  }

  // pomocne vrcholy ve smeru j

  for (int i=-ghost; i<Mnodes+ghost; i++) {
    Vector2d s(node[i][1], node[i][0]);
    for (int k=1; k<=ghost; k++) {
      nodes[i][-k].vertex = node[i][0] + k*s;
    }

    s = Vector2d(node[i][Nnodes-2], node[i][Nnodes-1]);
    for (int k=1; k<=ghost; k++) {
      nodes[i][Nnodes-1+k].vertex = node[i][Nodes-1] + k*s;
    }
  }

  // vypocet stredu bunek
  for (int i=-ghost; i<Mvolumes+ghost; i++) {
    for (int j=-ghost; j<Nvolumes+ghost; j++) {
      centers[i][j] = (node[i][j] + node[i+1][j] + node[i+1][j+1] + node[i][j+1]) / 4.;
    }
  }

  // vypocet objemu bunek
  for (int i=-ghost; i<Mvolumes+ghost; i++) {
    for (int j=-ghost; j<Nvolumes+ghost; j++) {
      Vector2d s1(node[i][j], node[i+1][j+1]);
      Vector2d s2(node[i+1][j], node[i][j+1]);

      volumes[i][j] = fabs(cross(s1, s2)) / 2.;
    }
  }
      
}
