#include <stdio.h>
#include "../src/cpuinfo_manip.h"

int main() {
    CPUInfo info;
    get_cpu_info(&info);

    printf("Modelo: %s\n", info.model_name);
    printf("Fabricante: %s\n", info.vendor_id);
    printf("Núcleos físicos: %d\n", info.cores);
    printf("Hilos (lógicos): %d\n", info.threads);

    float usage[info.threads];
    get_cpu_usage_percentages(usage, info.threads);

    for (int i = 0; i < info.threads; i++) {
        printf("CPU %d: %.2f%% uso\n", i, usage[i]);
    }

    return 0;
}
