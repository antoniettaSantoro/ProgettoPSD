CC = gcc
#Imposta gcc come compilatore

CFLAGS = -Wall -std=c99 -Iinclude
#Attiva i warning, usa C99 e cerca gli header in include/

# .c files, necessari per la compilazione
COMMON_SRCS = src/item.c src/data.c src/hashmap.c src/priorityQueue.c src/gestione.c src/utils.c

# --- Programma Principale ---
MAIN_SRCS = src/main.c
TARGET = segnalazioni

# --- Programma di Testing ---
TEST_SRCS = tests/main_test.c
TEST_TARGET = run_tests

# Compila entrambi i programmi
all: $(TARGET) $(TEST_TARGET)

# Compilazione del programma segnalazioni
$(TARGET): $(COMMON_SRCS) $(MAIN_SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(COMMON_SRCS) $(MAIN_SRCS)

# Compilazione del programma di testing
$(TEST_TARGET): $(COMMON_SRCS) $(TEST_SRCS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(COMMON_SRCS) $(TEST_SRCS)