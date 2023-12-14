#ifndef CRIAR_TABELA_H
#define CRIAR_TABELA_H
#include "utils.h"

void definir_tipo_coluna(int enum_type, Tabela *banco_de_dados, int aux);
int salvar_coluna(Tabela *banco_de_dados, int colunas_qtd);
int criar_banco_de_dados();

#endif