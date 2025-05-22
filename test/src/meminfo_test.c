#include <stdio.h>
#include "../src/meminfo_manip.h"

int main() {
    MemInfo meminfo;
    if (get_mem_info(&meminfo) != 0) {
        printf("Error al leer /proc/meminfo\n");
        return 1;
    }

    printf("RAM Total: %lu MB\n", meminfo.mem_total_kb / 1024);
    printf("RAM Disponible: %lu MB\n", meminfo.mem_available_kb / 1024);
    printf("RAM Usada: %.2f%%\n", get_used_mem_percent(&meminfo));

    printf("Swap Total: %lu MB\n", meminfo.swap_total_kb / 1024);
    printf("Swap Libre: %lu MB\n", meminfo.swap_free_kb / 1024);
    printf("Swap Usada: %.2f%%\n", get_used_swap_percent(&meminfo));

    return 0;
}
