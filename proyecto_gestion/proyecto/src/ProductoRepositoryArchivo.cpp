#include "ProductoRepositoryArchivo.h"
#include <fstream>
#include <cstdio>
#include <stdexcept>
using namespace std;

ProductoRepositoryArchivo::ProductoRepositoryArchivo(string nombreArchivo) {
    this->nombreArchivo = nombreArchivo;
    this->archivoTemporal = "temporal.txt";
}

void ProductoRepositoryArchivo::crearProducto(const Producto& producto) {
    ifstream lectura(nombreArchivo);
    if (lectura.is_open()) {
        string linea;
        while (getline(lectura, linea)) {
            if (linea.empty()) continue;
            Producto existente = Producto::desdeLinea(linea);
            if (existente.getCodigo() == producto.getCodigo()) {
                throw runtime_error("Ya existe un producto con ese codigo");
            }
        }
        lectura.close();
    }

    ofstream archivo(nombreArchivo, ios::app);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir inventario.txt para escritura");
    }

    archivo << producto.convertirLinea() << endl;
    if (!archivo.good()) {
        throw runtime_error("No se pudo escribir en inventario.txt");
    }
}

vector<Producto> ProductoRepositoryArchivo::listarProductos() {
    ifstream archivo(nombreArchivo);
    vector<Producto> productos;

    if (!archivo.is_open()) {
        return productos;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            productos.push_back(Producto::desdeLinea(linea));
        }
    }

    return productos;
}

Producto ProductoRepositoryArchivo::buscarProductoPorCodigo(int codigo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw runtime_error("El archivo inventario.txt no existe o no se puede leer");
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        Producto producto = Producto::desdeLinea(linea);
        if (producto.getCodigo() == codigo) {
            return producto;
        }
    }

    throw runtime_error("El producto no existe");
}

void ProductoRepositoryArchivo::actualizarProducto(const Producto& productoActualizado) {
    ifstream archivoOriginal(nombreArchivo);
    ofstream archivoTemporalSalida(archivoTemporal);

    if (!archivoOriginal.is_open() || !archivoTemporalSalida.is_open()) {
        throw runtime_error("Error al abrir archivos para actualizar");
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoOriginal, linea)) {
        if (linea.empty()) continue;
        Producto producto = Producto::desdeLinea(linea);

        if (producto.getCodigo() == productoActualizado.getCodigo()) {
            archivoTemporalSalida << productoActualizado.convertirLinea() << endl;
            encontrado = true;
        }
        else {
            archivoTemporalSalida << linea << endl;
        }
    }

    archivoOriginal.close();
    archivoTemporalSalida.close();

    if (!encontrado) {
        remove(archivoTemporal.c_str());
        throw runtime_error("No se puede actualizar: el producto no existe");
    }

    if (remove(nombreArchivo.c_str()) != 0) {
        remove(archivoTemporal.c_str());
        throw runtime_error("No se pudo reemplazar inventario.txt");
    }

    if (rename(archivoTemporal.c_str(), nombreArchivo.c_str()) != 0) {
        throw runtime_error("No se pudo renombrar temporal.txt");
    }
}

void ProductoRepositoryArchivo::eliminarProducto(int codigo) {
    ifstream archivoOriginal(nombreArchivo);
    ofstream archivoTemporalSalida(archivoTemporal);

    if (!archivoOriginal.is_open() || !archivoTemporalSalida.is_open()) {
        throw runtime_error("Error al abrir archivos para eliminar");
    }

    string linea;
    bool encontrado = false;

    while (getline(archivoOriginal, linea)) {
        if (linea.empty()) continue;
        Producto producto = Producto::desdeLinea(linea);

        if (producto.getCodigo() != codigo) {
            archivoTemporalSalida << linea << endl;
        }
        else {
            encontrado = true;
        }
    }

    archivoOriginal.close();
    archivoTemporalSalida.close();

    if (!encontrado) {
        remove(archivoTemporal.c_str());
        throw runtime_error("No se puede eliminar: el producto no existe");
    }

    if (remove(nombreArchivo.c_str()) != 0) {
        remove(archivoTemporal.c_str());
        throw runtime_error("No se pudo reemplazar inventario.txt");
    }

    if (rename(archivoTemporal.c_str(), nombreArchivo.c_str()) != 0) {
        throw runtime_error("No se pudo renombrar temporal.txt");
    }
}
