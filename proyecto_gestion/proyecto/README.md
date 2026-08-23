# Sistema de Gestion — Productos y Libros

Proyecto consolidado en C++ (patron Service + Repository) a partir de las
multiples versiones que tenias. Se eligio una version "final" coherente para
cada clase y se completaron las clases de dominio que faltaban.

## Estructura

```
proyecto/
├── include/                     # Headers (.h)
│   ├── Producto.h                # Clase de dominio Producto (creada: faltaba en tus archivos)
│   ├── Libro.h                   # Clase de dominio Libro (creada: faltaba en tus archivos)
│   ├── IProductoRepository.h     # Interfaz del repositorio de productos
│   ├── ILibroRepository.h        # Interfaz del repositorio de libros
│   ├── ProductoRepositoryArchivo.h
│   ├── LibroRepositoryArchivo.h
│   ├── ProductoService.h
│   └── LibroService.h
├── src/                          # Implementaciones (.cpp)
│   ├── Producto.cpp               # Serializa/deserializa Producto a texto (codigo|nombre|precio|stock)
│   ├── Libro.cpp                  # Serializa/deserializa Libro a texto (codigo|titulo|autor|ejemplares)
│   ├── ProductoRepositoryArchivo.cpp  # Persiste productos en inventario.txt, valida duplicados
│   ├── LibroRepositoryArchivo.cpp     # Persiste libros en biblioteca.txt, valida duplicados
│   ├── ProductoService.cpp        # Logica de negocio + validaciones + entrada de usuario (productos)
│   ├── LibroService.cpp           # Logica de negocio + validaciones + entrada de usuario (libros)
│   └── main.cpp                   # Menu de consola que conecta todo (creado: no existia)
└── README.md
```

## Que se eligio y por que

De las multiples versiones que subiste, se tomo la mas completa y consistente
de cada clase (la que valida duplicados, maneja errores de lectura, y coincide
exactamente con su interfaz/header):

- **Producto**: version basada en la clase `Producto` (texto, `inventario.txt`),
  NO la version binaria (`ProductoBinario`/`.dat`), porque el header final
  `ProductoService.h` solo declara metodos compatibles con la version de texto.
- **Libro**: version con `registrarLibro()` y codigos `long long`, que es la
  que coincide con `ILibroRepository.h`.

Se descartaron (no se incluyeron en este proyecto, pero siguen en tus archivos
originales por si las quieres comparar):
- Las 2 versiones de `ProductoRepositoryBinario` (.dat)
- Las versiones antiguas de `ProductoService`/`LibroService` con `codigo int`
  o metodos `crearLibro` en vez de `registrarLibro`

## Compilar

Desde la carpeta `proyecto/`:

```bash
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o sistema
./sistema
```

## Archivos de datos generados

- `inventario.txt` — productos, una linea por registro: `codigo|nombre|precio|stock`
- `biblioteca.txt` — libros, una linea por registro: `codigo|titulo|autor|ejemplares`

Se crean automaticamente en la carpeta donde ejecutes el programa.
