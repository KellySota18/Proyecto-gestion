#include "ProductoRepositoryArchivo.h"
#include "ProductoService.h"
#include "LibroRepositoryArchivo.h"
#include "LibroService.h"
#include <iostream>
#include <limits>
using namespace std;

static void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static int leerOpcion(const string& mensaje) {
    int opcion;
    cout << mensaje;
    if (!(cin >> opcion)) {
        limpiarEntrada();
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return opcion;
}

static void menuProductos(ProductoService& servicio) {
    int opcion;
    do {
        cout << "\n===== MENU PRODUCTOS =====" << endl;
        cout << "1. Registrar producto" << endl;
        cout << "2. Listar productos" << endl;
        cout << "3. Buscar producto" << endl;
        cout << "4. Actualizar producto" << endl;
        cout << "5. Eliminar producto" << endl;
        cout << "0. Volver al menu principal" << endl;

        opcion = leerOpcion("Seleccione una opcion: ");

        try {
            switch (opcion) {
                case 1: servicio.registrarProducto(); break;
                case 2: servicio.listarProductos();   break;
                case 3: servicio.buscarProducto();    break;
                case 4: servicio.actualizarProducto();break;
                case 5: servicio.eliminarProducto();  break;
                case 0: cout << "Volviendo al menu principal..." << endl; break;
                default: cout << "Opcion invalida." << endl; break;
            }
        }
        catch (const exception& error) {
            cout << "Error: " << error.what() << endl;
        }
    } while (opcion != 0);
}

static void menuLibros(LibroService& servicio) {
    int opcion;
    do {
        cout << "\n===== MENU LIBROS =====" << endl;
        cout << "1. Registrar libro" << endl;
        cout << "2. Listar libros" << endl;
        cout << "3. Buscar libro" << endl;
        cout << "4. Actualizar libro" << endl;
        cout << "5. Eliminar libro" << endl;
        cout << "0. Volver al menu principal" << endl;

        opcion = leerOpcion("Seleccione una opcion: ");

        try {
            switch (opcion) {
                case 1: servicio.registrarLibro();  break;
                case 2: servicio.listarLibros();    break;
                case 3: servicio.buscarLibro();     break;
                case 4: servicio.actualizarLibro(); break;
                case 5: servicio.eliminarLibro();   break;
                case 0: cout << "Volviendo al menu principal..." << endl; break;
                default: cout << "Opcion invalida." << endl; break;
            }
        }
        catch (const exception& error) {
            cout << "Error: " << error.what() << endl;
        }
    } while (opcion != 0);
}

int main() {
    ProductoRepositoryArchivo productoRepo("inventario.txt");
    ProductoService productoService(&productoRepo);

    LibroRepositoryArchivo libroRepo("biblioteca.txt");
    LibroService libroService(&libroRepo);

    int opcion;
    do {
        cout << "\n===== MENU PRINCIPAL =====" << endl;
        cout << "1. Gestionar productos" << endl;
        cout << "2. Gestionar libros" << endl;
        cout << "0. Salir" << endl;

        opcion = leerOpcion("Seleccione una opcion: ");

        switch (opcion) {
            case 1: menuProductos(productoService); break;
            case 2: menuLibros(libroService);        break;
            case 0: cout << "Saliendo del programa..." << endl; break;
            default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);

    return 0;
}
