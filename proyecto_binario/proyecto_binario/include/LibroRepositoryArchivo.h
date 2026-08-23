#pragma once
#include "ILibroRepository.h"
#include <string>
using namespace std;

class LibroRepositoryArchivo : public ILibroRepository {
private:
    string nombreArchivo;
    string archivoTemporal;

public:
    LibroRepositoryArchivo(const string& nombreArchivo);
    void crearLibro(const Libro& libro) override;
    vector<Libro> listarLibros() override;
    Libro buscarLibroPorCodigo(int codigo) override;
    void actualizarLibro(const Libro& libroActualizado) override;
    void eliminarLibro(int codigo) override;
};
