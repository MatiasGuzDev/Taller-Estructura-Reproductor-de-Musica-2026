#include "Reproductor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

Reproductor::Reproductor() {
    this->id_actual = 0;
    this->estado = "Reproducción Detenida";
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
        std::cout << "Error: El archivo music_source.txt no está presente en la carpeta Estructuras.\n";
        return;
    }

    std::string linea;
    while (std::getline(archivoCanciones, linea)) {
        if (linea.empty()) continue;

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
    }

    archivoCanciones.close();
    std::cout << "Archivos cargados exitosamente.\n";
    seleccionarCancionInicial();
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
    if (lista_reproduccion.isEmpty()) {
        lista_reproduccion.append(cancion_actual);
        std::cout << "Añadiendo '" << cancion_actual.getNombreCancion() << "' a la lista de reproducción...\n";
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
        std::cout << "No hay canciones cargadas en la lista.\n";
        return;
    }

    if (this->modo_repeticion == 1) { // R1 (Repetir 1)
        std::cout << "Modo repetición activado. Manteniendo la pista actual.\n";
        return;
    }

    if (lista_reproduccion.isEmpty()) {

        Cancion aleatoria = lista_canciones.get(std::rand() % lista_canciones.size());
        cancion_actual = aleatoria;
        lista_reproduccion.append(cancion_actual);
        std::cout << "Cargando pista aleatoria: " << cancion_actual.getNombreCancion() << "\n";
        return;
    }

    int indiceActual = 0;
    for (int i = 0; i < lista_canciones.size(); i++) {
        if (lista_canciones.get(i).getIdInterno() == cancion_actual.getIdInterno()) {
            indiceActual = i;
            break;
        }
    }

    int nuevoIndice = (indiceActual + 1) % lista_canciones.size();
    cancion_actual = lista_canciones.get(nuevoIndice);

    while (!lista_reproduccion.isEmpty()) {
        lista_reproduccion = LinkedList<Cancion>();
        break;
    }
    lista_reproduccion.append(cancion_actual);

    std::cout << "Cambiando a la siguiente pista...\n";
}

void Reproductor::pistaAnterior() {
    if (lista_canciones.isEmpty()) {
        std::cout << "No hay canciones cargadas en la lista.\n";
        return;
    }

    int indiceActual = 0;
    for (int i = 0; i < lista_canciones.size(); i++) {
        if (lista_canciones.get(i).getIdInterno() == cancion_actual.getIdInterno()) {
            indiceActual = i;
            break;
        }
    }

    int nuevoIndice = (indiceActual - 1 + lista_canciones.size()) % lista_canciones.size();
    cancion_actual = lista_canciones.get(nuevoIndice);

    while (!lista_reproduccion.isEmpty()) {
        lista_reproduccion = LinkedList<Cancion>();
        break;
    }
    lista_reproduccion.append(cancion_actual);

    std::cout << "Cambiando a la pista anterior...\n";
}

void Reproductor::alternarModoAleatorio() {
    this->modo_aleatorio = !this->modo_aleatorio;
    guardarEstado();

    if (this->modo_aleatorio) {
        // Algoritmo Fisher-Yates manual
        int n = lista_reproduccion.size();
        for (int i = n - 1; i > 0; --i) {
            int j = std::rand() % (i + 1);
            if (i != j) {
                Cancion temp1 = lista_reproduccion.get(i);
                Cancion temp2 = lista_reproduccion.get(j);
                lista_reproduccion.set(i, temp2);
                lista_reproduccion.set(j, temp1);
            }
        }
        std::cout << "Modo aleatorio activado. Lista de reproduccion mezclada.\n";
    } else {
        std::cout << "Modo aleatorio desactivado.\n";
    }
}

void Reproductor::alternarRepeticion() {
    this->modo_repeticion = (this->modo_repeticion + 1) % 3;
    guardarEstado();

    std::cout << "Modo repeticion cambiado a: " << this->modo_repeticion
              << " (0: Desactivado, 1: Repetir una, 2: Repetir todas)\n";
}

void Reproductor::verListaReproduccion() {
    std::cout << "Actual (S-R1): " << cancion_actual.getNombreCancion() << " - " << cancion_actual.getNombreArtista() << "\n";
    std::cout << "Lista de reproduccion actual:\n";
    if (lista_reproduccion.isEmpty()) {
        std::cout << " Vacia\n";
    } else {
        lista_reproduccion.display();
    }

    std::cout << "\nOpciones:\n";
    std::cout << "S<num> - Saltar a la cancion seleccionada\n";
    std::cout << "V - Volver al menu principal\n";
    std::cout << "Seleccione opcion (Ej. S2, o V): ";

    std::string sub_opcion;
    std::cin >> sub_opcion;

    if (sub_opcion[0] == 'S' || sub_opcion[0] == 's') {
        try {
            int num = std::stoi(sub_opcion.substr(1));
            if (num >= 1 && num <= lista_reproduccion.size()) {
                cancion_actual = lista_reproduccion.get(num - 1);
                std::cout << "Reproduciendo: " << cancion_actual.getNombreCancion() << "\n";
            } else {
                std::cout << "Numero fuera de rango.\n";
            }
        } catch (...) {
            std::cout << "Opcion de salto no válida.\n";
        }
    }
}

void Reproductor::verListadoCanciones() {
    std::cout << "Actual (S-R1): " << cancion_actual.getNombreCancion() << " - " << cancion_actual.getNombreArtista() << "\n";
    std::cout << "Canciones registradas:\n";
    lista_canciones.display();

    std::cout << "\nOpciones:\n";
    std::cout << "R<num> - Reproducir cancion seleccionada\n";
    std::cout << "A<num> - Agregar cancion al final de la lista de reproduccion actual\n";
    std::cout << "N - Agregar cancion al registro de canciones\n";
    std::cout << "D<num> - Eliminar cancion seleccionada\n";
    std::cout << "V - Volver al menu principal\n";
    std::cout << "Seleccione opcion: ";

    std::string sub_opcion;
    std::cin >> sub_opcion;

    if (sub_opcion[0] == 'R' || sub_opcion[0] == 'r') {
        try {
            int num = std::stoi(sub_opcion.substr(1));
            if (num >= 1 && num <= lista_canciones.size()) {
                cancion_actual = lista_canciones.get(num - 1);
                while (!lista_reproduccion.isEmpty()) {
                    lista_reproduccion = LinkedList<Cancion>();
                    break;
                }
                lista_reproduccion.append(cancion_actual);
                std::cout << "Reproduciendo ahora: " << cancion_actual.getNombreCancion() << "\n";
            }
        } catch (...) {
            std::cout << "Opcion no válida.\n";
        }
    } else if (sub_opcion[0] == 'A' || sub_opcion[0] == 'a') {
        try {
            int num = std::stoi(sub_opcion.substr(1));
            if (num >= 1 && num <= lista_canciones.size()) {
                Cancion c = lista_canciones.get(num - 1);
                lista_reproduccion.append(c);
                std::cout << "Cancion agregada al final de la cola.\n";
            }
        } catch (...) {
            std::cout << "Opcion no válida.\n";
        }
    } else if (sub_opcion == "N" || sub_opcion == "n") {
        std::string n_nombre, n_artista, n_album, n_ubicacion;
        int n_ano, n_duracion;

        std::cout << "Ingrese nombre: ";
        std::cin.ignore();
        std::getline(std::cin, n_nombre);
        std::cout << "Ingrese artista: ";
        std::getline(std::cin, n_artista);
        std::cout << "Ingrese album: ";
        std::getline(std::cin, n_album);
        std::cout << "Ingrese ano: ";
        std::cin >> n_ano;
        std::cout << "Ingrese duracion (segundos): ";
        std::cin >> n_duracion;
        std::cout << "Ingrese ubicacion de archivo: ";
        std::cin.ignore();
        std::getline(std::cin, n_ubicacion);

        id_actual++;
        Cancion nuevaCancion(id_actual, n_nombre, n_artista, n_album, n_ano, n_duracion, n_ubicacion);
        lista_canciones.append(nuevaCancion);

        std::ofstream archivoSalida("../Estructuras/music_source.txt", std::ios_base::app);
        archivoSalida << id_actual << "," << n_nombre << "," << n_artista << "," << n_album << ","
                      << n_ano << "," << n_duracion << "," << n_ubicacion << "\n";
        archivoSalida.close();

        std::cout << "Cancion registrada y añadida al archivo exitosamente.\n";
    } else if (sub_opcion[0] == 'D' || sub_opcion[0] == 'd') {
        std::cout << "Funcionalidad de eliminacion en desarrollo.\n";
    }
}

void Reproductor::mostrarMenuPrincipal() {
    std::cout << "Reproduciendo ("
              << (modo_repeticion == 1 ? "R1" : "RA")
              << "): " << cancion_actual.getNombreCancion() << "\n";
}
//verificar si está bien implementado chaval