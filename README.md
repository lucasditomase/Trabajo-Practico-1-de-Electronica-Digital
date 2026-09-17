# Electrónica Digital - Trabajo Práctico 1
### Universidad Católica Argentina (UCA) - Facultad de Ingeniería y Ciencias Agrarias

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/lucasditomase/Trabajo-Practico-1-de-Electronica-Digital)

Este repositorio contiene la resolución completa y explicada del **Trabajo Práctico 1** de la materia **Electrónica Digital** (Carrera de Ingeniería Informática, UCA).

El proyecto abarca tanto la implementación e inspección a nivel de bits de las actividades en código C (estándar C99) como la redacción del informe técnico académico en Markdown.

---

## Ejecución Rápida en GitHub Codespaces

Puedes ejecutar y probar todo este proyecto directamente desde tu navegador sin instalar nada localmente:

1. Haz clic en el botón superior **"Open in GitHub Codespaces"** (o crea un Codespace desde tu repositorio de GitHub).
2. Abre la terminal integrada en VS Code / Codespaces.
3. Compila y ejecuta todo con un solo comando:
   ```bash
   make run
   ```

---

## Ejecución Local

### Requisitos Previos
* Compilador de C compatible con C99 (`gcc` recomendado).
* Herramienta `make`.

### Comandos de Compilación y Ejecución
El proyecto incluye un `Makefile` con objetivos simplificados:

| Comando | Descripción |
| :--- | :--- |
| `make` | Compila todos los ejecutables (`tp1_obligatorios` y `tp1_ia_experiments`). |
| `make run` | Compila y ejecuta la totalidad de los programas del Trabajo Práctico. |
| `make run-obligatorios` | Compila y ejecuta únicamente los Puntos Obligatorios (1 al 5). |
| `make run-experimentos` | Compila y ejecuta únicamente los Experimentos de IA (IA1 al IA6). |
| `make clean` | Elimina los archivos binarios generados. |
| `make help` | Muestra la ayuda de comandos disponibles. |

---

## Estructura del Repositorio

```text
.
├── .devcontainer/
│   └── devcontainer.json    # Configuración de entorno para GitHub Codespaces (GCC, GDB, Make)
├── src/
│   ├── tp1_obligatorios.c   # Implementación de los Puntos Obligatorios 1 al 5
│   └── tp1_ia_experiments.c # Implementación de los Experimentos de IA IA1 al IA6
├── Makefile                 # Reglas de compilación y ejecución automatizadas
├── Informe_TP1_Digital.md   # Informe técnico final completo con teoría, análisis de bits y salidas
└── README.md                # Guía de uso e instrucciones del proyecto
```

---

## Contenido del Trabajo Práctico

### Puntos Obligatorios (1 al 5)
* **Punto 1:** Inspección de memoria real (byte a byte, LSB/MSB), rangos y representación de `char`, `unsigned char`, `int` y `unsigned int`.
* **Punto 2:** Descomposición e inspección del estándar **IEEE 754** para flotantes de 32 bits (bit de signo, exponente polarizado y mantisa con bit oculto).
* **Punto 3:** Análisis del mecanismo de **extensión de signo** en conversión de `char` a `int`.
* **Punto 4:** Verificación del comportamiento ante **desbordamiento** (*wrap-around*) y detección en ALU ($C_{in} \oplus C_{out}$).
* **Punto 5:** Demostración de la **pérdida de precisión** en `float` por alineación de mantisas en la FPU.

### Experimentos de IA (IA1 al IA6)
* **IA1:** Inexactitud de flotantes, error acumulado y comparaciones con margen $\epsilon$ (`EPSILON`).
* **IA2:** Promoción implícita en comparaciones mixtas (`signed` vs `unsigned`).
* **IA3:** Truncamiento en división entera y signo del resto en C99.
* **IA4:** Desbordamiento en multiplicaciones antes de la asignación y promoción explícita.
* **IA5:** Asimetría del rango en complemento a 2 y comportamiento de `INT_MIN`.
* **IA6:** Detección de acarreo (*Carry*) en software para enteros sin signo.
