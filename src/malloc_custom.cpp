#include "../include/malloc_custom.h"

// puntero global al inicio de la lista de bloques
void* global_base = NULL;

// busca el primero bloque libre que pueda acomodar el tamaño solicitado
struct Block* find_free_block(struct Block** last, size_t size) {
    struct Block* current = (struct Block*)global_base;
    while (current && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

// solicita más espacio al sistema operativo usando sbrk
struct Block* request_space(struct Block* last, size_t size) {
    struct Block* block = (struct Block*)sbrk(0);
    void* request = sbrk(size + BLOCK_SIZE);

    if (request == (void*)-1) return NULL; // error de memoria del SO

    if (last) last->next = block;
    
    block->size = size;
    block->next = NULL;
    block->free = false;
    return block;
}

// función principal de asignación de memoria
void* my_malloc(size_t size) {
    if (size <= 0) return NULL;

    size = ALIGN(size); // aseguramos que el tamaño esté alineado a 8 bytes

    struct Block* block;

    if (!global_base) { // primera llamada, no hay bloques aún
        block = request_space(NULL, size);
        if (!block) return NULL;
        global_base = block;
    } else {
        struct Block* last = (struct Block*)global_base;
        block = find_free_block(&last, size);
        if (!block) { // no hay bloque libre suficiente, solicitamos más espacio
            block = request_space(last, size);
            if (!block) return NULL;
        } else {      // encontramos un bloque libre adecuado
            block->free = false;
        }
    }

    // return el puntero al espacio útil para el usuario (después de los metadatos)
    return (void*)(block + 1);
}

// función de liberación de memoria
void my_free(void* ptr) {
    if (!ptr) return;

    // obtenemos el bloque correspondiente a este puntero (restando el tamaño de la cabecera)
    struct Block* block_ptr = (struct Block*)ptr - 1;
    block_ptr->free = true;
}