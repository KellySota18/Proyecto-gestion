#include "LibroRepositoryArchivo.h"
#include <cstdio>
#include <fstream>
#include <stdexcept>

using namespace std;

LibroRepositoryArchivo::LibroRepositoryArchivo(string nombreArchivo) {
    this->nombreArchivo = nombreArchivo;
}

static bool intentarLeerLibro(const string& linea, Libro& libro) {
    try {
        libro = Libro::desdeLinea(linea);
        return true;
    }
    catch (...) {
        return false;
    }
}

void LibroRepositoryArchivo::registrarLibro(const Libro& libro) {
    ofstream archivo(nombreArchivo, ios::app);

    if (!archivo.is_open()) {
        throw runtime_error("Error al abrir biblioteca.txt para escritura");
    }

    archivo << libro.convertirLinea() << endl;

    if (!archivo.good()) {
        throw runtime_error("No se pudo escribir el libro en biblioteca.txt");
    }

    archivo.close();
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
            Libro libro;

            if (intentarLeerLibro(linea, libro)) {
                libros.push_back(libro);
            }
        }
    }

    archivo.close();
    return libros;
}

Libro LibroRepositoryArchivo::buscarLibroPorCodigo(long long codigo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        throw runtime_error("El archivo biblioteca.txt no existe o no se puede abrir");
    }

    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        Libro libro;

        if (!intentarLeerLibro(linea, libro)) {
            continue;
        }

        if (libro.getCodigo() == codigo) {
            archivo.close();
            return libro;
        }
    }

    archivo.close();
    throw runtime_error("El libro no existe");
}

void LibroRepositoryArchivo::actualizarLibro(const Libro& libroActualizado) {
    ifstream archivoOriginal(nombreArchivo);
    ofstream archivoTemporal("temporal.txt");

    if (!archivoOriginal.is_open() || !archivoTemporal.is_open()) {
        throw runtime_error("Error al abrir archivos para actualizar biblioteca.txt");
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoOriginal, linea)) {
        if (linea.empty()) {
            continue;
        }

        Libro libro;

        if (!intentarLeerLibro(linea, libro)) {
            continue;
        }

        if (libro.getCodigo() == libroActualizado.getCodigo()) {
            archivoTemporal << libroActualizado.convertirLinea() << endl;
            encontrado = true;
        }
        else {
            archivoTemporal << linea << endl;
        }
    }

    archivoOriginal.close();
    archivoTemporal.close();

    if (!encontrado) {
        remove("temporal.txt");
        throw runtime_error("El libro no existe");
    }

    remove(nombreArchivo.c_str());

    if (rename("temporal.txt", nombreArchivo.c_str()) != 0) {
        throw runtime_error("Error al reemplazar biblioteca.txt");
    }
}

void LibroRepositoryArchivo::eliminarLibro(long long codigo) {
    ifstream archivoOriginal(nombreArchivo);
    ofstream archivoTemporal("temporal.txt");

    if (!archivoOriginal.is_open() || !archivoTemporal.is_open()) {
        throw runtime_error("Error al abrir archivos para eliminar libro");
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoOriginal, linea)) {
        if (linea.empty()) {
            continue;
        }

        Libro libro;

        if (!intentarLeerLibro(linea, libro)) {
            continue;
        }

        if (libro.getCodigo() == codigo) {
            encontrado = true;
            continue;
        }

        archivoTemporal << linea << endl;
    }

    archivoOriginal.close();
    archivoTemporal.close();

    if (!encontrado) {
        remove("temporal.txt");
        throw runtime_error("El libro no existe");
    }

    remove(nombreArchivo.c_str());

    if (rename("temporal.txt", nombreArchivo.c_str()) != 0) {
        throw runtime_error("Error al reemplazar biblioteca.txt");
    }
}