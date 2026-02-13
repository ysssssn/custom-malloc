#ifndef MALLOC_CUSTOM_H
#define MALLOC_CUSTOM_H

#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>

// estructura de metadatos para cada bloque en el heap
struct Block {
    size_t size;        // tamaño útil para el usuario
    bool free;          // true si el bloque está disponible
    struct Block* next; // siguiente bloque en la lista enlazada
};

// tamaño de la cabecera (metadatos)
#define BLOCK_SIZE sizeof(struct Block)

// funciones (por ahora)
void* my_malloc(size_t size);
void my_free(void* ptr);

#endif