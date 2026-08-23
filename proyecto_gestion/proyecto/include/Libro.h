#pragma once
#include <string>
using namespace std;

// Representa un libro persistido como linea de texto en biblioteca.txt
// Formato de linea: codigo|titulo|autor|ejemplares
class Libro {
private:
    long long codigo;
    string titulo;
    string autor;
    int ejemplares;

public:
    Libro();
    Libro(long long codigo, const string& titulo, const string& autor, int ejemplares);

    // Getters
    long long getCodigo() const;
    string getTitulo() const;
    string getAutor() const;
    int getEjemplares() const;

    // Setters (el codigo no se modifica una vez creado el libro)
    void setTitulo(const string& titulo);
    void setAutor(const string& autor);
    void setEjemplares(int ejemplares);

    // Serializacion a linea de texto para el archivo
    string convertirLinea() const;

    // Reconstruye un Libro a partir de una linea leida del archivo
    static Libro desdeLinea(const string& linea);
};
