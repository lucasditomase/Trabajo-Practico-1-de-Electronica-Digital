/**
 * @file tp1_ia_experiments.c
 * @brief Implementación de los Experimentos con IA (IA1 al IA6) - Trabajo Práctico 1
 * @course Electrónica Digital | Universidad Católica Argentina (UCA)
 * @std ISO C99
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * Experimento IA1: Inexactitud en Punto Flotante y Comparaciones Directas
 */
void exp_ia1_inexactitud_flotante(void) {
    printf("======================================================================\n");
    printf("EXPERIMENTO IA1: Inexactitud en Punto Flotante y Comparaciones Directas\n");
    printf("======================================================================\n");

    float suma = 0.0f;
    for (int i = 0; i < 10; i++) {
        suma += 0.1f;
    }

    printf("Suma acumulada de 0.1f diez veces: %.10f\n", suma);
    printf("Comparación directa (suma == 1.0f): %s\n", (suma == 1.0f) ? "VERDADERO" : "FALSO");

    // Solución correcta usando tolerancia epsilon
    float epsilon = 1e-6f;
    bool son_iguales = fabsf(suma - 1.0f) < epsilon;
    printf("Comparación con EPSILON (1e-6f):  %s (Correcto en ingeniería)\n\n", son_iguales ? "VERDADERO" : "FALSO");
}

/**
 * Experimento IA2: Comparaciones Mixtas (signed vs unsigned)
 */
void exp_ia2_comparaciones_mixtas(void) {
    printf("======================================================================\n");
    printf("EXPERIMENTO IA2: Comparaciones Mixtas (signed vs unsigned)\n");
    printf("======================================================================\n");

    int negativo = -1;
    unsigned int uno = 1U;

    printf("Evaluando expresión en C: -1 < 1U\n");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
    if (negativo < uno) {
        printf("  Resultado C: -1 < 1U es VERDADERO\n");
    } else {
        printf("  Resultado C: -1 < 1U es FALSO\n");
        printf("  Explicación: Por las reglas 'Usual Arithmetic Conversions', -1 (0xFFFFFFFF)\n");
        printf("  es promovido a unsigned int, reorientando su valor a %u.\n", (unsigned int)negativo);
    }
#pragma GCC diagnostic pop

    // Solución correcta mediante casting explícito
    if (negativo < (int)uno) {
        printf("  Solución con casting (-1 < (int)1U): VERDADERO (Comparación correcta en con signo)\n\n");
    }
}

/**
 * Experimento IA3: División Entera y Truncamiento (ISO C99)
 */
void exp_ia3_division_entera_y_truncamiento(void) {
    printf("======================================================================\n");
    printf("EXPERIMENTO IA3: División Entera y Truncamiento (Estándar C99)\n");
    printf("======================================================================\n");

    printf("Resultados observados:\n");
    printf("   5 /  2 = %2d  |   5 %%  2 = %2d\n", 5 / 2, 5 % 2);
    printf("  (-5) /  2 = %2d  |  (-5) %%  2 = %2d\n", (-5) / 2, (-5) % 2);
    printf("   5 / (-2) = %2d  |   5 %% (-2) = %2d\n", 5 / (-2), 5 % (-2));
    printf("  (-5) / (-2) = %2d  |  (-5) %% (-2) = %2d\n\n", (-5) / (-2), (-5) % (-2));

    printf("Comprobación de Identidad Teórica: (a / b) * b + (a %% b) == a\n");
    int a = -5, b = 2;
    int q = a / b;
    int r = a % b;
    printf("  Para a = -5, b = 2 -> (%d * %d) + (%d) = %d (Cumple: %s)\n\n",
           q, b, r, (q * b) + r, ((q * b) + r == a) ? "SI" : "NO");
}

/**
 * Experimento IA4: Multiplicación y Promoción de Tipos
 */
void exp_ia4_multiplicacion_y_promocion(void) {
    printf("======================================================================\n");
    printf("EXPERIMENTO IA4: Multiplicación y Promoción de Tipos de Datos\n");
    printf("======================================================================\n");

    int a = 100000;
    int b = 100000;

    long long mal = (long long)(a * b); // Multiplicación calculada en registros de 32 bits antes de la asignación
    long long bien = (long long)a * b; // Promoción antes de la multiplicación

    printf("Variables: a = %d, b = %d (Producto real: 10,000,000,000)\n", a, b);
    printf("  Sin casting previa: (long long)(a * b) = %lld (ERROR por overflow 32 bits)\n", mal);
    printf("  Con casting previa: (long long)a * b   = %lld (CORRECTO)\n\n", bien);
}

/**
 * Experimento IA5: Asimetría del Complemento a la Base e INT_MIN
 */
void exp_ia5_asimetria_complemento_base(void) {
    printf("======================================================================\n");
    printf("EXPERIMENTO IA5: Asimetría del Complemento a la Base e INT_MIN\n");
    printf("======================================================================\n");

    int min_val = INT_MIN;
    int abs_val = abs(min_val);
    int neg_val = -min_val;

    printf("Rango de int (32 bits): [%d, %d]\n", INT_MIN, INT_MAX);
    printf("  Valor INT_MIN:      %d (Hex: 0x%08X)\n", min_val, min_val);
    printf("  abs(INT_MIN):       %d (Hex: 0x%08X) -> Asimetría de Rango\n", abs_val, abs_val);
    printf("  -INT_MIN:           %d (Hex: 0x%08X)\n", neg_val, neg_val);
    printf("Explicación: En 32 bits complemento a 2, no existe la representación de +2^31 (%u).\n", (unsigned int)INT_MAX + 1U);
    printf("El complemento a 1 de 0x80000000 es 0x7FFFFFFF, que al sumar 1 vuelve a ser 0x80000000.\n\n");
}

/**
 * Experimento IA6: Detección de Acarreo (Carry) en Enteros Sin Signo
 */
void exp_ia6_deteccion_acarreo_unsigned(void) {
    printf("======================================================================\n");
    printf("EXPERIMENTO IA6: Detección de Acarreo (Carry) en Software\n");
    printf("======================================================================\n");

    unsigned int a = UINT_MAX - 5U;
    unsigned int b = 10U;
    unsigned int suma = a + b;

    printf("Operando a:    %u (Hex: 0x%08X)\n", a, a);
    printf("Operando b:    %u (Hex: 0x%08X)\n", b, b);
    printf("Suma (a + b):  %u (Hex: 0x%08X)\n", suma, suma);

    bool carry_detectado = (suma < a);
    printf("Condición de Acarreo ((a + b) < a): %s\n", carry_detectado ? "VERDADERO -> OCURRIÓ CARRY" : "FALSO");
    if (carry_detectado) {
        printf("¡Demostrado! Se detectó el acarreo en software sin consultar registros de banderas de la CPU.\n\n");
    }
}

int main(void) {
    printf("======================================================================\n");
    printf("  ELECTRÓNICA DIGITAL (UCA) - TRABAJO PRÁCTICO 1\n");
    printf("  Resolución de Experimentos de IA (IA1 al IA6)\n");
    printf("======================================================================\n\n");

    exp_ia1_inexactitud_flotante();
    exp_ia2_comparaciones_mixtas();
    exp_ia3_division_entera_y_truncamiento();
    exp_ia4_multiplicacion_y_promocion();
    exp_ia5_asimetria_complemento_base();
    exp_ia6_deteccion_acarreo_unsigned();

    return 0;
}
