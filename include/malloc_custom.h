#ifndef MALLOC_CUSTOM_H
#define MALLOC_CUSTOM_H

#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>

// alinear a 8 bytes para evitar problemas de alineación
#define ALIGN(size) (((size) + (8-1)) & ~(8-1)) // formula para alinear a 8 bytes

// estructura de metadatos para cada bloque en el heap
struct Block {
    size_t size;        // tamaño útil para el usuario
    bool free;          // true si el bloque está disponible
    struct Block* next; // siguiente bloque en la lista enlazada
};

// tamaño de la cabecera (metadatos)
#define BLOCK_SIZE ALIGN(sizeof(struct Block)) // asegura que los datos estén alineados

// funciones (por ahora)
void* my_malloc(size_t size);
void my_free(void* ptr);
void debug_heap();

#endif