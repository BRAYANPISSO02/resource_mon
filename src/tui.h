#ifndef TUI_H
#define TUI_H

#include "cpuinfo_manip.h"
#include "meminfo_manip.h"

void draw_screen(const CPUInfo *cpuinfo, const float *cpu_usage, const MemInfo *meminfo);
int tui_check_exit();  // Devuelve 1 si el usuario presiona 'q'

#endif // TUI_H
