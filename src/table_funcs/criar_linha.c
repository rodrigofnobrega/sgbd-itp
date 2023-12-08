#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../../includes/utils.h"

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
Dados definindo_dados(char *linha, int col_type, Dados col_dados){
    switch(col_type){
        case INT:
            sscanf(linha,"%d", &col_dados.inteiro);
            break;
        case FLOAT:
            sscanf(linha,"%f", &col_dados.flutuante);
            break;
        case DOUBLE:
            sscanf(linha,"%lf", &col_dados.real);
            break;
        case CHAR:
            sscanf(linha," %c", &col_dados.caracter);
            break;
        case STRING:
            col_dados.string = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
            sscanf(linha,"%s", col_dados.string);
            break;
    }
    return col_dados;
}

void criar_linha() {
    char banco_nome[STRING_MAX_SIZE];
    printf("Digite o nome do arquivo que desejas adicionar as linhas: ");
    fgets(banco_nome, STRING_MAX_SIZE, stdin);
    int string_length = strlen(banco_nome);
    if(banco_nome[string_length-1] == '\n'){
        banco_nome[string_length-1] = '\0';
    }
    char arquivo_nome[STRING_MAX_SIZE];
    sprintf(arquivo_nome, "../database/%s.txt", banco_nome);

    FILE *arquivo = fopen(arquivo_nome, "r");
    int tam_titulo = strlen("Coluna Nome");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
    }

    char linha[MAX_TAMANHO_LINHA];
    if (fgets(linha, MAX_TAMANHO_LINHA, arquivo) == NULL) {
        perror("Erro ao ler a primeira linha");
        fclose(arquivo);
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
    fclose(arquivo);
    FILE *arquivo_escrever = fopen(arquivo_nome, "a");

    int qtd_linhas;
    printf("\nDigite quantas linhas ira adicionar a cada coluna: ");
    scanf("%d", &qtd_linhas);
    getchar();
    Dados *col_dados = (Dados *)malloc(sizeof(Dados) * qtd_linhas * aux-1);
    for(int i = 0; i < qtd_linhas; i++){
        printf("Digite a %dª linha: ", i+1);
        fgets(linha, MAX_TAMANHO_LINHA, stdin);
        string_length = strlen(linha);
        if(linha[string_length-1] == '\n'){
            linha[string_length-1] = '\0';
        }
        fprintf(arquivo_escrever, "\n");
        char *token = strtok(linha, " ");
        while (token != NULL) {
            fprintf(arquivo_escrever, "%s;", token);
            token = strtok(NULL, " "); 
        }
        /*Dados new_col_dados = definindo_dados(linha, col_types[i], col_dados[i]);
        printf("[%d] [%s]\n", new_col_dados.inteiro, new_col_dados.string);
        free(new_col_dados.string);
        */
    }
    free(col_types);
    free(col_names);
    free(col_dados);
    fclose(arquivo_escrever);
}