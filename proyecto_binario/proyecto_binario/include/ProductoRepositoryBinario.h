#pragma once
#include "IProductoRepository.h"
#include <string>
using namespace std;

class ProductoRepositoryBinario : public IProductoRepository {
private:
    string nombreArchivo;

public:
    ProductoRepositoryBinario(string nombreArchivo);
    void crearProducto(const ProductoBinario& producto) override;
    void listarProductos() override;
    ProductoBinario buscarProductoPorCodigo(int codigo) override;
    void actualizarProducto(const ProductoBinario& producto) override;
    void eliminarProducto(int codigo) override;
};
