# 🖥 resource_mon

**Monitor de recursos del sistema en Linux (CLI)**  
Proyecto para el Taller de Programación de Sistemas – Linux Embebidos 2025-1S.

---

## Integrantes del equipo

- **Tomás Rocha Castaño** – 1054856763  
- **Brayan Ricardo Pisso Ramírez** – 1004249850

---

## Descripción

El programa `resource_mon` permite monitorear desde la consola la información de recursos del sistema Linux embebido, mostrando:  

- Nombre y fabricante de la CPU.  
- Número de núcleos físicos y lógicos (hilos).  
- Porcentaje de uso de cada hilo de CPU.  
- Memoria RAM y Swap total y porcentaje de uso.  
- Actualización automática cada segundo.  
- Finaliza al presionar la tecla `q`, `Ctrl+C` o cerrar la terminal.

---

## Estructura del proyecto

resource_mon
├── bin # Ejecutables compilados
│   └── resource_mon
├── obj # Archivos objeto (.o) intermedios
│   ├── cpuinfo_manip.o
│   ├── cpuinfo_test.o
│   ├── meminfo_manip.o
│   ├── meminfo_test.o
│   ├── resource_mon.o
│   ├── tui_test.o
│   └── tui.o
├── src # Código fuente principal
│   ├── cpuinfo_manip.c
│   ├── cpuinfo_manip.h
│   ├── meminfo_manip.c
│   ├── meminfo_manip.h
│   ├── resource_mon.c
│   ├── tui.c
│   └── tui.h
│   └── Makefile # Reglas para compilar objetos en src
├── test # Tests unitarios
│   ├── bin # Ejecutables de test
│   │   ├── cpuinfo_test
│   │   ├── meminfo_test
│   │   └── tui_test
│   ├── src # Código fuente de tests
│   │   ├── cpuinfo_test.c
│   │   ├── Makefile
│   │   │── meminfo_test.c
│   │   └── tui_test.c
│   ├── Makefile # Makefile para tests
│   └── README.md # Documentación de tests
├── Makefile # Makefile principal
└── README.md # Documentación general (este archivo)

---

## Descripción de módulos principales

### 1. cpuinfo_manip

Este módulo es responsable de obtener y procesar la información relativa a la CPU, mediante la lectura de los archivos del sistema Linux:

- **`get_cpu_info(CPUInfo *info)`**  
  Lee `/proc/cpuinfo` para obtener:  
  - Nombre del modelo de CPU (`model_name`).  
  - Identificador del fabricante (`vendor_id`).  
  - Número de núcleos físicos (`cores`).  
  - Número de hilos lógicos (`threads`).  

- **`get_cpu_usage_percentages(float *percentages, int thread_count)`**  
  Obtiene el porcentaje de uso de CPU por hilo (núcleo lógico), leyendo dos veces los tiempos de CPU de `/proc/stat` con un intervalo de 1 segundo para calcular la variación de uso activo vs. inactivo.  
  Devuelve un arreglo de porcentajes de uso para cada hilo.

### 2. meminfo_manip

Este módulo obtiene información de la memoria física y de intercambio (swap), leyendo `/proc/meminfo`:

- **`get_mem_info(MemInfo *info)`**  
  Lee y almacena:  
  - Memoria total instalada (`mem_total_kb`).  
  - Memoria disponible (`mem_available_kb`).  
  - Memoria swap total (`swap_total_kb`).  
  - Memoria swap libre (`swap_free_kb`).  

- **`get_used_mem_percent(const MemInfo *info)`**  
  Calcula el porcentaje de uso de memoria física.  

- **`get_used_swap_percent(const MemInfo *info)`**  
  Calcula el porcentaje de uso de memoria swap.

### 3. tui (Interfaz de usuario en consola)

Este módulo se encarga de la interacción con el usuario a través de la consola en modo texto (CLI):

- **`draw_screen(const CPUInfo *cpuinfo, const float *cpu_usage, const MemInfo *meminfo)`**  
  Imprime en pantalla toda la información actualizada del sistema:  
  - Modelo y fabricante de CPU.  
  - Número de núcleos y hilos.  
  - Porcentaje de uso de cada hilo de CPU.  
  - Memoria RAM total y porcentaje usada.  
  - Swap total y porcentaje usado.  
  Limpia la pantalla antes de mostrar la nueva información para que la actualización sea visualmente clara.

- **`tui_check_exit()`**  
  Detecta si el usuario ha presionado la tecla `'q'` o `'Q'` para indicar salida. Usa modo no bloqueante para lectura sin detener la ejecución del programa.

### 4. resource_mon.c (Programa principal)

Controla la ejecución del programa:

- Configura una señal para capturar interrupciones (`Ctrl+C`) y permitir salida ordenada.  
- Obtiene la información estática de CPU al inicio (`get_cpu_info`).  
- En un ciclo que se repite cada segundo:  
  - Calcula el porcentaje de uso por hilo de CPU (`get_cpu_usage_percentages`).  
  - Obtiene el estado actual de memoria (`get_mem_info`).  
  - Actualiza la pantalla con `draw_screen`.  
  - Consulta si el usuario presionó la tecla de salida (`q`) mediante `tui_check_exit()`.  
- Finaliza liberando recursos y mostrando mensaje de salida.

---

## Uso de Make

### Makefile principal (raíz)

- `make resource_mon` : compila el programa principal.  
- `make tests` : compila los ejecutables de test en `test/bin`.  
- `make all` : compila tanto el programa principal como los tests.  
- `make clean` : elimina todos los archivos objeto y ejecutables.  
- `make src` : compila sólo los archivos objeto en `src/`.

---

### Makefile en src/

Define las reglas para compilar los archivos `.c` en `.o` dentro de `obj` y es invocado desde el Makefile principal.  

---

### Makefile en test/

Gestiona la compilación de los tests unitarios:

- Compila los archivos de prueba `.c` en objetos.  
- Genera los ejecutables de test en `test/bin` (`cpuinfo_test`, `meminfo_test`, `tui_test`).  
- Incluye reglas para limpiar los objetos y ejecutables de test.

---

## Ejecución del programa

```bash
./bin/resource_mon

---

## Créditos

Proyecto desarrollado por el equipo para el Taller de Programación de Sistemas - Linux Embebidos 2025-1S.
