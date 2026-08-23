#include "ProductoService.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <stdexcept>
using namespace std;

ProductoService::ProductoService(IProductoRepository* repository) {
    this->repository = repository;
}

int ProductoService::leerEntero(const string& mensaje) {
    string entrada;
    int valor;

    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        stringstream ss(entrada);

        if (ss >> valor) {
            ss >> ws;

            if (ss.eof()) {
                return valor;
            }
        }

        cout << "Entrada invalida. Ingrese solo numeros enteros." << endl;
    }
}

double ProductoService::leerDouble(const string& mensaje) {
    string entrada;
    double valor;

    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        stringstream ss(entrada);

        if (ss >> valor) {
            ss >> ws;

            if (ss.eof()) {
                return valor;
            }
        }

        cout << "Entrada invalida. Ingrese solo numeros decimales." << endl;
    }
}

void ProductoService::validarCodigo(int codigo) {
    if (codigo <= 0) {
        throw runtime_error("El codigo debe ser mayor que cero");
    }
}

void ProductoService::validarNombre(const char nombre[]) {
    if (strlen(nombre) == 0) {
        throw runtime_error("El nombre no puede estar vacio");
    }
}

void ProductoService::validarPrecio(double precio) {
    if (precio <= 0) {
        throw runtime_error("El precio debe ser mayor que cero");
    }
}

void ProductoService::validarStock(int stock) {
    if (stock < 0) {
        throw runtime_error("El stock no puede ser negativo");
    }
}

ProductoBinario ProductoService::solicitarDatosProducto() {
    ProductoBinario producto;
    string nombreTemporal;

    producto.codigo = leerEntero("\nIngrese codigo: ");
    validarCodigo(producto.codigo);

    cout << "Ingrese nombre: ";
    getline(cin, nombreTemporal);

    if (nombreTemporal.length() >= sizeof(producto.nombre)) {
        nombreTemporal = nombreTemporal.substr(0, sizeof(producto.nombre) - 1);
    }

    strncpy(producto.nombre, nombreTemporal.c_str(), sizeof(producto.nombre) - 1);
    producto.nombre[sizeof(producto.nombre) - 1] = '\0';

    validarNombre(producto.nombre);

    producto.precio = leerDouble("Ingrese precio: ");
    validarPrecio(producto.precio);

    producto.stock = leerEntero("Ingrese stock: ");
    validarStock(producto.stock);

    return producto;
}

void ProductoService::registrarProducto() {
    ProductoBinario producto = solicitarDatosProducto();
    repository->crearProducto(producto);

    cout << "Producto guardado correctamente en productos.dat." << endl;
}

void ProductoService::listarProductos() {
    repository->listarProductos();
}

void ProductoService::buscarProducto() {
    int codigo = leerEntero("\nIngrese codigo del producto a buscar: ");
    validarCodigo(codigo);

    ProductoBinario producto = repository->buscarProductoPorCodigo(codigo);

    cout << "\nProducto encontrado:" << endl;
    cout << "Codigo: " << producto.codigo << endl;
    cout << "Nombre: " << producto.nombre << endl;
    cout << "Precio: " << producto.precio << endl;
    cout << "Stock: " << producto.stock << endl;
}

void ProductoService::actualizarProducto() {
    int codigo = leerEntero("\nIngrese codigo del producto a actualizar: ");
    validarCodigo(codigo);

    ProductoBinario producto = repository->buscarProductoPorCodigo(codigo);

    cout << "\nDato a actualizar:" << endl;
    cout << "1. Nombre" << endl;
    cout << "2. Precio" << endl;
    cout << "3. Stock" << endl;

    int opcion = leerEntero("Seleccione una opcion: ");

    if (opcion == 1) {
        string nuevoNombre;

        cout << "Ingrese nuevo nombre: ";
        getline(cin, nuevoNombre);

        if (nuevoNombre.length() >= sizeof(producto.nombre)) {
            nuevoNombre = nuevoNombre.substr(0, sizeof(producto.nombre) - 1);
        }

        strncpy(producto.nombre, nuevoNombre.c_str(), sizeof(producto.nombre) - 1);
        producto.nombre[sizeof(producto.nombre) - 1] = '\0';

        validarNombre(producto.nombre);
    }
    else if (opcion == 2) {
        producto.precio = leerDouble("Ingrese nuevo precio: ");
        validarPrecio(producto.precio);
    }
    else if (opcion == 3) {
        producto.stock = leerEntero("Ingrese nuevo stock: ");
        validarStock(producto.stock);
    }
    else {
        throw runtime_error("Opcion invalida");
    }

    repository->actualizarProducto(producto);

    cout << "Producto actualizado correctamente." << endl;
}

void ProductoService::eliminarProducto() {
    int codigo = leerEntero("\nIngrese codigo del producto a eliminar: ");
    validarCodigo(codigo);

    repository->eliminarProducto(codigo);

    cout << "Producto eliminado correctamente." << endl;
}