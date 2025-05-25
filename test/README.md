# Carpeta test

Esta carpeta contiene las pruebas unitarias para el proyecto `resource_mon`. Los tests están diseñados para verificar el correcto funcionamiento de cada módulo del sistema: CPU, memoria y la interfaz de usuario en consola (TUI).

---

## Contenido de la carpeta

- **cpuinfo_test.c**  
  Test para verificar las funciones relacionadas con la información de la CPU (`cpuinfo_manip`). Este test obtiene y muestra el modelo, fabricante, número de núcleos y hilos de la CPU, así como el porcentaje de uso de cada hilo.

- **meminfo_test.c**  
  Test para verificar las funciones relacionadas con la información de la memoria (`meminfo_manip`). Este test obtiene y muestra la memoria total, disponible y swap, así como el porcentaje de memoria usada.

- **tui_test.c**  
  Test para verificar la interfaz de usuario en consola (TUI). Muestra en pantalla la información de la CPU y la memoria y espera la tecla `'q'` para finalizar la prueba.

- **Makefile**  
  Reglas para compilar y generar los ejecutables de los tests en la carpeta `bin`. Además, gestiona la limpieza de archivos generados.

---
## Estructura

test
├── bin                   # Ejecutables compilados de los tests
│   ├── cpuinfo_test
│   ├── meminfo_test
│   └── tui_test
├── src                   # Código fuente de los tests
│   ├── cpuinfo_test.c
│   ├── meminfo_test.c
│   ├── tui_test.c
│   └── Makefile          # Makefile para compilar los tests
├── Makefile              # Makefile principal de la carpeta test
└── README.md             # Documentación de los tests (README que elaboramos)


---
## Descripción de los tests

### cpuinfo_test.c

Este test verifica que las funciones de `cpuinfo_manip` funcionen correctamente:

- **`get_cpu_info`**  
  - Verifica que se pueda obtener correctamente la información de la CPU:  
    - Modelo de CPU  
    - Fabricante de la CPU  
    - Número de núcleos físicos y lógicos  
    - Uso de cada hilo de CPU

- **`get_cpu_usage_percentages`**  
  - Verifica que se calculen correctamente los porcentajes de uso por hilo.

### meminfo_test.c

Este test verifica que las funciones de `meminfo_manip` funcionen correctamente:

- **`get_mem_info`**  
  - Verifica que se pueda obtener correctamente la información de la memoria:  
    - Memoria total  
    - Memoria disponible  
    - Memoria swap total y libre

- **`get_used_mem_percent`**  
  - Verifica que se calcule correctamente el porcentaje de uso de memoria.

- **`get_used_swap_percent`**  
  - Verifica que se calcule correctamente el porcentaje de uso de swap.

### tui_test.c

Este test verifica el funcionamiento de la interfaz de usuario en consola (TUI):

- **Interfaz**  
  - Muestra la información de la CPU y la memoria usando `draw_screen`.
  - Permite verificar que la pantalla se actualice correctamente.

- **Entrada del usuario**  
  - Espera la tecla `'q'` para finalizar la prueba usando la función `tui_check_exit`.

---

## Uso del Makefile

### Comandos disponibles en el Makefile:

- `make`  
  Compila todos los archivos fuente de prueba en la carpeta `test/src/`, generando los ejecutables en la carpeta `test/bin`.

- `make clean`  
  Elimina los archivos objeto `.o` y los ejecutables generados en la carpeta `test/bin`.

---

## Ejecución de los tests

Para ejecutar los tests, sigue estos pasos:

1. **Compilar los tests**  
   Desde la raíz del proyecto, ejecuta el siguiente comando para compilar todos los tests:

   ```bash
   make tests
