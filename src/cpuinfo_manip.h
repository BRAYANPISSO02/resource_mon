#ifndef CPUINFO_MANIP_H
#define CPUINFO_MANIP_H

typedef struct {
    char model_name[128];
    char vendor_id[64];
    int cores;         // núcleos físicos
    int threads;       // hilos lógicos
} CPUInfo;

typedef struct {
    unsigned long long int user;
    unsigned long long int nice;
    unsigned long long int system;
    unsigned long long int idle;
    unsigned long long int iowait;
    unsigned long long int irq;
    unsigned long long int softirq;
    unsigned long long int steal;
    unsigned long long int guest;
    unsigned long long int guest_nice;
} CPUStat;

int get_cpu_info(CPUInfo *info);
int get_cpu_usage_percentages(float *percentages, int thread_count);

#endif // CPUINFO_MANIP_H
