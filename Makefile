CC = gcc
CFLAGS = -g -W -pedantic
TARGET_DIR = bin

# Comando de exclusão baseado no sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXTENSION = exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        RM = rm -rf
        EXTENSION = bin
    endif
    ifeq ($(UNAME_S),Darwin)
        RM = rm -rf
        EXTENSION = bin
    endif
endif

all: $(TARGET_DIR)/sgbd.$(EXTENSION) clean

$(TARGET_DIR)/sgbd.$(EXTENSION): main.o criar_tabela.o criar_linha.o listar_tabelas.o | $(TARGET_DIR)
	$(CC) $^ -o $@

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

criar_tabela.o: src/table_funcs/criar_tabela.c
	$(CC) $< -c -o $@ $(CFLAGS)

criar_linha.o: src/table_funcs/criar_linha.c
	$(CC) $< -c -o $@ $(CFLAGS)

listar_tabelas.o: src/table_funcs/listar_tabelas.c
	$(CC) $< -c -o $@ $(CFLAGS)

main.o: src/main.c
	$(CC) $< -c -o $@ $(CFLAGS)

.PHONY: clean
clean:
	$(RM) *.o
