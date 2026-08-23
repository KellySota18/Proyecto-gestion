#include "LibroRepositoryArchivo.h"
#include <fstream>
#include <cstdio>
#include <stdexcept>
using namespace std;

LibroRepositoryArchivo::LibroRepositoryArchivo(const string& nombreArchivo) {
    this->nombreArchivo = nombreArchivo;
    this->archivoTemporal = "temporal_biblioteca.txt";
}

void LibroRepositoryArchivo::crearLibro(const Libro& libro) {
    ifstream lectura(nombreArchivo);
    if (lectura.is_open()) {
        string linea;
        while (getline(lectura, linea)) {
            if (linea.empty()) continue;
            Libro existente = Libro::desdeLinea(linea);
            if (existente.getCodigo() == libro.getCodigo()) {
                throw runtime_error("Ya existe un libro con ese codigo");
            }
        }
        lectura.close();
    }

    ofstream archivo(nombreArchivo, ios::app);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir biblioteca.txt para escritura");
    }

    archivo << libro.convertirLinea() << endl;
    if (!archivo.good()) {
        throw runtime_error("No se pudo escribir el libro en biblioteca.txt");
    }
}

vector<Libro> LibroRepositoryArchivo::listarLibros() {
    ifstream archivo(nombreArchivo);
    vector<Libro> libros;

    if (!archivo.is_open()) {
        return libros;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            libros.push_back(Libro::desdeLinea(linea));
        }
    }

    return libros;
}

Libro LibroRepositoryArchivo::buscarLibroPorCodigo(int codigo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw runtime_error("El archivo biblioteca.txt no existe o no se puede leer");
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        Libro libro = Libro::desdeLinea(linea);
        if (libro.getCodigo() == codigo) {
            return libro;
        }
    }

    throw runtime_error("El libro no existe");
}

void LibroRepositoryArchivo::actualizarLibro(const Libro& libroActualizado) {
    ifstream original(nombreArchivo);
    ofstream temporal(archivoTemporal);

    if (!original.is_open() || !temporal.is_open()) {
        throw runtime_error("Error al abrir archivos para actualizar biblioteca.txt");
    }

    string linea;
    bool encontrado = false;

    while (getline(original, linea)) {
        if (linea.empty()) continue;
        Libro libro = Libro::desdeLinea(linea);

        if (libro.getCodigo() == libroActualizado.getCodigo()) {
            temporal << libroActualizado.convertirLinea() << endl;
            encontrado = true;
        }
        else {
            temporal << linea << endl;
        }
    }

    original.close();
    temporal.close();

    if (!encontrado) {
        remove(archivoTemporal.c_str());
        throw runtime_error("No se puede actualizar: el libro no existe");
    }

    if (remove(nombreArchivo.c_str()) != 0) {
        remove(archivoTemporal.c_str());
        throw runtime_error("No se pudo reemplazar biblioteca.txt");
    }

    if (rename(archivoTemporal.c_str(), nombreArchivo.c_str()) != 0) {
        throw runtime_error("No se pudo renombrar el archivo temporal");
    }
}

void LibroRepositoryArchivo::eliminarLibro(int codigo) {
    ifstream original(nombreArchivo);
    ofstream temporal(archivoTemporal);

    if (!original.is_open() || !temporal.is_open()) {
        throw runtime_error("Error al abrir archivos para eliminar libro");
    }

    string linea;
    bool encontrado = false;

    while (getline(original, linea)) {
        if (linea.empty()) continue;
        Libro libro = Libro::desdeLinea(linea);

        if (libro.getCodigo() != codigo) {
            temporal << linea << endl;
        }
        else {
            encontrado = true;
        }
    }

    original.close();
    temporal.close();

    if (!encontrado) {
        remove(archivoTemporal.c_str());
        throw runtime_error("No se puede eliminar: el libro no existe");
    }

    if (remove(nombreArchivo.c_str()) != 0) {
        remove(archivoTemporal.c_str());
        throw runtime_error("No se pudo reemplazar biblioteca.txt");
    }

    if (rename(archivoTemporal.c_str(), nombreArchivo.c_str()) != 0) {
        throw runtime_error("No se pudo renombrar el archivo temporal");
    }
}
