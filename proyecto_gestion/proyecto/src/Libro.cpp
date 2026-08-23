#include "Libro.h"
#include <sstream>
#include <stdexcept>
using namespace std;

Libro::Libro() : codigo(0), titulo(""), autor(""), ejemplares(0) {}

Libro::Libro(long long codigo, const string& titulo, const string& autor, int ejemplares) {
    this->codigo = codigo;
    this->titulo = titulo;
    this->autor = autor;
    this->ejemplares = ejemplares;
}

long long Libro::getCodigo() const { return codigo; }
string Libro::getTitulo() const { return titulo; }
string Libro::getAutor() const { return autor; }
int Libro::getEjemplares() const { return ejemplares; }

void Libro::setTitulo(const string& titulo) { this->titulo = titulo; }
void Libro::setAutor(const string& autor) { this->autor = autor; }
void Libro::setEjemplares(int ejemplares) { this->ejemplares = ejemplares; }

string Libro::convertirLinea() const {
    ostringstream linea;
    linea << codigo << "|" << titulo << "|" << autor << "|" << ejemplares;
    return linea.str();
}

Libro Libro::desdeLinea(const string& linea) {
    istringstream ss(linea);
    string campoCodigo, campoTitulo, campoAutor, campoEjemplares;

    if (!getline(ss, campoCodigo, '|') ||
        !getline(ss, campoTitulo, '|') ||
        !getline(ss, campoAutor, '|') ||
        !getline(ss, campoEjemplares, '|')) {
        throw runtime_error("Linea de libro con formato invalido");
    }

    try {
        long long codigo = stoll(campoCodigo);
        int ejemplares = stoi(campoEjemplares);
        return Libro(codigo, campoTitulo, campoAutor, ejemplares);
    }
    catch (...) {
        throw runtime_error("Linea de libro con datos numericos invalidos");
    }
}
