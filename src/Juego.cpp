#include "Juego.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>

Juego::Juego()
    : ventana(Tablero::ANCHO * BLOCK_SIZE, Tablero::ALTO * BLOCK_SIZE, "Tetris SFML"), gameOver(false) {
    piezaActual = nullptr;
}

void Juego::nuevaPieza() {
    if (piezaActual) delete piezaActual;
    piezaActual = new Pieza(rand() % 7); // Crea una pieza aleatoria
    piezaActual->x = 3; piezaActual->y = 0;
    if (tablero.colision(*piezaActual)) gameOver = true;
}

void Juego::jugar() {
    Ventana ventana(Tablero::ANCHO * BLOCK_SIZE, Tablero::ALTO * BLOCK_SIZE, "Tetris SFML");
    sf::Clock clock;
    float timer = 0, delay = 0.5;

    nuevaPieza();

    while (ventana.estaAbierta() && !gameOver) {
        float time = clock.restart().asSeconds();
        timer += time;

        sf::Event e;
        while (ventana.obtenerEvento(e)) {
            if (e.type == sf::Event::Closed)
                ventana.getWindow().close();
            Controles::Accion accion = Controles::procesarEvento(e);
            switch (accion) {
                case Controles::MoverIzquierda:
                    piezaActual->x--; if (tablero.colision(*piezaActual)) piezaActual->x++;
                    break;
                case Controles::MoverDerecha:
                    piezaActual->x++; if (tablero.colision(*piezaActual)) piezaActual->x--;
                    break;
                case Controles::Bajar:
                    piezaActual->y++; 
                    if (tablero.colision(*piezaActual)) { 
                        piezaActual->y--; 
                        tablero.fijarPieza(*piezaActual); 
                        tablero.limpiarLineas(); 
                        nuevaPieza(); 
                    }
                    break;
                case Controles::Rotar:
                    piezaActual->rotar(); 
                    if (tablero.colision(*piezaActual)) piezaActual->rotar();
                    break;
                case Controles::Salir:
                    ventana.getWindow().close();
                    break;
                default:
                    break;
            }
        }

        if (timer > delay) {
            piezaActual->y++;
            if (tablero.colision(*piezaActual)) {
                piezaActual->y--;
                tablero.fijarPieza(*piezaActual);
                tablero.limpiarLineas();
                nuevaPieza();
            }
            timer = 0;
        }

        ventana.limpiar();

        // Dibuja el tablero
        for (int i = 0; i < Tablero::ALTO; ++i) {
            for (int j = 0; j < Tablero::ANCHO; ++j) {
                if (tablero.matriz[i][j]) {
                    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE-2, BLOCK_SIZE-2));
                    // Cambia el color según el valor almacenado (tipo de pieza)
                    switch (tablero.matriz[i][j]) {
                        case 1: block.setFillColor(sf::Color::Cyan); break;    // I
                        case 2: block.setFillColor(sf::Color::Yellow); break;  // O
                        case 3: block.setFillColor(sf::Color::Magenta); break; // T
                        case 4: block.setFillColor(sf::Color::Green); break;   // S
                        case 5: block.setFillColor(sf::Color::Red); break;     // Z
                        case 6: block.setFillColor(sf::Color::Blue); break;    // J
                        case 7: block.setFillColor(sf::Color(255,140,0)); break; // L (naranja)
                        default: block.setFillColor(sf::Color::White); break;
                    }
                    block.setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);
                    ventana.getWindow().draw(block);
                }
            }
        }

        // Dibuja la pieza actual
        for (size_t i = 0; i < piezaActual->forma.size(); ++i)
            for (size_t j = 0; j < piezaActual->forma[0].size(); ++j)
                if (piezaActual->forma[i][j]) {
                    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE-2, BLOCK_SIZE-2));
                    // Usa el color según el tipo de pieza actual
                    switch (piezaActual->tipo + 1) {
                        case 1: block.setFillColor(sf::Color::Cyan); break;
                        case 2: block.setFillColor(sf::Color::Yellow); break;
                        case 3: block.setFillColor(sf::Color::Magenta); break;
                        case 4: block.setFillColor(sf::Color::Green); break;
                        case 5: block.setFillColor(sf::Color::Red); break;
                        case 6: block.setFillColor(sf::Color::Blue); break;
                        case 7: block.setFillColor(sf::Color(255,140,0)); break;
                        default: block.setFillColor(sf::Color::White); break;
                    }
                    block.setPosition((piezaActual->x + j) * BLOCK_SIZE, (piezaActual->y + i) * BLOCK_SIZE);
                    ventana.getWindow().draw(block);
                }

        ventana.mostrar();
    }
    delete piezaActual;
}