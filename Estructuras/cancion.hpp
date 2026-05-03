//
// Created by marti on 03-05-2026.
//

#ifndef TALLER_ESTRUCTURA_REPRODUCTOR_DE_MUSICA_2026_CANCION_HPP
#define TALLER_ESTRUCTURA_REPRODUCTOR_DE_MUSICA_2026_CANCION_HPP

class cancion {
private:
    int id;
    std::string nombre;
    std::string artista;
    std::string album;
    int ano;
    int duracion;
    std::string ubicacion;

public:
    cancion();
    cancion(int id, std::string nombre, std::string artista, std::string album, int ano, int duracion, std::string ubicacion);

    int getId() const;
    std::string getNombreCancion() const;
    std::string getNombreArtista() const;
    std::string getAlbum() const;
    int getAno() const;
    int getDuracion() const;
    std::string getUbicion() const;

};

#endif //TALLER_ESTRUCTURA_REPRODUCTOR_DE_MUSICA_2026_CANCION_HPP
