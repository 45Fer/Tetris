#pragma once
#include "Tablero.hpp"
#include "Pieza.hpp"
#include "Ventana.hpp"
#include "Controles.hpp"
#include "Constantes.hpp"

class Juego {
public:
    Juego();
    void jugar();
private:
    Ventana ventana;
    Tablero tablero;
    Pieza* piezaActual;
    bool gameOver;
    void nuevaPieza();
};
