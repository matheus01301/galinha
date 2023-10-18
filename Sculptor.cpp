#include "Sculptor.h"

// O construtor aloca dinamicamente um array tridimensional de voxels com as dimensões especificadas (nx, ny, nz).
Sculptor ::Sculptor(int _nx, int _ny, int _nz) {
  nx = _nx;
  ny = _ny;
  nz = _nz;

  // alocação dinâmica
  v = new Voxel **[nx];
  for (int i = 0; i < nx; i++) {
    v[i] = new Voxel *[ny];
    for (int j = 0; j < ny; j++) {
      v[i][j] = new Voxel[nz];
    }
  }
}

// O destrutor libera a memória alocada para os voxels quando o objeto Sculptor é destruído.
Sculptor ::~Sculptor() {

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      delete[] v[i][j];
    }
    delete[] v[i];
  }
  delete[] v;
}

// Define a cor atual para os voxels que serão desenhados na escultura. Os parâmetros especificam os componentes de cor RGBA (vermelho, verde, azul, alfa).
void Sculptor ::setColor(float _r, float _g, float _b, float _a) {
  r = _r;
  g = _g;
  b = _b;
  a = _a;
}

// Ativa um voxel na posição (x, y, z) e atribui a ele a cor atual definida por setColor.
void Sculptor ::putVoxel(int x, int y, int z) {
  v[x][y][z].show = true;
  v[x][y][z].r = r;
  v[x][y][z].g = g;
  v[x][y][z].b = b;
  v[x][y][z].a = a;
}

// Desativa (remove) um voxel na posição (x, y, z).
void Sculptor ::cutVoxel(int x, int y, int z) { v[x][y][z].show = false; }

  // Ativa voxels em forma de cubo dentro das coordenadas especificadas.
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int i = x0; i <= x1; i++) {
    for (int j = y0; j <= y1; j++) {
      for (int k = z0; k <= z1; k++) {
        putVoxel(i, j, k);
      }
    }
  }
}

  // Desativa (remove) voxels em forma de cubo dentro das coordenadas especificadas.
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int i = x0; i <= x1; i++) {
    for (int j = y0; j <= y1; j++) {
      for (int k = z0; k <= z1; k++) {
        cutVoxel(i, j, k);
      }
    }
  }
}
    // Ativa voxels em forma de esfera com o centro e raio especificados.
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        float dx = i - xcenter;
        float dy = j - ycenter;
        float dz = k - zcenter;
        float distance = sqrt(dx * dx + dy * dy + dz * dz);
        if (distance <= radius) {
          putVoxel(i, j, k);
        }
      }
    }
  }
}

    // Desativa (remove) voxels em forma de esfera com o centro e raio especificados.
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if ((i - xcenter) * (i - xcenter) + (j - ycenter) * (j - ycenter) +
                (k - zcenter) * (k - zcenter) <=
            radius * radius) {
          cutVoxel(i, j, k);
        }
      }
    }
  }
}

    // Ativa voxels em forma de elipsóide com o centro e raios especificados.
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        float normalizedX = static_cast<float>(i - xcenter) / rx;
        float normalizedY = static_cast<float>(j - ycenter) / ry;
        float normalizedZ = static_cast<float>(k - zcenter) / rz;
        float distance = normalizedX * normalizedX + normalizedY * normalizedY +
                         normalizedZ * normalizedZ;

        if (distance <= 1.0) {
          putVoxel(i, j, k);
        }
      }
    }
  }
}

    // Desativa (remove) voxels em forma de elipsóide com o centro e raios especificados.
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz) {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        float normalizedX = static_cast<float>(i - xcenter) / rx;
        float normalizedY = static_cast<float>(j - ycenter) / ry;
        float normalizedZ = static_cast<float>(k - zcenter) / rz;
        float distance = normalizedX * normalizedX + normalizedY * normalizedY +
                         normalizedZ * normalizedZ;

        if (distance <= 1.0) {
          cutVoxel(i, j, k);
        }
      }
    }
  }
}

// Gera um arquivo no formato OFF (um formato de arquivo para representar objetos 3D) contendo a representação da escultura atual. Este arquivo pode ser usado para visualização ou renderização em software de modelagem 3D.
void Sculptor::writeOFF(char const *filename) {
  std::ofstream outfile(filename);
  if (!outfile.is_open()) {
    std::cerr << "Erro." << std::endl;
    return;
  }

  int numVertices = 0;
  int numFaces = 0;

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          numVertices += 8;
          numFaces += 6;
        }
      }
    }
  }

  outfile << "OFF" << std::endl;
  outfile << numVertices << " " << numFaces << " 0" << std::endl;

  // Escreva as coordenadas dos vértices
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          outfile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          outfile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          outfile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          outfile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          outfile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
          outfile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
          outfile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
          outfile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
        }
      }
    }
  }

  // Escreva os índices das faces
  int offset = 0;
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          outfile << std::fixed
                  << std::setprecision(2);
          outfile << "4 " << 0 + offset << " " << 3 + offset << " "
                  << 2 + offset << " " << 1 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          outfile << "4 " << 4 + offset << " " << 5 + offset << " "
                  << 6 + offset << " " << 7 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          outfile << "4 " << 0 + offset << " " << 1 + offset << " "
                  << 5 + offset << " " << 4 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          outfile << "4 " << 0 + offset << " " << 4 + offset << " "
                  << 7 + offset << " " << 3 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          outfile << "4 " << 1 + offset << " " << 2 + offset << " "
                  << 6 + offset << " " << 5 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          outfile << "4 " << 2 + offset << " " << 3 + offset << " "
                  << 7 + offset << " " << 6 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          offset += 8;
        }
      }
    }
  }

  // Feche a seção OFF
  outfile.close();

  std ::cout << "Arquivo " << filename << " criado" << std::endl;
}
