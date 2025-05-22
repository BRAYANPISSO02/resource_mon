# 🖥 resource_mon

**Monitor de recursos del sistema en Linux (CLI)**
Proyecto para el Taller de Programación de Sistemas – Linux Embebidos 2025-1S.

---

##  Integrantes del equipo

- **Tomás Rocha Castaño** – 1054856763


---

##  Descripción

Este programa llamado `resource_mon` permite monitorear desde la consola:

- Nombre y fabricante de la CPU.
- Número de núcleos físicos y lógicos (hilos).
- Porcentaje de uso de cada hilo de CPU.
- Memoria RAM y Swap total y porcentaje de uso.
- Actualización automática cada segundo.
- Finaliza al presionar la tecla `q`, `Ctrl+C` o cerrar la terminal.

---

##  Estructura del proyecto

resource_mon
├── bin
│   └── resource_mon
├── Makefile
├── obj
│   ├── cpuinfo_manip.o
│   ├── cpuinfo_test.o
│   ├── meminfo_manip.o
│   ├── meminfo_test.o
│   ├── resource_mon.o
│   ├── tui.o
│   └── tui_test.o
├── README.md
├── src
│   ├── cpuinfo_manip.c
│   ├── cpuinfo_manip.h
│   ├── Makefile
│   ├── meminfo_manip.c
│   ├── meminfo_manip.h
│   ├── resource_mon.c
│   ├── tui.c
│   └── tui.h
└── test
    ├── bin
    │   ├── cpuinfo_test
    │   ├── meminfo_test
    │   └── tui_test
    ├── Makefile
    └── src
        ├── cpuinfo_test.c
        ├── Makefile
        ├── meminfo_test.c
        └── tui_test.c


---

##  Uso de Make

Desde la raíz del proyecto:

- `make resource_mon`: compila el programa principal.
- `make tests`: compila los ejecutables de test en `test/bin`.
- `make all`: compila programa y pruebas.
- `make clean`: elimina archivos `.o` y ejecutables.
- `make src`: compila sólo los objetos en `src/`.

---

##  Ejecución del programa

```bash
./bin/resource_mon
