#include "LibroService.h"
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

static void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static int leerEntero(const string& mensaje) {
    int valor;
    cout << mensaje;
    if (!(cin >> valor)) {
        limpiarEntrada();
        throw runtime_error("Entrada invalida: debe ingresar un numero entero");
    }
    return valor;
}

static long long leerCodigo(const string& mensaje) {
    long long valor;
    cout << mensaje;

    if (!(cin >> valor)) {
        limpiarEntrada();
        throw runtime_error("Entrada invalida: debe ingresar un codigo numerico");
    }

    return valor;
}

LibroService::LibroService(ILibroRepository* repository) {
    this->repository = repository;
}

void LibroService::validarCodigo(long long codigo) {
    if (codigo <= 0) {
        throw runtime_error("El codigo debe ser mayor que cero");
    }
}

void LibroService::validarTextoNoVacio(const string& texto, const string& nombreCampo) {
    if (texto.empty()) {
        throw runtime_error("El campo " + nombreCampo + " no debe estar vacio");
    }
}

void LibroService::validarEjemplares(int ejemplares) {
    if (ejemplares < 0) {
        throw runtime_error("Los ejemplares deben ser mayor o igual que cero");
    }
}

void LibroService::registrarLibro() {
    long long codigo = leerCodigo("\nIngrese codigo: ");
    validarCodigo(codigo);

    try {
        repository->buscarLibroPorCodigo(codigo);
        throw runtime_error("Ya existe un libro registrado con ese codigo");
    }
    catch (const runtime_error& error) {
        string mensaje = error.what();

        if (mensaje != "El libro no existe" &&
            mensaje.find("no existe") == string::npos &&
            mensaje.find("no se puede abrir") == string::npos &&
            mensaje.find("Error al abrir") == string::npos) {
            throw;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string titulo;
    cout << "Ingrese titulo: ";
    getline(cin, titulo);
    validarTextoNoVacio(titulo, "titulo");

    string autor;
    cout << "Ingrese autor: ";
    getline(cin, autor);
    validarTextoNoVacio(autor, "autor");

    int ejemplares = leerEntero("Ingrese cantidad de ejemplares: ");
    validarEjemplares(ejemplares);

    Libro libro(codigo, titulo, autor, ejemplares);
    repository->registrarLibro(libro);

    cout << "Libro registrado correctamente en biblioteca.txt." << endl;
}

void LibroService::listarLibros() {
    vector<Libro> libros = repository->listarLibros();

    cout << "\n===== LIBROS REGISTRADOS =====" << endl;

    if (libros.empty()) {
        cout << "No hay libros registrados o el archivo esta vacio." << endl;
        return;
    }

    for (const Libro& libro : libros) {
        cout << "Codigo: " << libro.getCodigo() << endl;
        cout << "Titulo: " << libro.getTitulo() << endl;
        cout << "Autor: " << libro.getAutor() << endl;
        cout << "Ejemplares: " << libro.getEjemplares() << endl;
        cout << "-----------------------------" << endl;
    }
}

void LibroService::buscarLibro() {
    long long codigo = leerCodigo("\nIngrese codigo del libro a buscar: ");
    validarCodigo(codigo);

    Libro libro = repository->buscarLibroPorCodigo(codigo);

    cout << "\nLibro encontrado:" << endl;
    cout << "Codigo: " << libro.getCodigo() << endl;
    cout << "Titulo: " << libro.getTitulo() << endl;
    cout << "Autor: " << libro.getAutor() << endl;
    cout << "Ejemplares: " << libro.getEjemplares() << endl;
}

void LibroService::actualizarLibro() {
    long long codigo = leerCodigo("\nIngrese codigo del libro a actualizar: ");
    validarCodigo(codigo);

    Libro libro = repository->buscarLibroPorCodigo(codigo);

    cout << "\nDato a actualizar:" << endl;
    cout << "1. Titulo" << endl;
    cout << "2. Autor" << endl;
    cout << "3. Ejemplares" << endl;

    int opcion = leerEntero("Seleccione una opcion: ");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opcion == 1) {
        string nuevoTitulo;
        cout << "Ingrese nuevo titulo: ";
        getline(cin, nuevoTitulo);
        validarTextoNoVacio(nuevoTitulo, "titulo");
        libro.setTitulo(nuevoTitulo);
    }
    else if (opcion == 2) {
        string nuevoAutor;
        cout << "Ingrese nuevo autor: ";
        getline(cin, nuevoAutor);
        validarTextoNoVacio(nuevoAutor, "autor");
        libro.setAutor(nuevoAutor);
    }
    else if (opcion == 3) {
        int nuevosEjemplares = leerEntero("Ingrese nueva cantidad de ejemplares: ");
        validarEjemplares(nuevosEjemplares);
        libro.setEjemplares(nuevosEjemplares);
    }
    else {
        throw runtime_error("Opcion invalida");
    }

    repository->actualizarLibro(libro);
    cout << "Libro actualizado correctamente." << endl;
}

void LibroService::eliminarLibro() {
    long long codigo = leerCodigo("\nIngrese codigo del libro a eliminar: ");
    validarCodigo(codigo);

    repository->buscarLibroPorCodigo(codigo);
    repository->eliminarLibro(codigo);

    cout << "Libro eliminado correctamente." << endl;
}