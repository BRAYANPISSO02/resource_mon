#ifndef MEMINFO_MANIP_H
#define MEMINFO_MANIP_H

typedef struct {
    unsigned long mem_total_kb;
    unsigned long mem_available_kb;
    unsigned long swap_total_kb;
    unsigned long swap_free_kb;
} MemInfo;

int get_mem_info(MemInfo *info);
float get_used_mem_percent(const MemInfo *info);
float get_used_swap_percent(const MemInfo *info);

#endif // MEMINFO_MANIP_H
