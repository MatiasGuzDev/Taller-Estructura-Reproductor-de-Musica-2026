# Taller-Estructura-Reproductor-de-Musica-2026

Proyecto ReMusik

Este proyecto consiste en un sistema de gestión y reproducción de música desarrollado en C++ utilizando Estructuras de Datos Lineales (Listas Enlazadas). Permite cargar canciones desde archivos, gestionar estados de reproducción y navegar por una lista de pistas de forma eficiente.

1. Funcionamiento de la Aplicación
La aplicación simula el comportamiento de un reproductor digital moderno. Al iniciar, el programa realiza las siguientes acciones:

Carga de Datos: Lee el archivo music_source.txt para poblar la lista de canciones disponibles.

Persistencia: Carga el último estado guardado (canción actual, modo aleatorio) desde status.cfg.

Interfaz de Usuario: Ofrece un menú interactivo por consola para:

Reproducir, pausar y saltar entre pistas.

Activar/desactivar el modo Aleatorio (Shuffle).

Alternar modos de Repetición (Ninguna, Una, Todas).

Visualizar la lista de reproducción actual gestionada mediante una Linked List.


2. Instrucciones de Compilación y Ejecución
Requisitos previos
Compilador GCC/G++ (MinGW para Windows).

CMake (versión 3.28 o superior).

IDE recomendado: JetBrains CLion.

Compilación con CMake (Recomendado)
Abre el proyecto en CLion.

Asegúrate de que el archivo CMakeLists.txt esté en la raíz.

Ve a File > Reload CMake Project.

Presiona el botón del Martillo (Build) o Ctrl + F9.

Proyecto realizado por:
-Martin Canales Barraza
-Matias Guzman Matus 
