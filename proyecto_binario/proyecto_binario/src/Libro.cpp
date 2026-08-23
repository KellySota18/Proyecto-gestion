#include "Libro.h"
#include <sstream>
#include <stdexcept>

Libro::Libro() {
    codigo = 0;
    titulo = "";
    autor = "";
    ejemplares = 0;
}

Libro::Libro(int codigo, const string& titulo, const string& autor, int ejemplares) {
    this->codigo = codigo;
    this->titulo = titulo;
    this->autor = autor;
    this->ejemplares = ejemplares;
}

int Libro::getCodigo() const { return codigo; }
string Libro::getTitulo() const { return titulo; }
string Libro::getAutor() const { return autor; }
int Libro::getEjemplares() const { return ejemplares; }

void Libro::setTitulo(const string& titulo) { this->titulo = titulo; }
void Libro::setAutor(const string& autor) { this->autor = autor; }
void Libro::setEjemplares(int ejemplares) { this->ejemplares = ejemplares; }

string Libro::convertirLinea() const {
    return to_string(codigo) + ";" + titulo + ";" + autor + ";" + to_string(ejemplares);
}

Libro Libro::desdeLinea(const string& linea) {
    stringstream ss(linea);
    string codigoTexto, tituloTexto, autorTexto, ejemplaresTexto;

    if (!getline(ss, codigoTexto, ';') || !getline(ss, tituloTexto, ';') ||
        !getline(ss, autorTexto, ';') || !getline(ss, ejemplaresTexto, ';')) {
        throw runtime_error("Registro invalido en biblioteca.txt");
    }

    return Libro(stoi(codigoTexto), tituloTexto, autorTexto, stoi(ejemplaresTexto));
}
