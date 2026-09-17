# Makefile - Trabajo Práctico 1 | Electrónica Digital (UCA)

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lm

SRC_DIR = src
BIN_OBLIGATORIOS = tp1_obligatorios
BIN_EXPERIMENTOS = tp1_ia_experiments

.PHONY: all obligatorios experimentos run run-obligatorios run-experimentos clean help

all: obligatorios experimentos

obligatorios: $(SRC_DIR)/tp1_obligatorios.c
	$(CC) $(CFLAGS) $< -o $(BIN_OBLIGATORIOS)

experimentos: $(SRC_DIR)/tp1_ia_experiments.c
	$(CC) $(CFLAGS) $< -o $(BIN_EXPERIMENTOS) $(LDFLAGS)

run: run-obligatorios run-experimentos

run-obligatorios: obligatorios
	@echo "======================================================================"
	@echo "  Ejecutando Puntos Obligatorios (1 al 5)..."
	@echo "======================================================================"
	./$(BIN_OBLIGATORIOS)

run-experimentos: experimentos
	@echo "======================================================================"
	@echo "  Ejecutando Experimentos de IA (IA1 al IA6)..."
	@echo "======================================================================"
	./$(BIN_EXPERIMENTOS)

clean:
	rm -f $(BIN_OBLIGATORIOS) $(BIN_EXPERIMENTOS)

help:
	@echo "Comandos disponibles:"
	@echo "  make              : Compila todos los ejecutables"
	@echo "  make obligatorios : Compila únicamente el ejecutable de los Puntos Obligatorios"
	@echo "  make experimentos : Compila únicamente el ejecutable de los Experimentos de IA"
	@echo "  make run          : Compila y ejecuta la totalidad de las pruebas"
	@echo "  make run-obligatorios  : Ejecuta los Puntos Obligatorios"
	@echo "  make run-experimentos  : Ejecuta los Experimentos de IA"
	@echo "  make clean        : Elimina los archivos binarios compilados"
