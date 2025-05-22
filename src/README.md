#  src – Código fuente de `resource_mon`

Esta carpeta contiene el código fuente modular del proyecto `resource_mon`.  
Cada archivo implementa una funcionalidad específica del sistema:

---

##  Módulos

###  cpuinfo_manip.c / .h

Funciones para obtener información de la CPU desde `/proc/cpuinfo` y `/proc/stat`.

**Funciones:**

- `int get_cpu_info(CPUInfo *info)`
  - Llena una estructura con:
    - Modelo de la CPU (`model_name`)
    - Fabricante (`vendor_id`)
    - Número de núcleos físicos (`cores`)
    - Número de hilos lógicos (`threads`)
- `int get_cpu_usage_percentages(float *percentages, int threads)`
  - Calcula el uso de CPU por hilo, devolviendo un arreglo de porcentajes por hilo (`CPU 0`, `CPU 1`, etc.).

**Estructura:**

```c
typedef struct {
    char model_name[128];
    char vendor_id[64];
    int cores;
    int threads;
} CPUInfo;
```

meminfo_manip.c / .h

Lectura de uso de memoria RAM y Swap desde /proc/meminfo.

Funciones:

   int get_mem_info(MemInfo *info)

   Llena la estructura con:

   RAM total y disponible (en KB)

   Swap total y libre (en KB)

  float get_used_mem_percent(const MemInfo *info)

   Devuelve el porcentaje de RAM usada.

  float get_used_swap_percent(const MemInfo *info)

   Devuelve el porcentaje de Swap usada.

Estructura:
typedef struct {
    unsigned long mem_total_kb;
    unsigned long mem_available_kb;
    unsigned long swap_total_kb;
    unsigned long swap_free_kb;
} MemInfo;

tui.c / .h

Interfaz de usuario basada en consola (CLI) que muestra los datos en la misma posición de pantalla.

Funciones:

    void draw_screen(const CPUInfo *cpuinfo, const float *cpu_usage, const MemInfo *meminfo)

        Muestra la información en pantalla, actualizándola cada segundo.

    int tui_check_exit()

        Retorna 1 si el usuario presiona la tecla q.

 resource_mon.c

Archivo principal que contiene el bucle principal del programa.

Responsabilidades:

    Llama a los módulos cpuinfo, meminfo y tui.

    Ejecuta el ciclo de actualización cada segundo.

    Finaliza cuando el usuario presiona q o Ctrl+C.

 Compilación desde esta carpeta

Desde src/, puedes usar:
make         # Compila los .o en ../obj/
make clean   # Limpia archivos objeto
