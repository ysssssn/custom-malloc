#include <iostream>
#include "../include/malloc_custom.h"

int main() {
    std::cout << "--- Test Gestor de Memoria ---" << std::endl;

    // prueba de asignación y liberación
    int* arr = (int*)my_malloc(5 * sizeof(int));
    if (arr) {
        for(int i=0; i<5; i++) arr[i] = i * 10;
        std::cout << "Asignación exitosa. Valor 3: " << arr[3] << std::endl;
        my_free(arr);
        std::cout << "Memoria liberada." << std::endl;
    }

    char* c = (char*)my_malloc(10);
    if (c) {
        std::cout << "Segunda asignación en: " << (void*)c << std::endl;
        my_free(c);
    }

    return 0;
}