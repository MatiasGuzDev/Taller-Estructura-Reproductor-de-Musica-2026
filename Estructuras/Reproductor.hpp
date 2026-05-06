//
// Created by marti on 06-05-2026.
//

#ifndef TALLER_ESTRUCTURA_REPRODUCTOR_DE_MUSICA_2026_REPRODUCTOR_HPP
#define TALLER_ESTRUCTURA_REPRODUCTOR_DE_MUSICA_2026_REPRODUCTOR_HPP

#include <string>
#include "Cancion.hpp"
#include "LinkedList.h"

class Reproductor {
private:
    int id_actual;
    std::string estado;
    bool modo_aleatorio;
    int modo_repeticion;
    Cancion cancion_actual;
    LinkedList<Cancion>lista_canciones;
    LinkedList<Cancion> lista_reproduccion;

public:
    Reproductor();
    void cargarArchivos();
    void guardarEstado();
    void seleccionarCancionInicial();
    void reproducirPausar();
    void pistaSiguiente();
    void pistaAnterior();
    void alternarModoAleatorio();
    void alternarRepeticion();
    void verListaReproduccion();
    void verListadoCanciones();
    void mostrarMenuPrincipal();
};

#endif //TALLER_ESTRUCTURA_REPRODUCTOR_DE_MUSICA_2026_REPRODUCTOR_HPP
