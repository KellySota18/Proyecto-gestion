#include "ProductoRepositoryBinario.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdexcept>
using namespace std;

ProductoRepositoryBinario::ProductoRepositoryBinario(string nombreArchivo) {
    this->nombreArchivo = nombreArchivo;
}

void ProductoRepositoryBinario::crearProducto(const ProductoBinario& producto) {
    ifstream lectura(nombreArchivo, ios::binary);
    if (lectura.is_open()) {
        ProductoBinario existente;
        while (lectura.read(reinterpret_cast<char*>(&existente), sizeof(ProductoBinario))) {
            if (existente.codigo == producto.codigo) {
                throw runtime_error("Ya existe un producto con ese codigo");
            }
        }
        lectura.close();
    }

    ofstream archivo(nombreArchivo, ios::binary | ios::app);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir productos.dat para escritura");
    }

    archivo.write(reinterpret_cast<const char*>(&producto), sizeof(ProductoBinario));
    if (!archivo.good()) {
        throw runtime_error("No se pudo escribir el producto en productos.dat");
    }
}

void ProductoRepositoryBinario::listarProductos() {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cout << "No hay productos registrados o el archivo productos.dat no existe." << endl;
        return;
    }

    ProductoBinario producto;
    bool hayProductos = false;

    cout << "\n===== PRODUCTOS REGISTRADOS =====" << endl;
    while (archivo.read(reinterpret_cast<char*>(&producto), sizeof(ProductoBinario))) {
        cout << "Codigo: " << producto.codigo << endl;
        cout << "Nombre: " << producto.nombre << endl;
        cout << "Precio: " << producto.precio << endl;
        cout << "Stock: " << producto.stock << endl;
        cout << "-----------------------------" << endl;
        hayProductos = true;
    }

    if (!hayProductos) {
        cout << "No hay productos registrados o el archivo esta vacio." << endl;
    }
}

ProductoBinario ProductoRepositoryBinario::buscarProductoPorCodigo(int codigo) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        throw runtime_error("El archivo productos.dat no existe o no se puede leer");
    }

    ProductoBinario producto;
    while (archivo.read(reinterpret_cast<char*>(&producto), sizeof(ProductoBinario))) {
        if (producto.codigo == codigo) {
            return producto;
        }
    }

    throw runtime_error("El producto no existe");
}

void ProductoRepositoryBinario::actualizarProducto(const ProductoBinario& productoActualizado) {
    fstream archivo(nombreArchivo, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir productos.dat para actualizar");
    }

    ProductoBinario producto;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&producto), sizeof(ProductoBinario))) {
        if (producto.codigo == productoActualizado.codigo) {
            archivo.seekp(-static_cast<int>(sizeof(ProductoBinario)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&productoActualizado), sizeof(ProductoBinario));
            if (!archivo.good()) {
                throw runtime_error("No se pudo escribir la modificacion en productos.dat");
            }
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        throw runtime_error("No se puede actualizar: el producto no existe");
    }
}

void ProductoRepositoryBinario::eliminarProducto(int codigo) {
    ifstream archivoOriginal(nombreArchivo, ios::binary);
    ofstream archivoTemporal("temporal.dat", ios::binary);

    if (!archivoOriginal.is_open() || !archivoTemporal.is_open()) {
        throw runtime_error("Error al abrir archivos binarios para eliminar");
    }

    ProductoBinario producto;
    bool encontrado = false;

    while (archivoOriginal.read(reinterpret_cast<char*>(&producto), sizeof(ProductoBinario))) {
        if (producto.codigo != codigo) {
            archivoTemporal.write(reinterpret_cast<const char*>(&producto), sizeof(ProductoBinario));
            if (!archivoTemporal.good()) {
                throw runtime_error("No se pudo escribir en temporal.dat");
            }
        }
        else {
            encontrado = true;
        }
    }

    archivoOriginal.close();
    archivoTemporal.close();

    if (!encontrado) {
        remove("temporal.dat");
        throw runtime_error("No se puede eliminar: el producto no existe");
    }

    if (remove(nombreArchivo.c_str()) != 0) {
        remove("temporal.dat");
        throw runtime_error("No se pudo reemplazar productos.dat");
    }

    if (rename("temporal.dat", nombreArchivo.c_str()) != 0) {
        throw runtime_error("No se pudo renombrar temporal.dat");
    }
}
