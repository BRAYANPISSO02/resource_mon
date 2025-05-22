#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "cpuinfo_manip.h"
#include "meminfo_manip.h"
#include "tui.h"

static volatile int keep_running = 1;

void handle_sigint(int sig) {
    keep_running = 0;
}

int main() {
    signal(SIGINT, handle_sigint);  // Captura Ctrl+C

    CPUInfo cpuinfo;
    if (get_cpu_info(&cpuinfo) != 0) {
        fprintf(stderr, "Error al obtener información de la CPU.\n");
        return 1;
    }

    float *cpu_usage = malloc(sizeof(float) * cpuinfo.threads);
    if (!cpu_usage) {
        perror("malloc");
        return 1;
    }

    while (keep_running) {
        // Obtener porcentaje de uso de CPU
        get_cpu_usage_percentages(cpu_usage, cpuinfo.threads);

        // Obtener información de memoria
        MemInfo meminfo;
        get_mem_info(&meminfo);

        // Mostrar en pantalla
        draw_screen(&cpuinfo, cpu_usage, &meminfo);

        // Verificar si el usuario quiere salir
        if (tui_check_exit()) {
            break;
        }

        sleep(1);
    }

    free(cpu_usage);
    printf("\nSaliendo de resource_mon...\n");
    return 0;
}
