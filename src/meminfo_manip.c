#include <stdio.h>
#include <string.h>
#include "meminfo_manip.h"

int get_mem_info(MemInfo *info) {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) return -1;

    char label[64];
    unsigned long value;
    char unit[16];

    // Inicializar en 0
    info->mem_total_kb = 0;
    info->mem_available_kb = 0;
    info->swap_total_kb = 0;
    info->swap_free_kb = 0;

    while (fscanf(fp, "%63s %lu %15s\n", label, &value, unit) == 3) {
        if (strcmp(label, "MemTotal:") == 0)
            info->mem_total_kb = value;
        else if (strcmp(label, "MemAvailable:") == 0)
            info->mem_available_kb = value;
        else if (strcmp(label, "SwapTotal:") == 0)
            info->swap_total_kb = value;
        else if (strcmp(label, "SwapFree:") == 0)
            info->swap_free_kb = value;
    }

    fclose(fp);
    return 0;
}

float get_used_mem_percent(const MemInfo *info) {
    if (info->mem_total_kb == 0) return 0.0f;
    unsigned long used = info->mem_total_kb - info->mem_available_kb;
    return 100.0f * used / info->mem_total_kb;
}

float get_used_swap_percent(const MemInfo *info) {
    if (info->swap_total_kb == 0) return 0.0f;
    unsigned long used = info->swap_total_kb - info->swap_free_kb;
    return 100.0f * used / info->swap_total_kb;
}
