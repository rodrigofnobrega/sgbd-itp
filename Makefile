CC = gcc
CFLAGS = -g -W -pedantic

all: run clean

run: main.o criar_tabela.o criar_linha.o listar_tabelas.o
	$(CC) $^ -o $@

criar_tabela.o: src/table_funcs/criar_tabela.c
	$(CC) $< -c -o $@ $(CFLAGS)

criar_linha.o: src/table_funcs/criar_linha.c
	$(CC) $< -c -o $@ $(CFLAGS)

listar_tabelas.o: src/table_funcs/listar_tabelas.c
	$(CC) $< -c -o $@ $(CFLAGS)

main.o: src/main.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	del *.o 
# Se linux mude "del" por "rm -f"
