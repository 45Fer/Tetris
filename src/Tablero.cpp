#include "Tablero.hpp"
#include <iostream>

Tablero::Tablero() : matriz(ALTO, std::vector<int>(ANCHO, 0)) {}

bool Tablero::colision(const Pieza& pieza) const {
    for (size_t i = 0; i < pieza.forma.size(); ++i)
        for (size_t j = 0; j < pieza.forma[0].size(); ++j)
            if (pieza.forma[i][j]) {
                int nx = pieza.x + j;
                int ny = pieza.y + i;
                if (nx < 0 || nx >= ANCHO || ny < 0 || ny >= ALTO || matriz[ny][nx])
                    return true;
            }
    return false;
}

void Tablero::fijarPieza(const Pieza& pieza) {
    for (size_t i = 0; i < pieza.forma.size(); ++i)
        for (size_t j = 0; j < pieza.forma[0].size(); ++j)
            if (pieza.forma[i][j]) {
                int nx = pieza.x + j;
                int ny = pieza.y + i;
                if (ny >= 0 && ny < ALTO && nx >= 0 && nx < ANCHO)
                    matriz[ny][nx] = pieza.tipo + 1;
            }
}

void Tablero::limpiarLineas() {
    for (int i = ALTO-1; i >= 0; --i) {
        bool llena = true;
        for (int j = 0; j < ANCHO; ++j)
            if (!matriz[i][j]) llena = false;
        if (llena) {
            matriz.erase(matriz.begin() + i);
            matriz.insert(matriz.begin(), std::vector<int>(ANCHO, 0));
            ++i;
        }
    }
}

void Tablero::dibujar() const {
    system("cls");
    for (int i = 0; i < ALTO; ++i) {
        for (int j = 0; j < ANCHO; ++j)
            std::cout << (matriz[i][j] ? "#" : ".");
        std::cout << "\n";
    }
}