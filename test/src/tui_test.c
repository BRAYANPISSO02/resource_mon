#include <stdio.h>
#include <unistd.h>
#include "../src/tui.h"
#include "../src/cpuinfo_manip.h"
#include "../src/meminfo_manip.h"

int main() {
    printf("Iniciando prueba de TUI...\n");

    CPUInfo cpuinfo;
    if (get_cpu_info(&cpuinfo) != 0) {
        fprintf(stderr, "Error al obtener información de CPU.\n");
        return 1;
    }

    float usage[cpuinfo.threads];
    get_cpu_usage_percentages(usage, cpuinfo.threads);

    MemInfo meminfo;
    if (get_mem_info(&meminfo) != 0) {
        fprintf(stderr, "Error al obtener información de memoria.\n");
        return 1;
    }

    draw_screen(&cpuinfo, usage, &meminfo);

    printf("Presiona 'q' para continuar con el test...\n");
    while (!tui_check_exit()) {
        sleep(1);
    }

    printf("TUI test finalizado correctamente.\n");
    return 0;
}
