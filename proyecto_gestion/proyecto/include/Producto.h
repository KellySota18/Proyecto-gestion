#pragma once
#include <string>
using namespace std;

// Representa un producto persistido como linea de texto en inventario.txt
// Formato de linea: codigo|nombre|precio|stock
class Producto {
private:
    int codigo;
    string nombre;
    double precio;
    int stock;

public:
    Producto();
    Producto(int codigo, const string& nombre, double precio, int stock);

    // Getters
    int getCodigo() const;
    string getNombre() const;
    double getPrecio() const;
    int getStock() const;

    // Setters (el codigo no se modifica una vez creado el producto)
    void setNombre(const string& nombre);
    void setPrecio(double precio);
    void setStock(int stock);

    // Serializacion a linea de texto para el archivo
    string convertirLinea() const;

    // Reconstruye un Producto a partir de una linea leida del archivo
    static Producto desdeLinea(const string& linea);
};
