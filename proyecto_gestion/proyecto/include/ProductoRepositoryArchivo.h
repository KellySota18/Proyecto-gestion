#pragma once
#include "IProductoRepository.h"
#include <string>
using namespace std;

class ProductoRepositoryArchivo : public IProductoRepository {
private:
    string nombreArchivo;
    string archivoTemporal;

public:
    ProductoRepositoryArchivo(string nombreArchivo);
    void crearProducto(const Producto& producto) override;
    vector<Producto> listarProductos() override;
    Producto buscarProductoPorCodigo(int codigo) override;
    void actualizarProducto(const Producto& producto) override;
    void eliminarProducto(int codigo) override;
};
