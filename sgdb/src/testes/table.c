#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef enum{
    INTEIRO,
    FLOAT,
    STRING
} DadosTipo; 

typedef union{
        char *coluna_nome;
        int *chaves_primarias;

        int *celulas_int;
        float *celulas_float;
        char **celulas_string;
} Coluna;

typedef struct tabela{
    char *tabela_nome;
    DadosTipo tipo; 
    Coluna *colunas;   
} Tabela;


int main(){
    Tabela tabela;
    tabela.tabela_nome = "Database";
    tabela.colunas = (Coluna *)malloc(sizeof(Coluna) * 5);
    tabela.tipo = 0;
    for(int i = 0; i < 5; i++){
        tabela.colunas[i].coluna_nome = "Coluna";
        switch (tabela.tipo)
        {
        case INTEIRO:
            tabela.colunas[i].celulas_int = (int *)malloc(sizeof(int) * 10);
            for(int j = 0; j < 10; j++){
                tabela.colunas[i].celulas_int[j] = 1;
            }
            break;
        default:
            break;
        }
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 10; j++){
            printf("%d", tabela.colunas[i].celulas_int[j]);
        }

    }
    /*
    FILE *tabela_arquivo = fopen("tabela.txt", "w");
    if(tabela_arquivo == NULL){
        printf("Erro: %s", strerror(errno));
    }


    fclose(tabela_arquivo);
    */

    return 0;
}
