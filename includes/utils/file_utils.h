#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>
#include "../utils.h"

char *definir_caminho_tabela(const char *nome_tabela);

FILE *abrir_arquivo(const char *nome_tabela, char modo_abertura);

#endif // FILE_UTILS_H
