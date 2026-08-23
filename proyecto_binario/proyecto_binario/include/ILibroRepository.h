#pragma once
#include "Libro.h"
#include <vector>
using namespace std;

class ILibroRepository {
public:
    virtual void crearLibro(const Libro& libro) = 0;
    virtual vector<Libro> listarLibros() = 0;
    virtual Libro buscarLibroPorCodigo(int codigo) = 0;
    virtual void actualizarLibro(const Libro& libroActualizado) = 0;
    virtual void eliminarLibro(int codigo) = 0;
    virtual ~ILibroRepository() {}
};
