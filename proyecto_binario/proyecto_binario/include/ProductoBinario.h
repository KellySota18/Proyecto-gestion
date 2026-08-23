#pragma once

// Estructura de tamano fijo para persistir productos en formato binario (productos.dat).
// IMPORTANTE: al ser un struct de tamano fijo, escrito con fwrite/ofstream::write,
// no se debe agregar ningun tipo de tamano variable (string, vector, etc.) aqui.
struct ProductoBinario {
    int codigo;
    char nombre[50];
    double precio;
    int stock;
};
