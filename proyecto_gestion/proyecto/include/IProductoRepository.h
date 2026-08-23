#pragma once
#include "Producto.h"
#include <vector>
using namespace std;

class IProductoRepository {
public:
    virtual void crearProducto(const Producto& producto) = 0;
    virtual vector<Producto> listarProductos() = 0;
    virtual Producto buscarProductoPorCodigo(int codigo) = 0;
    virtual void actualizarProducto(const Producto& producto) = 0;
    virtual void eliminarProducto(int codigo) = 0;
    virtual ~IProductoRepository() {}
};
