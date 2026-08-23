#pragma once
#include "ProductoBinario.h"

// Interfaz de repositorio para la version binaria de Producto.
// A diferencia de IProductoRepository (version texto), listarProductos()
// no retorna un vector: imprime directamente por consola, siguiendo el
// mismo comportamiento que ProductoRepositoryBinario.cpp.
class IProductoRepository {
public:
    virtual void crearProducto(const ProductoBinario& producto) = 0;
    virtual void listarProductos() = 0;
    virtual ProductoBinario buscarProductoPorCodigo(int codigo) = 0;
    virtual void actualizarProducto(const ProductoBinario& producto) = 0;
    virtual void eliminarProducto(int codigo) = 0;
    virtual ~IProductoRepository() {}
};
