# custom-malloc

Implementación personalizada de un allocator de memoria dinámica en C++ que simula el comportamiento de `malloc` y `free`.

## Características

- **Asignación de memoria dinámica**: Solicita memoria al sistema operativo mediante `sbrk`.
- **Alineación de 8 bytes**: Garantiza que los datos estén correctamente alineados.
- **Splitting**: Divide bloques grandes en bloques más pequeños para optimizar el uso de memoria.
- **Coalescing**: Fusiona bloques libres contiguos para evitar fragmentación.
- **Gestión de metadatos**: Cada bloque incluye información sobre su tamaño y estado.

## Compilación

```bash
make
```

Genera el ejecutable en `bin/demo`.

## Ejecución

```bash
./bin/demo
```

## Limpieza

```bash
make clean
```

## Licencia

MIT License © 2026 Yassin