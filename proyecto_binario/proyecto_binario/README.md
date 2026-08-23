# Sistema de Gestion (Variante binaria) — Productos y Libros

Segunda variante del proyecto, **independiente** de `proyecto/` (la version de
texto que ya se armo antes). Esta usa:

- **Producto**: persistencia **binaria** (`ProductoBinario` struct, archivo `productos.dat`)
- **Libro**: codigo tipo `int`, metodo `crearLibro()`, separador `;` en el archivo

## Estructura

```
proyecto_binario/
├── include/
│   ├── ProductoBinario.h          # Struct de Producto (creado: nunca lo subiste, se infirio del uso en el codigo)
│   ├── IProductoRepository.h      # Interfaz binaria (creada: no existia, listarProductos() retorna void)
│   ├── ProductoRepositoryBinario.h# Header del repo binario (creado: solo tenias el .cpp)
│   ├── ProductoService.h          # Tal cual la subiste
│   ├── Libro.h                    # Tal cual la subiste (codigo int, separador ;)
│   ├── ILibroRepository.h         # Tal cual la subiste (crearLibro, int)
│   ├── LibroRepositoryArchivo.h   # Tal cual la subiste
│   └── LibroService.h             # Tal cual la subiste
├── src/
│   ├── ProductoRepositoryBinario.cpp  # Version que ya habias subido (valida duplicados)
│   ├── ProductoService.cpp            # Tal cual la subiste
│   ├── Libro.cpp                      # Tal cual la subiste
│   ├── LibroRepositoryArchivo.cpp     # Creado: no lo habias subido para esta variante
│   ├── LibroService.cpp               # Recuperado de tu primera subida (coincide con este .h)
│   └── main.cpp                       # Creado: menu de consola
└── README.md
```

## Diferencias clave frente a `proyecto/` (la otra carpeta)

| Aspecto | `proyecto/` (texto) | `proyecto_binario/` (esta carpeta) |
|---|---|---|
| Producto | Clase `Producto`, texto (`inventario.txt`) | Struct `ProductoBinario`, binario (`productos.dat`) |
| Codigo de Libro | `long long` | `int` |
| Metodo crear Libro | `registrarLibro()` | `crearLibro()` |
| Separador de Libro | `\|` | `;` |

**No mezclar archivos entre las dos carpetas**: los headers de una son
incompatibles con los .cpp de la otra (firmas de metodos distintas).

## Compilar

```bash
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o sistema
./sistema
```

## Archivos generados

- `productos.dat` — binario, struct `ProductoBinario` de tamano fijo por registro
- `biblioteca.txt` — texto plano, una linea por libro: `codigo;titulo;autor;ejemplares`
