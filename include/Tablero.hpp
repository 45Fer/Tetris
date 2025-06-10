#pragma once
#include <vector>
#include "Pieza.hpp"

class Tablero {
public:
    static const int ANCHO = 10;
    static const int ALTO = 20;
    std::vector<std::vector<int>> matriz;

    Tablero();
    bool colision(const Pieza& pieza) const;
    void fijarPieza(const Pieza& pieza);
    void limpiarLineas();
    void dibujar() const;
};
