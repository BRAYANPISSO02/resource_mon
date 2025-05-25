# Carpeta src

Esta carpeta contiene el código fuente principal del proyecto `resource_mon`.  

Aquí se implementan los módulos funcionales encargados de obtener la información del sistema (CPU y memoria), la interfaz de usuario en consola y el programa principal que integra todo.

---

## Estructura

src
├── cpuinfo_manip.c       # Implementación de funciones para manejo de info CPU
├── cpuinfo_manip.h       # Declaraciones y estructuras para info CPU
├── meminfo_manip.c       # Implementación de funciones para manejo de info memoria
├── meminfo_manip.h       # Declaraciones y estructuras para info memoria
├── resource_mon.c        # Programa principal que integra los módulos
├── tui.c                 # Implementación de la interfaz de usuario en consola
├── tui.h                 # Declaraciones de funciones para la interfaz (TUI)
└── Makefile              # Makefile para compilar los archivos fuente de src

---
## Contenido de la carpeta

- **cpuinfo_manip.c / cpuinfo_manip.h**  
  Funciones y estructuras para obtener y procesar la información de la CPU: modelo, fabricante, núcleos, hilos y porcentaje de uso.

- **meminfo_manip.c / meminfo_manip.h**  
  Funciones y estructuras para obtener y procesar la información de la memoria física y swap: total, disponible y porcentaje de uso.

- **tui.c / tui.h**  
  Funciones para la interfaz de usuario en modo texto (CLI), encargadas de mostrar la información en pantalla y detectar la entrada del usuario.

- **resource_mon.c**  
  Programa principal que ejecuta el ciclo de monitoreo, actualizando la pantalla y gestionando la interacción con el usuario.

- **Makefile**  
  Reglas para compilar los archivos fuente en objetos `.o` y preparar la carpeta para enlazado.

---

## Módulos y funciones principales

### cpuinfo_manip

- **Estructura `CPUInfo`**  
  ```c
  typedef struct {
      char model_name[128];
      char vendor_id[64];
      int cores;     // núcleos físicos
      int threads;   // hilos lógicos
  } CPUInfo;

### Funciones

#### int get_cpu_info(CPUInfo *info)
    Lee /proc/cpuinfo y llena la estructura CPUInfo con datos del sistema.
    Retorna 0 si tuvo éxito, -1 en caso de error.

#### int get_cpu_usage_percentages(float *percentages, int thread_count)
    Calcula el porcentaje de uso de CPU por cada hilo (núcleo lógico) leyendo /proc/stat dos veces con intervalo de 1 segundo.
    Llena el arreglo percentages con los valores calculados.

### Estrutura meminfo_manip
    typedef struct {
        unsigned long mem_total_kb;
        unsigned long mem_available_kb;
        unsigned long swap_total_kb;
        unsigned long swap_free_kb;
    } MemInfo;

#### Funciones

##### int get_mem_info(MemInfo *info)
    Lee /proc/meminfo y llena la estructura MemInfo con datos actuales de memoria.
    Retorna 0 si tuvo éxito, -1 en caso de error.

##### float get_used_mem_percent(const MemInfo *info)
    Calcula el porcentaje de memoria física usada.

##### float get_used_swap_percent(const MemInfo *info)
    Calcula el porcentaje de memoria swap usada.

### tui
#### Funciones

##### void draw_screen(const CPUInfo *cpuinfo, const float *cpu_usage, const MemInfo *meminfo)
    Limpia la pantalla y muestra la información actualizada de CPU y memoria.

##### int tui_check_exit()
    Detecta si el usuario presionó 'q' o 'Q' para indicar que desea salir.
    Usa modo no bloqueante para no detener la ejecución mientras espera entrada.

#### Detalles adicionales
    El módulo tui gestiona la salida en consola para mostrar las métricas del sistema (CPU y memoria) de manera interactiva. Permite la actualización continua de la pantalla sin generar nuevas líneas en cada ciclo.

### resource_mon.c

Este archivo contiene el programa principal que ejecuta el ciclo de monitoreo de CPU y memoria:

#### Configura una señal para manejar interrupciones (Ctrl+C).
#### Obtiene la información estática de la CPU al inicio del programa utilizando get_cpu_info.
#### En un ciclo que se repite cada segundo:

##### Obtiene el porcentaje de uso de CPU utilizando get_cpu_usage_percentages.
##### Obtiene la información de memoria usando get_mem_info.
##### Actualiza la pantalla con la información más reciente.
##### Verifica si el usuario presionó la tecla q para salir utilizando tui_check_exit.

#### Al finalizar, libera los recursos y muestra un mensaje de salida.

