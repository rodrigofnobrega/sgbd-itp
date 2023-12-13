#ifndef LISTAR_DADOS_TABELA_H
#define LISTAR_DADOS_TABELA_H

void mostrar_linha(int *tam_colunas, int qtd_colunas);
int * formatar_tab(char **nomes_colunas, int *tipos_colunas, int qtd_colunas);
void formatar_dados(char **tupla, int *tam_colunas, int qtd_colunas);
int listar_dados();

#endif