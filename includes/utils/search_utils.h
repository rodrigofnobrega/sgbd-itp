#ifndef SEARCH_UTILS_H
#define SEARCH_UTILS_H
#include <stdio.h>
#include "../../includes/utils.h"

void pesquisa_int(Dados valor, FILE *arquivo, char buffer[], int index_coluna, int pesquisa_opt);
void pesquisa_float(Dados valor, FILE *arquivo, char buffer[], int index_coluna, int pesquisa_opt);
void pesquisa_double(Dados valor, FILE *arquivo, char buffer[], int index_coluna, int pesquisa_opt);
void pesquisa_char(Dados valor, FILE *arquivo, char buffer[], int index_coluna, int pesquisa_opt);
void pesquisa_string(Dados valor, FILE *arquivo, char buffer[], int index_coluna, int pesquisa_opt);

#endif