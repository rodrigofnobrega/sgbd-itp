#ifndef CRIAR_LINHA_H
#define CRIAR_LINHA_H
#include "utils.h"

void mostrar_line(int *tam_colunas, int qtd_colunas);
void formatar_tabelas(char **nomes_colunas, int *tipos_colunas, int qtd_colunas);
Dados definindo_dados(char *linha, int col_type, Dados col_dados);
void criar_linha();

#endif