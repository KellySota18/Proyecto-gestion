#include "ProductoService.h"
#include <iostream>
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
        if ((ss >> valor) && (ss >> ws).eof()) return valor;
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
        if ((ss >> valor) && (ss >> ws).eof()) return valor;
        cout << "Entrada invalida. Ingrese solo numeros decimales." << endl;
    }
}

string ProductoService::leerTextoObligatorio(const string& mensaje) {
    string texto;
    while (true) {
        cout << mensaje;
        getline(cin, texto);
        if (!texto.empty()) return texto;
        cout << "Entrada invalida. El nombre no puede estar vacio." << endl;
    }
}

void ProductoService::validarCodigo(int codigo) {
    if (codigo <= 0) throw runtime_error("El codigo debe ser mayor que cero");
}

void ProductoService::validarPrecio(double precio) {
    if (precio < 0) throw runtime_error("El precio debe ser mayor o igual que cero");
}

void ProductoService::validarStock(int stock) {
    if (stock < 0) throw runtime_error("El stock debe ser mayor o igual que cero");
}

void ProductoService::registrarProducto() {
    int codigo = leerEntero("\nIngrese codigo: ");
    validarCodigo(codigo);

    string nombre = leerTextoObligatorio("Ingrese nombre: ");

    double precio = leerDouble("Ingrese precio: ");
    validarPrecio(precio);

    int stock = leerEntero("Ingrese stock: ");
    validarStock(stock);

    repository->crearProducto(Producto(codigo, nombre, precio, stock));
    cout << "Producto registrado correctamente." << endl;
}

void ProductoService::listarProductos() {
    vector<Producto> productos = repository->listarProductos();

    if (productos.empty()) {
        cout << "No hay productos registrados o el archivo esta vacio." << endl;
        return;
    }

    cout << "\n===== PRODUCTOS REGISTRADOS =====" << endl;
    for (const Producto& producto : productos) {
        cout << "Codigo: " << producto.getCodigo() << endl;
        cout << "Nombre: " << producto.getNombre() << endl;
        cout << "Precio: " << producto.getPrecio() << endl;
        cout << "Stock: " << producto.getStock() << endl;
        cout << "-----------------------------" << endl;
    }
}

void ProductoService::buscarProducto() {
    int codigo = leerEntero("\nIngrese codigo del producto a buscar: ");
    validarCodigo(codigo);

    Producto producto = repository->buscarProductoPorCodigo(codigo);
    cout << "\nProducto encontrado:" << endl;
    cout << "Codigo: " << producto.getCodigo() << endl;
    cout << "Nombre: " << producto.getNombre() << endl;
    cout << "Precio: " << producto.getPrecio() << endl;
    cout << "Stock: " << producto.getStock() << endl;
}

void ProductoService::actualizarProducto() {
    int codigo = leerEntero("\nIngrese codigo del producto a actualizar: ");
    validarCodigo(codigo);

    Producto producto = repository->buscarProductoPorCodigo(codigo);

    cout << "\nDato a actualizar:" << endl;
    cout << "1. Precio" << endl;
    cout << "2. Stock" << endl;

    int opcion = leerEntero("Seleccione una opcion: ");
    if (opcion == 1) {
        double nuevoPrecio = leerDouble("Ingrese nuevo precio: ");
        validarPrecio(nuevoPrecio);
        producto.setPrecio(nuevoPrecio);
    }
    else if (opcion == 2) {
        int nuevoStock = leerEntero("Ingrese nuevo stock: ");
        validarStock(nuevoStock);
        producto.setStock(nuevoStock);
    }
    else {
        throw runtime_error("Opcion invalida. Debe elegir 1 o 2");
    }

    repository->actualizarProducto(producto);
    cout << "Producto actualizado correctamente." << endl;
}

void ProductoService::eliminarProducto() {
    int codigo = leerEntero("\nIngrese codigo del producto a eliminar: ");
    validarCodigo(codigo);

    repository->buscarProductoPorCodigo(codigo);
    repository->eliminarProducto(codigo);
    cout << "Producto eliminado correctamente." << endl;
}
