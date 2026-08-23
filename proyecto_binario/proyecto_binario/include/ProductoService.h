#pragma once
#include "IProductoRepository.h"
#include "ProductoBinario.h"
#include <string>
using namespace std;

class ProductoService {
private:
    IProductoRepository* repository;

    int leerEntero(const string& mensaje);
    double leerDouble(const string& mensaje);
    void validarCodigo(int codigo);
    void validarNombre(const char nombre[]);
    void validarPrecio(double precio);
    void validarStock(int stock);
    ProductoBinario solicitarDatosProducto();

public:
    ProductoService(IProductoRepository* repository);

    void registrarProducto();
    void listarProductos();
    void buscarProducto();
    void actualizarProducto();
    void eliminarProducto();
};
