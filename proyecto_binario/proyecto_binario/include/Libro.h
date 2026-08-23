#pragma once
#include <string>
using namespace std;

class Libro {
private:
    int codigo;
    string titulo;
    string autor;
    int ejemplares;

public:
    Libro();
    Libro(int codigo, const string& titulo, const string& autor, int ejemplares);

    int getCodigo() const;
    string getTitulo() const;
    string getAutor() const;
    int getEjemplares() const;

    void setTitulo(const string& titulo);
    void setAutor(const string& autor);
    void setEjemplares(int ejemplares);

    string convertirLinea() const;
    static Libro desdeLinea(const string& linea);
};
