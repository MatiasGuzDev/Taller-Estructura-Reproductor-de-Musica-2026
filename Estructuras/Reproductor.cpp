#include "Reproductor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

Reproductor::Reproductor() {
    this->id_actual = 0;
    this->estado = "Reproduccion Detenida";
    this->modo_aleatorio = false;
    this->modo_repeticion = 0;
    std::srand(std::time(nullptr));
}

void Reproductor::cargarArchivos() {

    std::ifstream archivoStatus("../status.cfg");
    if (!archivoStatus.is_open()) {
        std::ofstream nuevoStatus("../status.cfg");
        nuevoStatus << "CONTADOR_IDS 0\n";
        nuevoStatus << "CANCION_ACTUAL Ninguna\n";
        nuevoStatus << "MODO_ALEATORIO 0\n";
        nuevoStatus << "REPETICION 0\n";
        nuevoStatus.close();
    } else {
        std::string parametro, valor;
        while (archivoStatus >> parametro >> valor) {
            if (parametro == "MODO_ALEATORIO") {
                this->modo_aleatorio = (valor == "1");
            } else if (parametro == "REPETICION") {
                this->modo_repeticion = std::stoi(valor);
            }
        }
        archivoStatus.close();
    }


    std::ifstream archivoCanciones("../Estructuras/music_source.txt");


    if (!archivoCanciones.is_open()) {
        std::cout << "\n[ERROR]: El archivo 'music_source.txt' no se encuentra en la carpeta Estructuras." << std::endl;
        return;
    }


    if (archivoCanciones.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "\n[ALERTA]: El archivo 'music_source.txt' esta vacio. No hay canciones para cargar." << std::endl;
        archivoCanciones.close();
        return;
    }

    std::string linea;
    bool seCargoAlMenosUna = false;

    while (std::getline(archivoCanciones, linea)) {
        if (linea.empty()) continue;

        try {
            std::stringstream ss(linea);
            std::string id_str, nombre, artista, album, ano_str, duracion_str, ubicacion;

            std::getline(ss, id_str, ',');
            std::getline(ss, nombre, ',');
            std::getline(ss, artista, ',');
            std::getline(ss, album, ',');
            std::getline(ss, ano_str, ',');
            std::getline(ss, duracion_str, ',');
            std::getline(ss, ubicacion, ',');

            int id = std::stoi(id_str);
            int ano = std::stoi(ano_str);
            int duracion = std::stoi(duracion_str);



            Cancion nuevaCancion(id, nombre, artista, album, ano, duracion, ubicacion);
            lista_canciones.append(nuevaCancion);
            id_actual = id;
            seCargoAlMenosUna = true;
        } catch (...) {

        }
    }

    archivoCanciones.close();

    if (seCargoAlMenosUna) {
        std::cout << "Archivos cargados exitosamente (" << lista_canciones.size() << " canciones).\n";
        seleccionarCancionInicial();
    } else {
        std::cout << "[ALERTA]: El archivo existe pero no contiene datos validos.\n";
    }
}

void Reproductor::seleccionarCancionInicial() {
    if (!lista_canciones.isEmpty()) {
        Cancion primeraCancion = lista_canciones.getFirst();
        this->cancion_actual = primeraCancion;

        if (lista_reproduccion.isEmpty()) {
            lista_reproduccion.append(cancion_actual);
        }
    }
}

void Reproductor::guardarEstado() {
    std::ofstream archivoStatus("../status.cfg");
    if (archivoStatus.is_open()) {
        archivoStatus << "CONTADOR_IDS " << this->id_actual << "\n";
        archivoStatus << "MODO_ALEATORIO " << (this->modo_aleatorio ? 1 : 0) << "\n";
        archivoStatus << "REPETICION " << this->modo_repeticion << "\n";
        archivoStatus.close();
    }
}

void Reproductor::reproducirPausar() {
    if (lista_reproduccion.isEmpty() && !lista_canciones.isEmpty()) {
        lista_reproduccion.append(cancion_actual);
        std::cout << "Anadiendo '" << cancion_actual.getNombreCancion() << "' a la lista...\n";
    }

    if (this->estado == "Reproduciendo") {
        this->estado = "En pausa";
    } else {
        this->estado = "Reproduciendo";
    }

    std::cout << "Estado actual: " << this->estado << "\n";
}

void Reproductor::pistaSiguiente() {
    if (lista_canciones.isEmpty()) {
        std::cout << "No hay canciones cargadas.\n";
        return;
    }

    if (this->modo_repeticion == 1) {
        std::cout << "Modo R1: Repitiendo pista actual.\n";
        return;
    }

    int indiceActual = 0;
    for (int i = 0; i < lista_canciones.size(); i++) {
        if (lista_canciones.get(i).getId() == cancion_actual.getId()) {
            indiceActual = i;
            break;
        }
    }

    int nuevoIndice = (indiceActual + 1) % lista_canciones.size();
    cancion_actual = lista_canciones.get(nuevoIndice);


    lista_reproduccion = LinkedList<Cancion>();
    lista_reproduccion.append(cancion_actual);

    std::cout << "Siguiente pista: " << cancion_actual.getNombreCancion() << "\n";
}

void Reproductor::pistaAnterior() {
    if (lista_canciones.isEmpty()) {
        std::cout << "No hay canciones cargadas.\n";
        return;
    }

    int indiceActual = 0;
    for (int i = 0; i < lista_canciones.size(); i++) {
        if (lista_canciones.get(i).getId() == cancion_actual.getId()) {
            indiceActual = i;
            break;
        }
    }

    int nuevoIndice = (indiceActual - 1 + lista_canciones.size()) % lista_canciones.size();
    cancion_actual = lista_canciones.get(nuevoIndice);

    lista_reproduccion = LinkedList<Cancion>();
    lista_reproduccion.append(cancion_actual);

    std::cout << "Pista anterior: " << cancion_actual.getNombreCancion() << "\n";
}

void Reproductor::alternarModoAleatorio() {
    this->modo_aleatorio = !this->modo_aleatorio;
    guardarEstado();
    std::cout << "Modo aleatorio: " << (this->modo_aleatorio ? "Activado" : "Desactivado") << "\n";
}

void Reproductor::alternarRepeticion() {
    this->modo_repeticion = (this->modo_repeticion + 1) % 3;
    guardarEstado();
    std::cout << "Modo repeticion: " << this->modo_repeticion << " (0:Off, 1:Una, 2:Todas)\n";
}

void Reproductor::verListaReproduccion() {
    std::cout << "\n--- LISTA DE REPRODUCCION ---\n";
    if (lista_reproduccion.isEmpty()) {
        std::cout << "Vacia\n";
    } else {
        lista_reproduccion.display();
    }
    std::cout << "V - Volver | S<num> - Saltar a cancion\n";
}

void Reproductor::verListadoCanciones() {
    std::cout << "\n--- CANCIONES REGISTRADAS ---\n";
    lista_canciones.display();
    std::cout << "V - Volver | R<num> - Reproducir | A<num> - Agregar a cola\n";
}

void Reproductor::mostrarMenuPrincipal() {
    std::cout << "\n====================================\n";
    std::cout << "Estado: " << this->estado << "\n";
    std::cout << "Actual: " << cancion_actual.getNombreCancion() << " [" << (modo_repeticion == 1 ? "R1" : "RA") << "]\n";
    std::cout << "====================================\n";
}