#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "cpuinfo_manip.h"

int get_cpu_info(CPUInfo *info) {
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp) return -1;

    char line[256];
    info->cores = 0;
    info->threads = 0;
    int model_set = 0, vendor_set = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "vendor_id", 9) == 0 && !vendor_set) {
            sscanf(line, "vendor_id : %s", info->vendor_id);
            vendor_set = 1;
        } else if (strncmp(line, "model name", 10) == 0 && !model_set) {
            sscanf(line, "model name : %[^\n]", info->model_name);
            model_set = 1;
        } else if (strncmp(line, "cpu cores", 9) == 0) {
            int cores;
            sscanf(line, "cpu cores : %d", &cores);
            if (info->cores == 0) info->cores = cores;
        } else if (strncmp(line, "processor", 9) == 0) {
            info->threads++;
        }
    }

    fclose(fp);
    return 0;
}

static int read_cpu_times(CPUStat *stats, int max_cpus) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) return -1;

    char line[512];
    int cpu_idx = 0;

    while (fgets(line, sizeof(line), fp) && cpu_idx < max_cpus) {
        if (strncmp(line, "cpu", 3) == 0 && isdigit(line[3])) {
            sscanf(line, "cpu%d %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                   &cpu_idx,
                   &stats[cpu_idx].user,
                   &stats[cpu_idx].nice,
                   &stats[cpu_idx].system,
                   &stats[cpu_idx].idle,
                   &stats[cpu_idx].iowait,
                   &stats[cpu_idx].irq,
                   &stats[cpu_idx].softirq,
                   &stats[cpu_idx].steal,
                   &stats[cpu_idx].guest,
                   &stats[cpu_idx].guest_nice);
        } else {
            break;
        }
    }

    fclose(fp);
    return cpu_idx;
}

int get_cpu_usage_percentages(float *percentages, int thread_count) {
    CPUStat prev[thread_count], curr[thread_count];

    read_cpu_times(prev, thread_count);
    sleep(1);
    read_cpu_times(curr, thread_count);

    for (int i = 0; i < thread_count; i++) {
        unsigned long long int prev_idle = prev[i].idle + prev[i].iowait;
        unsigned long long int curr_idle = curr[i].idle + curr[i].iowait;

        unsigned long long int prev_total = prev[i].user + prev[i].nice + prev[i].system +
                                            prev[i].idle + prev[i].iowait + prev[i].irq +
                                            prev[i].softirq + prev[i].steal + prev[i].guest +
                                            prev[i].guest_nice;

        unsigned long long int curr_total = curr[i].user + curr[i].nice + curr[i].system +
                                            curr[i].idle + curr[i].iowait + curr[i].irq +
                                            curr[i].softirq + curr[i].steal + curr[i].guest +
                                            curr[i].guest_nice;

        unsigned long long int total_diff = curr_total - prev_total;
        unsigned long long int idle_diff = curr_idle - prev_idle;

        if (total_diff == 0)
            percentages[i] = 0;
        else
            percentages[i] = 100.0 * (total_diff - idle_diff) / total_diff;
    }

    return 0;
}
