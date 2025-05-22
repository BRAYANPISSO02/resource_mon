#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "tui.h"

void draw_screen(const CPUInfo *cpuinfo, const float *cpu_usage, const MemInfo *meminfo) {
    // Limpia la pantalla (versión simple)
    printf("\033[H\033[J");  // Mueve cursor al inicio y limpia pantalla

    printf("===== MONITOR DE RECURSOS =====\n\n");

    printf("CPU: %s\n", cpuinfo->model_name);
    printf("Fabricante: %s\n", cpuinfo->vendor_id);
    printf("Núcleos físicos: %d\n", cpuinfo->cores);
    printf("Hilos (lógicos): %d\n", cpuinfo->threads);
    for (int i = 0; i < cpuinfo->threads; i++) {
        printf("CPU %d: %.2f%% uso\n", i, cpu_usage[i]);
    }

    printf("\nMemoria RAM total: %lu MB\n", meminfo->mem_total_kb / 1024);
    printf("Memoria RAM usada: %.2f%%\n", get_used_mem_percent(meminfo));

    printf("Swap total: %lu MB\n", meminfo->swap_total_kb / 1024);
    printf("Swap usada: %.2f%%\n", get_used_swap_percent(meminfo));

    printf("\nPresione 'q' para salir\n");
}

// Configura terminal en modo no bloqueante
static void set_input_mode(int enable) {
    static struct termios oldt, newt;

    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, 0);
    }
}

// Retorna 1 si el usuario presiona 'q'
int tui_check_exit() {
    set_input_mode(1);

    int ch = getchar();

    set_input_mode(0);

    return ch == 'q' || ch == 'Q';
}
