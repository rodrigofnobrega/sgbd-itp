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

$(TARGET_DIR)/sgbd.$(EXTENSION): main.o string_utils.o criar_tabela.o criar_linha.o listar_tabelas.o apagar_tabela.o apagar_linha.o file_utils.o| $(TARGET_DIR)
	$(CC) $^ -o $@

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

string_utils.o: src/utils/string_utils.c 
	$(CC) $< -c -o $@ $(CFLAGS)

file_utils.o: src/utils/file_utils.c 
	$(CC) $< -c -o $@ $(CFLAGS)

criar_tabela.o: src/table_funcs/criar_tabela.c
	$(CC) $< -c -o $@ $(CFLAGS)

criar_linha.o: src/table_funcs/criar_linha.c
	$(CC) $< -c -o $@ $(CFLAGS)

listar_tabelas.o: src/table_funcs/listar_tabelas.c
	$(CC) $< -c -o $@ $(CFLAGS)

apagar_tabela.o: src/table_funcs/apagar_tabela.c
	$(CC) $< -c -o $@ $(CFLAGS)

apagar_linha.o: src/table_funcs/apagar_linha.c
	$(CC) $< -c -o $@ $(CFLAGS)

main.o: src/main.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	$(RM) *.o
    
.PHONY: clean
