#  test – Pruebas unitarias de `resource_mon`

Esta carpeta contiene las pruebas individuales para cada módulo del proyecto.  
Los archivos `.c` de prueba están ubicados en `test/src/` y los ejecutables generados se encuentran en `test/bin/`.

---

##  Estructura

test
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

##  Tests disponibles

###  cpuinfo_test.c

- Verifica:
  - Modelo de la CPU
  - Fabricante
  - Núcleos físicos y hilos
  - Porcentaje de uso por hilo

###  meminfo_test.c

- Verifica:
  - Lectura de RAM total y disponible
  - Lectura de Swap total y libre
  - Porcentaje de uso de RAM y Swap

###  tui_test.c

- Muestra una pantalla de prueba con los datos actuales
- Espera a que el usuario presione `'q'` para terminar

---

##  Compilación y ejecución

### Desde la raíz del proyecto:

```bash
make tests
