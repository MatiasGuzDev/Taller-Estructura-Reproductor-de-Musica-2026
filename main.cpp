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
        reproductor.mostrarMenuPrincipal();
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

        switch (opcion) {
            case 'w':
            case 'W':
                reproductor.reproducirPausar();
                break;
            case 'q':
            case 'Q':
                reproductor.pistaAnterior();
                break;
            case 'e':
            case 'E':
                reproductor.pistaSiguiente();
                break;
            case 's':
            case 'S':
                reproductor.alternarModoAleatorio();
                break;
            case 'r':
            case 'R':
                reproductor.alternarRepeticion();
                break;
            case 'a':
            case 'A':
                reproductor.verListaReproduccion();
                break;
            case 'l':
            case 'L':
                reproductor.verListadoCanciones();
                break;
            case 'x':
            case 'X':
                reproductor.guardarEstado();
                std::cout << "Saliendo programa...\n";
                break;
            default:
                std::cout << "Opción no válida, intente nuevamente.\n";
        }
    } while (opcion != 'x' && opcion != 'X');
    return 0;
}