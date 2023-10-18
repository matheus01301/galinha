#ifndef SCULPTOR_H
#define SCULPTOR_H

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

struct Voxel {
  float r, g, b, a;  // Cores e transparência
  bool show = false; // Ativado ou desativado
};

class Sculptor {
private:
  Voxel ***v;       // Matriz 3D de voxels
  int nx, ny, nz;   // Dimensões da matriz
  float r, g, b, a; // Cor atual

public:
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();
  void setColor(float r, float g, float b, float a);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry,
                    int rz);
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry,
                    int rz);
  void writeOFF(const char *filename);
};

#endif // SCULPTOR_H
