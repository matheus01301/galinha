#include "Sculptor.h"

int main() {
  Sculptor galinha(20, 20, 20);
    galinha.setColor(1, 1, 1, 1.0); // Cor roxa
    galinha.putBox(1, 8, 1, 6, 5, 10);

    // cabeça
    galinha.putBox(8, 10, 2, 5, 9, 14);

    // asas
    galinha.putBox(2, 7, 7, 7, 7, 10);
    galinha.putBox(2, 7, 0, 0, 7, 10);

    // patas
    galinha.setColor(0.568, 0.423, 0.01, 1.0);
    galinha.putBox(3, 3, 2, 2, 2, 4);
    galinha.putBox(3, 3, 5, 5, 2, 4);

    // pés
    galinha.putBox(4, 5, 1, 6, 2, 2);

    // olhos
    galinha.setColor(0, 0, 0, 1.0);
    galinha.putVoxel(10, 5, 13);
    galinha.putVoxel(10, 2, 13);

    // bico
    galinha.setColor(1, 0.968, 0, 1.0);
    galinha.putBox(11, 12, 2, 5, 11, 12);

    // papo
    galinha.setColor(1, 0, 0, 1.0);
    galinha.putBox(11, 11, 3, 4, 9, 10);

    galinha.writeOFF("galinha.off");

  return 0;
}
