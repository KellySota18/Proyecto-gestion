#include "LibroService.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

LibroService::LibroService(ILibroRepository* repository) {
    this->repository = repository;
}

int LibroService::leerEntero(const string& mensaje) {
    string entrada;
    int valor;

    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        stringstream ss(entrada);
        if ((ss >> valor) && (ss >> ws).eof()) {
            return valor;
        }

        cout << "Entrada invalida. Ingrese solo numeros enteros." << endl;
    }
}

string LibroService::leerTextoObligatorio(const string& mensaje) {
    string texto;

    while (true) {
        cout << mensaje;
        getline(cin, texto);

        if (!texto.empty()) {
            return texto;
        }

        cout << "Entrada invalida. El texto no puede estar vacio." << endl;
    }
}

void LibroService::validarCodigo(int codigo) {
    if (codigo <= 0) throw runtime_error("El codigo debe ser mayor que cero");
}

void LibroService::validarTexto(const string& texto, const string& campo) {
    if (texto.empty()) throw runtime_error("El campo " + campo + " no puede estar vacio");
}

void LibroService::validarEjemplares(int ejemplares) {
    if (ejemplares < 0) throw runtime_error("Los ejemplares no pueden ser negativos");
}

void LibroService::registrarLibro() {
    int codigo = leerEntero("\nIngrese codigo: ");
    validarCodigo(codigo);

    string titulo = leerTextoObligatorio("Ingrese titulo: ");
    validarTexto(titulo, "titulo");

    string autor = leerTextoObligatorio("Ingrese autor: ");
    validarTexto(autor, "autor");

    int ejemplares = leerEntero("Ingrese ejemplares: ");
    validarEjemplares(ejemplares);

    repository->crearLibro(Libro(codigo, titulo, autor, ejemplares));
    cout << "Libro registrado correctamente en biblioteca.txt." << endl;
}

void LibroService::listarLibros() {
    vector<Libro> libros = repository->listarLibros();

    if (libros.empty()) {
        cout << "No hay libros registrados o el archivo esta vacio." << endl;
        return;
    }

    cout << "\n===== LIBROS REGISTRADOS =====" << endl;
    for (const Libro& libro : libros) {
        cout << "Codigo: " << libro.getCodigo() << endl;
        cout << "Titulo: " << libro.getTitulo() << endl;
        cout << "Autor: " << libro.getAutor() << endl;
        cout << "Ejemplares: " << libro.getEjemplares() << endl;
        cout << "-----------------------------" << endl;
    }
}

void LibroService::buscarLibro() {
    int codigo = leerEntero("\nIngrese codigo del libro a buscar: ");
    validarCodigo(codigo);

    Libro libro = repository->buscarLibroPorCodigo(codigo);

    cout << "\nLibro encontrado:" << endl;
    cout << "Codigo: " << libro.getCodigo() << endl;
    cout << "Titulo: " << libro.getTitulo() << endl;
    cout << "Autor: " << libro.getAutor() << endl;
    cout << "Ejemplares: " << libro.getEjemplares() << endl;
}

void LibroService::actualizarLibro() {
    int codigo = leerEntero("\nIngrese codigo del libro a actualizar: ");
    validarCodigo(codigo);

    Libro libro = repository->buscarLibroPorCodigo(codigo);

    cout << "\nDato a actualizar:" << endl;
    cout << "1. Titulo" << endl;
    cout << "2. Autor" << endl;
    cout << "3. Ejemplares" << endl;

    int opcion = leerEntero("Seleccione una opcion: ");

    if (opcion == 1) {
        string titulo = leerTextoObligatorio("Ingrese nuevo titulo: ");
        validarTexto(titulo, "titulo");
        libro.setTitulo(titulo);
    }
    else if (opcion == 2) {
        string autor = leerTextoObligatorio("Ingrese nuevo autor: ");
        validarTexto(autor, "autor");
        libro.setAutor(autor);
    }
    else if (opcion == 3) {
        int ejemplares = leerEntero("Ingrese nuevos ejemplares: ");
        validarEjemplares(ejemplares);
        libro.setEjemplares(ejemplares);
    }
    else {
        throw runtime_error("Opcion invalida");
    }

    repository->actualizarLibro(libro);
    cout << "Libro actualizado correctamente." << endl;
}

void LibroService::eliminarLibro() {
    int codigo = leerEntero("\nIngrese codigo del libro a eliminar: ");
    validarCodigo(codigo);

    repository->buscarLibroPorCodigo(codigo);
    repository->eliminarLibro(codigo);
    cout << "Libro eliminado correctamente." << endl;
}
