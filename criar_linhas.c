#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define STRING_MAX_SIZE 100
#define MAX_TAMANHO_LINHA 100

typedef enum tipos {
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING
} ColunaTipos;

typedef struct coluna {
    ColunaTipos coluna_tipo;
    char *coluna_nome;

    int *celulas_int;
    float *celulas_float;
    char **celulas_string;
} Coluna;

typedef struct tabela {
    Coluna *colunas;
    char tabela_nome[STRING_MAX_SIZE];
} Tabela;

typedef union coluna_dados{
    int inteiro;
    float flutuante;
    double real;
    char caracter;
    char *string;
} Dados;

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

void formatar_tabelas(char **nomes_colunas, int *tipos_colunas, int qtd_colunas) {
    int tam_colunas[qtd_colunas];
    for (int i = 0; i < qtd_colunas; i++) {
        tam_colunas[i] = strlen(nomes_colunas[i]);
    }
    for (int i = 0; i < qtd_colunas; i++) {
        for (int j = 0; j < 4; j++) {
            switch (tipos_colunas[i]) {
                case 0: 
                case 1: 
                case 2: 
                case 3: 
                    tam_colunas[i] = tam_colunas[i] > 1 ? tam_colunas[i] : 1;
                    break;
                case 4: 
                    tam_colunas[i] = tam_colunas[i] > 4 ? tam_colunas[i] : 4;
                    break;
                default:
                    break;
            }
        }
    }
    mostrar_linhas(tam_colunas, qtd_colunas);
    printf("|");

    for (int i = 0; i < qtd_colunas; i++) {
        printf(" %-*s |", tam_colunas[i], nomes_colunas[i]);
    }
    printf("\n");

    mostrar_linhas(tam_colunas, qtd_colunas);

    for (int i = 0; i < 4; i++) {
        printf("|");
        for (int j = 0; j < qtd_colunas; j++) {
            switch (tipos_colunas[j]) {
                case 0: 
                    printf(" %*s |", tam_colunas[j], "");
                    break;
                case 1: 
                    printf(" %*s |", tam_colunas[j], "");
                    break;
                case 2: 
                    printf(" %*s |", tam_colunas[j], "");
                    break;
                case 3:
                    printf(" %*s |", tam_colunas[j], "");
                    break;
                case 4: 
                    printf(" %-*s |", tam_colunas[j], "");
                    break;
                default:
                    printf(" Tipo não reconhecido |");
                    break;
            }
        }
        printf("\n");
    }

    mostrar_linhas(tam_colunas, qtd_colunas);
}

int main() {
    char banco_nome[STRING_MAX_SIZE];
    printf("Digite o nome do arquivo que desejas adicionar as linhas: ");
    fgets(banco_nome, STRING_MAX_SIZE, stdin);
    int string_length = strlen(banco_nome);
    if(banco_nome[string_length-1] == '\n'){
        banco_nome[string_length-1] = '\0';
    }
    strcat(banco_nome, ".txt");
    FILE *arquivo = fopen(banco_nome, "r");
    int tam_titulo = strlen("Coluna Nome");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char linha[MAX_TAMANHO_LINHA];
    if (fgets(linha, MAX_TAMANHO_LINHA, arquivo) == NULL) {
        perror("Erro ao ler a primeira linha");
        fclose(arquivo);
        return 1;
    }

    int pos = 0;
    int aux = 1;
    int *col_types = (int *)malloc(sizeof(int) * aux);

    while (sscanf(linha + pos, "%d;", &col_types[aux-1]) == 1) {
        if(sizeof(col_types[aux-1]/4) > tam_titulo){
            tam_titulo = col_types[aux-1];
        }
        pos += strcspn(linha + pos, ";") + 1;
        aux++;
        col_types = realloc(col_types, sizeof(int) * aux * 2);
    }

    if (fgets(linha, MAX_TAMANHO_LINHA, arquivo) == NULL) {
        perror("Erro ao ler a segunda linha");
        fclose(arquivo);
        return 1;
    }

    pos = 0;
    aux = 1;
    char **col_names = (char **)malloc(sizeof(char *) * aux);
    col_names[aux-1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);

    while (sscanf(linha + pos, "%[^;\n];", col_names[aux-1]) == 1) {
        if(strlen(col_names[aux-1]) > tam_titulo){
            tam_titulo = strlen(col_names[aux-1]);
        }
        pos += strcspn(linha + pos, ";") + 1;
        aux++;
        col_names = realloc(col_names, sizeof(char *) * 2 * aux);
        col_names[aux-1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
    }
    formatar_tabelas(col_names, col_types, aux-1);


    Dados *coluna_dados = (Dados *)malloc(sizeof(Dados) * aux);
    free(col_types);
    free(col_names);
    free(coluna_dados);
    fclose(arquivo);
    return 0;
}