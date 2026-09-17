/**
 * @file tp1_obligatorios.c
 * @brief Implementación de los Puntos Obligatorios (1 al 5) - Trabajo Práctico 1
 * @course Electrónica Digital | Universidad Católica Argentina (UCA)
 * @std ISO C99
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdint.h>
#include <string.h>

/**
 * @brief Inspecciona byte a byte la representación real en memoria de una variable.
 * @param etiqueta Descripción legible de la variable.
 * @param ptr Puntero genérico a la zona de memoria.
 * @param tamano Tamaño en bytes de la variable.
 */
static void inspeccionar_memoria(const char *etiqueta, const void *ptr, size_t tamano) {
    const uint8_t *bytes = (const uint8_t *)ptr;
    printf("Variable '%s' (%zu byte/s):\n", etiqueta, tamano);

    // Muestra orden de bytes en memoria física (LSB a MSB en Little-Endian)
    printf("  Hexadecimal en memoria (LSB -> MSB): ");
    for (size_t i = 0; i < tamano; i++) {
        printf("0x%02X ", bytes[i]);
    }
    printf("\n  Representación binaria (MSB -> LSB): ");
    for (int i = (int)tamano - 1; i >= 0; i--) {
        for (int b = 7; b >= 0; b--) {
            printf("%d", (bytes[i] >> b) & 1);
        }
        printf(" ");
    }
    printf("\n\n");
}

/**
 * Punto 1: Representación Interna, Rangos y Memoria Real
 */
void punto_1_rangos_y_memoria(void) {
    printf("======================================================================\n");
    printf("PUNTO 1: Representación Interna, Rangos y Inspección de Memoria Real\n");
    printf("======================================================================\n");
    printf("char:           %zu byte(s) | Rango: [%d, %d]\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("unsigned char:  %zu byte(s) | Rango: [0, %u]\n", sizeof(unsigned char), UCHAR_MAX);
    printf("int:            %zu byte(s) | Rango: [%d, %d]\n", sizeof(int), INT_MIN, INT_MAX);
    printf("unsigned int:   %zu byte(s) | Rango: [0, %u]\n\n", sizeof(unsigned int), UINT_MAX);

    char c = -42;
    unsigned char uc = 200;
    int i = -12345678;
    unsigned int ui = 3000000000U;

    inspeccionar_memoria("char c = -42", &c, sizeof(c));
    inspeccionar_memoria("unsigned char uc = 200", &uc, sizeof(uc));
    inspeccionar_memoria("int i = -12345678", &i, sizeof(i));
    inspeccionar_memoria("unsigned int ui = 3000000000U", &ui, sizeof(ui));
}

/**
 * Punto 2: Representación Interna de Flotantes (Estándar IEEE 754 de 32 bits)
 */
void punto_2_flotantes_ieee754(void) {
    printf("======================================================================\n");
    printf("PUNTO 2: Representación Interna de Flotantes (Estándar IEEE 754)\n");
    printf("======================================================================\n");
    printf("Tamaño del float: %zu bytes (%zu bits)\n", sizeof(float), sizeof(float) * 8);
    printf("Mínimo positivo normalizado (FLT_MIN): %E\n", FLT_MIN);
    printf("Máximo representable (FLT_MAX):        %E\n", FLT_MAX);
    printf("Dígitos de precisión decimal (FLT_DIG): %d\n\n", FLT_DIG);

    float f = -12.375f; // -12.375_10 = -1100.011_2 = -1.100011_2 * 2^3
    uint32_t bits;
    memcpy(&bits, &f, sizeof(float));

    uint32_t signo = (bits >> 31) & 0x1;
    uint32_t exp_polarizado = (bits >> 23) & 0xFF;
    int exp_real = (int)exp_polarizado - 127;
    uint32_t mantisa = bits & 0x7FFFFF;

    printf("Analizando el valor float f = %f:\n", f);
    printf("  Patrón de bits completo (Hexadecimal): 0x%08X\n", bits);
    printf("  1. Bit de Signo (Bit 31):            %u (%s)\n", signo, signo ? "1 -> Negativo" : "0 -> Positivo");
    printf("  2. Exponente Polarizado (Bits 30-23): %u (0x%02X) -> Exponente Real E = %u - 127 = %d\n",
           exp_polarizado, exp_polarizado, exp_polarizado, exp_real);
    printf("  3. Mantisa/Fracción (Bits 22-0):     0x%06X\n", mantisa);
    printf("     Bits de mantisa en binario:       ");
    for (int b = 22; b >= 0; b--) {
        printf("%d", (mantisa >> b) & 1);
    }
    printf("\n  4. Reconstrucción teórica:           (-1)^%u * (1 + 0.5 + 0.03125) * 2^(%d) = %f\n\n",
           signo, exp_real, f);
}

/**
 * Punto 3: Mecanismo de Extensión de Signo (char a int)
 */
void punto_3_extension_de_signo(void) {
    printf("======================================================================\n");
    printf("PUNTO 3: Mecanismo de Extensión de Signo (char a int)\n");
    printf("======================================================================\n");

    char c_neg = -5; // En 8 bits complemento a 2: 0xFB (1111 1011)
    char c_pos = 5;  // En 8 bits: 0x05 (0000 0101)

    int i_neg = c_neg; // Extensión de signo a 32 bits: 0xFFFFFFFB
    int i_pos = c_pos; // Extensión con ceros a 32 bits: 0x00000005

    printf("Caso Negativo (c_neg = %d):\n", c_neg);
    printf("  char (8 bits):  Hex 0x%02X | Binario: ", (uint8_t)c_neg);
    for (int b = 7; b >= 0; b--) printf("%d", ((uint8_t)c_neg >> b) & 1);
    printf("\n  int (32 bits):   Hex 0x%08X | Decimal: %d | MSB propagado a 1\n", i_neg, i_neg);

    printf("\nCaso Positivo (c_pos = %d):\n", c_pos);
    printf("  char (8 bits):  Hex 0x%02X | Binario: ", (uint8_t)c_pos);
    for (int b = 7; b >= 0; b--) printf("%d", ((uint8_t)c_pos >> b) & 1);
    printf("\n  int (32 bits):   Hex 0x%08X | Decimal: %d | MSB propagado a 0\n\n", i_pos, i_pos);
}

/**
 * Punto 4: Comportamiento ante Desbordamiento (Overflow / Wrap-around)
 */
void punto_4_desbordamiento_overflow(void) {
    printf("======================================================================\n");
    printf("PUNTO 4: Comportamiento ante Desbordamiento (Wrap-around)\n");
    printf("======================================================================\n");

    unsigned int u_max = UINT_MAX;
    unsigned int u_overflow = u_max + 1U;
    printf("Entero Sin Signo (unsigned int):\n");
    printf("  Valor Máximo (UINT_MAX): %u (Hex: 0x%08X)\n", u_max, u_max);
    printf("  UINT_MAX + 1:           %u (Hex: 0x%08X) -> Wrap-around a 0\n\n", u_overflow, u_overflow);

    int i_max = INT_MAX;
    int i_overflow = i_max + 1;
    printf("Entero Con Signo (int en Complemento a 2):\n");
    printf("  Valor Máximo (INT_MAX):  %d (Hex: 0x%08X)\n", i_max, i_max);
    printf("  INT_MAX + 1:             %d (Hex: 0x%08X) -> Wrap-around a INT_MIN\n\n", i_overflow, i_overflow);
}

/**
 * Punto 5: Pérdida de Precisión en float (Cancelación y Alineación)
 */
void punto_5_perdida_precision_float(void) {
    printf("======================================================================\n");
    printf("PUNTO 5: Pérdida de Precisión por Alineación de Mantisas en float\n");
    printf("======================================================================\n");

    float grande = 10000000.0f; // 10^7 (Exponente 23 -> 2^23 = 8,388,608)
    float pequeno = 0.1f;
    float suma = grande + pequeno;

    printf("Operando Grande:  %.2f\n", grande);
    printf("Operando Pequeño: %.4f\n", pequeno);
    printf("Resultado Suma:   %.2f\n", suma);

    if (grande == suma) {
        printf("\n¡Demostrado! (grande + pequeño == grande).\n");
        printf("Explicación: Para realizar la suma, la FPU debe alinear los exponentes.\n");
        printf("Debido a que la diferencia de exponentes supera los 24 bits de mantisa,\n");
        printf("los bits del operando menor son desplazados completamente fuera de la ventana de precisión.\n\n");
    } else {
        printf("La suma modificó la variable grande.\n\n");
    }
}

int main(void) {
    printf("======================================================================\n");
    printf("  ELECTRÓNICA DIGITAL (UCA) - TRABAJO PRÁCTICO 1\n");
    printf("  Resolución de Puntos Obligatorios (1 al 5)\n");
    printf("======================================================================\n\n");

    punto_1_rangos_y_memoria();
    punto_2_flotantes_ieee754();
    punto_3_extension_de_signo();
    punto_4_desbordamiento_overflow();
    punto_5_perdida_precision_float();

    return 0;
}
