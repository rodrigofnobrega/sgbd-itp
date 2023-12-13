#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define STRING_MAX_SIZE 100
#define MAX_TAMANHO_buffer 100
#define TITULO "DADOS DA TABELA"

typedef enum tipos {
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING
} ColunaTipos;

void mostrar_linhas(int *tam_colunas, int qtd_colunas) {
    printf("+");
    for (int i = 0; i < qtd_colunas; i++) {
        for (int j = 0; j < tam_colunas[i] + 2; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}

int * formatar_tabelas(char **nomes_colunas, int *tipos_colunas, int qtd_colunas) {
    int *tam_colunas = (int *)malloc(sizeof(int) * qtd_colunas);
    for (int i = 0; i < qtd_colunas; i++) {
        tam_colunas[i] = strlen(nomes_colunas[i])+9;
    }

    mostrar_linhas(tam_colunas, qtd_colunas);
    printf("|");
    for (int i = 0; i < qtd_colunas; i++) {
        switch (tipos_colunas[i]) {
            case INT:
                sprintf(nomes_colunas[i], "%s(INT)", nomes_colunas[i]);
                printf(" %-*s |", tam_colunas[i], nomes_colunas[i]); 
                break;
            case FLOAT:
                sprintf(nomes_colunas[i], "%s(FLOAT)", nomes_colunas[i]);
                printf(" %-*s |", tam_colunas[i], nomes_colunas[i]); 
                break;
            case DOUBLE:
                sprintf(nomes_colunas[i], "%s(DOUBLE)", nomes_colunas[i]); 
                printf(" %-*s |", tam_colunas[i], nomes_colunas[i]);
                break;
            case CHAR:
                sprintf(nomes_colunas[i], "%s(CHAR)", nomes_colunas[i]); 
                printf(" %-*s |", tam_colunas[i], nomes_colunas[i]);
                break;
            case STRING:
                sprintf(nomes_colunas[i], "%s(STRING)", nomes_colunas[i]); 
                printf(" %-*s |", tam_colunas[i], nomes_colunas[i]);
                break;
            default:
                break;
        }
    }
    printf("\n");
    mostrar_linhas(tam_colunas, qtd_colunas);
    return tam_colunas;
}
void formatar_dados(char **tupla, int *tam_colunas, int qtd_colunas){
    printf("|");
    for (int j = 0; j < qtd_colunas; j++) {
        printf(" %-*s |", tam_colunas[j], tupla[j]);
    }
    printf("\n");
    mostrar_linhas(tam_colunas, qtd_colunas);
}

int main(){
    FILE *arquivo;
    arquivo = fopen("../Teste.txt", "r");
    
    if(arquivo == NULL){
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    char buffer[100];
    fgets(buffer, sizeof(buffer), arquivo);

    int pos = 0;
    int aux = 1;
    int *coluna_tipos = (int *)malloc(sizeof(int) * aux);
    while(sscanf(buffer+pos, "%d;", &coluna_tipos[aux-1]) == 1){
        pos += strcspn(buffer + pos, ";") + 1;
        aux++;
        coluna_tipos = realloc(coluna_tipos, sizeof(int) * aux * 2);
    }

    fgets(buffer, sizeof(buffer), arquivo);

    pos = 0;
    aux = 1;
    char **coluna_nomes = (char **)malloc(sizeof(char *) * aux);
    coluna_nomes[aux-1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
    while(sscanf(buffer + pos, "%[^;\n];", coluna_nomes[aux-1]) == 1){
        pos += strcspn(buffer + pos, ";") + 1;
        aux ++;
        coluna_nomes = realloc(coluna_nomes, sizeof(char *) * 2 * aux);
        coluna_nomes[aux-1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
    }

    int qtd_colunas = aux-1;
    int *coluna_tam = formatar_tabelas(coluna_nomes, coluna_tipos, qtd_colunas);

    while(fgets(buffer, sizeof(buffer), arquivo) != NULL){
        pos = 0;
        aux = 1;
        char **tupla = (char **)malloc(sizeof(char *) * aux);
        tupla[aux-1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
        while(sscanf(buffer + pos, "%[^;\n];", tupla[aux-1]) == 1){
            pos += strcspn(buffer + pos, ";") + 1;
            aux++;
            tupla = realloc(tupla, sizeof(char *) * aux * 2);
            tupla[aux-1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
        }
        formatar_dados(tupla, coluna_tam, qtd_colunas);
        free(tupla);
        for(int i = 0; i < qtd_colunas; i++){
            free(tupla[i]);
        }
    }   
    free(coluna_nomes);
    free(coluna_tam);
    free(coluna_tipos);
    fclose(arquivo);
    return 0;
}