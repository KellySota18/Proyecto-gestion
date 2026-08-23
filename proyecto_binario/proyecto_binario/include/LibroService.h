#pragma once
#include "ILibroRepository.h"
#include <string>
using namespace std;

class LibroService {
private:
    ILibroRepository* repository;

    int leerEntero(const string& mensaje);
    string leerTextoObligatorio(const string& mensaje);
    void validarCodigo(int codigo);
    void validarTexto(const string& texto, const string& campo);
    void validarEjemplares(int ejemplares);

public:
    LibroService(ILibroRepository* repository);
    void registrarLibro();
    void listarLibros();
    void buscarLibro();
    void actualizarLibro();
    void eliminarLibro();
};
