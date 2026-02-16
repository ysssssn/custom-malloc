#include <iostream>
#include <vector>
#include "../include/malloc_custom.h"

extern void debug_heap();

int main() {
    std::cout << "=== PRUEBAS DE my_malloc y my_free ===" << std::endl;

    // prueba 1: alineación de 8 bytes
    std::cout << "\n1. Verificando Alineación de 8 bytes..." << std::endl;
    void* p1 = my_malloc(10); // Pedimos 10, debería alinear a 16
    std::cout << "Pedido: 10 bytes | Dirección: " << p1 << std::endl;
    
    // verificamos que la dirección esté alineada a 8 bytes
    if (((size_t)p1 % 8) == 0) {
        std::cout << ">> [OK] Dirección alineada correctamente." << std::endl;
    } else {
        std::cout << ">> [ERROR] Dirección NO alineada." << std::endl;
    }

    // prueba 2: splitting (división de bloques)
    std::cout << "\n2. Verificando Splitting (División de bloques)..." << std::endl;
    std::cout << "Liberando el primer bloque para crear un hueco grande..." << std::endl;
    my_free(p1); 
    debug_heap();

    std::cout << "Pidiendo 8 bytes (Debería dividir el bloque libre anterior)..." << std::endl;
    void* p2 = my_malloc(8);
    debug_heap();

    // prueba 3: integridad de datos
    std::cout << "\n3. Verificando integridad de datos..." << std::endl;
    int* numeros = (int*)p2;
    numeros[0] = 1234;
    numeros[1] = 5678;
    
    if (numeros[0] == 1234 && numeros[1] == 5678) {
        std::cout << ">> [OK] Datos persistentes y correctos." << std::endl;
    }

    std::cout << "\n=== FIN ===" << std::endl;
    return 0;
}