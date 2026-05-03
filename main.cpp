//
// Created by marti on 02-05-2026.
//


#include <iostream>
#include <Reproductor.hpp>

int main() {
    Reproductor reproductor;

    reproductor.cargarArchivos();

    char opcion;
    do {
        std::cout << "\n=========================================\n";
        reproductor.();
        std::cout << "\n=========================================\n";
        std::cout << "Opciones:\n";
        std::cout << "W - Reproducir / Pausar\n";
        std::cout << "Q - Pista Anterior\n";
        std::cout << "E - Pista Siguiente\n";
        std::cout << "S - Activar/Desactivar modo aleatorio\n";
        std::cout << "R - Repetición (Desactivado / Repetir una / Repetir todas)\n";
        std::cout << "A - Ver lista de reproducción actual\n";
        std::cout << "L - Listado de canciones\n";
        std::cout << "X - Salir\n";
        std::cout << "Ingrese una opción: \n";
        std::cin >> opcion;

        switch (opcion) {}

    }













}
