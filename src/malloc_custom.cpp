#include "../include/malloc_custom.h"
#include <iostream>

// puntero global al inicio de la lista de bloques
void *global_base = NULL;

// dividir bloque si tiene suficiente espacio sobrante
void split_block(struct Block *b, size_t size)
{
    // calculo donde empieza el nuevo bloque (después del bloque actual + su tamaño)
    struct Block *new_block = (struct Block *)((char *)b + BLOCK_SIZE + size);

    // nuevo bloque heredar el tamaño sobrante
    new_block->size = b->size - size - BLOCK_SIZE;
    new_block->next = b->next;
    new_block->free = true;

    // ajustamos el bloque original
    b->size = size;
    b->next = new_block;
}

// busca el primero bloque libre que pueda acomodar el tamaño solicitado
struct Block *find_free_block(struct Block **last, size_t size)
{
    struct Block *current = (struct Block *)global_base;
    while (current && !(current->free && current->size >= size))
    {
        *last = current;
        current = current->next;
    }
    return current;
}

// solicita más espacio al sistema operativo usando sbrk
struct Block *request_space(struct Block *last, size_t size)
{
    struct Block *block = (struct Block *)sbrk(0);
    void *request = sbrk(size + BLOCK_SIZE);

    if (request == (void *)-1)
        return NULL; // error de memoria del SO

    if (last)
        last->next = block;

    block->size = size;
    block->next = NULL;
    block->free = false;
    return block;
}

// función principal de asignación de memoria
void *my_malloc(size_t size)
{
    if (size <= 0)
        return NULL;

    size = ALIGN(size);

    struct Block *block;

    if (!global_base)
    {
        block = request_space(NULL, size);
        if (!block)
            return NULL;
        global_base = block;
    }
    else
    {
        struct Block *last = (struct Block *)global_base;
        block = find_free_block(&last, size);

        if (!block)
        {
            block = request_space(last, size);
            if (!block)
                return NULL;
        }
        else
        {
            // splitting implementacion
            // solo dividimos si sobra espacio suficiente para otra cabecera + mínimo de datos
            if ((block->size - size) >= (BLOCK_SIZE + 8))
            {
                split_block(block, size);
            }
            block->free = false;
        }
    }
    return (void *)(block + 1);
}

// función de liberación de memoria
void my_free(void *ptr)
{
    if (!ptr)
        return;

    struct Block *block_ptr = (struct Block *)ptr - 1; // obtenemos el bloque a partir del puntero del usuario
    block_ptr->free = true;

    // fusión hacia adelante: si el siguiente bloque está libre, lo fusionamos
    if (block_ptr->next && block_ptr->next->free)
    {
        block_ptr->size += BLOCK_SIZE + block_ptr->next->size; // aumentamos
        block_ptr->next = block_ptr->next->next;               // saltamos el bloque siguiente
    }
}

// para comprobar que todo va
void debug_heap()
{
    extern void *global_base; // Accedemos al puntero global
    struct Block *actual = (struct Block *)global_base;
    std::cout << "\n--- ESTADO ACTUAL DEL HEAP ---" << std::endl;
    if (!actual)
        std::cout << "(Heap vacío)" << std::endl;

    while (actual)
    {
        std::cout << "[ Bloque en: " << actual
                  << " | Tamaño: " << actual->size
                  << " | Libre: " << (actual->free ? "SÍ" : "NO")
                  << " | Siguiente: " << actual->next << " ]" << std::endl;
        actual = actual->next;
    }
    std::cout << "------------------------------\n"
              << std::endl;
}