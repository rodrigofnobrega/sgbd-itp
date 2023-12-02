#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../utils.h"

typedef union coluna{
    ColunaTipos coluna_tipo;
    char *coluna_nome;

    int *celulas_int;
    float *celulas_float;
    char **celulas_string;
} Coluna;

typedef struct tabela{
    Coluna *colunas;
    char *tabela_nome;
} Tabela;

void criar_Tabela(){
    Tabela tabela;
    int colunas_qtd;
    printf("Nome da Tabela: ");
    scanf("%s", tabela.tabela_nome);
    printf("Quantidade Colunas: ");
    scanf("%d", &colunas_qtd);

    tabela.colunas = (Coluna *)malloc(sizeof(Coluna) * colunas_qtd);

    for(int i = 0; i < colunas_qtd; i++){
        char pergunta[100];
        sprintf(pergunta,"%dº Coluna nome: ", i);
        scanf("%s", tabela.colunas[i].coluna_nome);
        printf("%s", tabela.colunas[i].coluna_nome);
    }

}