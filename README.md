# Custom Malloc

Un gestor de memoria personalizado implementado en C++ que emula el comportamiento de `malloc()` y `free()` usando `sbrk()`.

## Características

- Asignación dinámica de memoria personalizada
- Liberación de memoria con reutilización de bloques
- Metadatos para cada bloque (tamaño, estado, encadenamiento)
- Búsqueda de bloques libres disponibles

## Compilación

```bash
make
```

## Ejecución

```bash
./bin/demo
```

## Limpieza

```bash
make clean
```

## Estructura del Proyecto

- `src/` - Código fuente
- `include/` - Archivos de cabecera
- `Makefile` - Configuración de compilación

## Licencia

MIT License © 2026 Yassin