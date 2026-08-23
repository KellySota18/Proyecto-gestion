#pragma once
#include "ILibroRepository.h"
#include <string>
using namespace std;

class LibroService {
private:
    ILibroRepository* repository;

    void validarCodigo(long long codigo);
    void validarTextoNoVacio(const string& texto, const string& nombreCampo);
    void validarEjemplares(int ejemplares);

public:
    LibroService(ILibroRepository* repository);

    void registrarLibro();
    void listarLibros();
    void buscarLibro();
    void actualizarLibro();
    void eliminarLibro();
};