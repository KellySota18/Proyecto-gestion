#include "Producto.h"
#include <sstream>
#include <stdexcept>
using namespace std;

Producto::Producto() : codigo(0), nombre(""), precio(0.0), stock(0) {}

Producto::Producto(int codigo, const string& nombre, double precio, int stock) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->precio = precio;
    this->stock = stock;
}

int Producto::getCodigo() const { return codigo; }
string Producto::getNombre() const { return nombre; }
double Producto::getPrecio() const { return precio; }
int Producto::getStock() const { return stock; }

void Producto::setNombre(const string& nombre) { this->nombre = nombre; }
void Producto::setPrecio(double precio) { this->precio = precio; }
void Producto::setStock(int stock) { this->stock = stock; }

string Producto::convertirLinea() const {
    ostringstream linea;
    linea << codigo << "|" << nombre << "|" << precio << "|" << stock;
    return linea.str();
}

Producto Producto::desdeLinea(const string& linea) {
    istringstream ss(linea);
    string campoCodigo, campoNombre, campoPrecio, campoStock;

    if (!getline(ss, campoCodigo, '|') ||
        !getline(ss, campoNombre, '|') ||
        !getline(ss, campoPrecio, '|') ||
        !getline(ss, campoStock, '|')) {
        throw runtime_error("Linea de producto con formato invalido");
    }

    try {
        int codigo = stoi(campoCodigo);
        double precio = stod(campoPrecio);
        int stock = stoi(campoStock);
        return Producto(codigo, campoNombre, precio, stock);
    }
    catch (...) {
        throw runtime_error("Linea de producto con datos numericos invalidos");
    }
}
