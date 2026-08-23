#pragma once
#include "ILibroRepository.h"
#include <string>
using namespace std;

class LibroRepositoryArchivo : public ILibroRepository {
private:
    string nombreArchivo;

public:
    LibroRepositoryArchivo(string nombreArchivo);

    void registrarLibro(const Libro& libro) override;
    vector<Libro> listarLibros() override;
    Libro buscarLibroPorCodigo(long long codigo) override;
    void actualizarLibro(const Libro& libroActualizado) override;
    void eliminarLibro(long long codigo) override;
};