#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "../include/mostrar_tabela.h"

void mostrar_linhas(int tamformatacao_tabela) {
    printf("+");
    for (int i = 0; i < tamformatacao_tabela + 2; i++) {
        printf("-");
    }
    printf("+\n");
}

void formatar_tabelas(char **nomes_tabelas, int tam_formatacao_tabela, int qtd_tabelas) {
    const char *titulo = "TABELAS EXISTENTES";
    int espacos_em_branco = (tam_formatacao_tabela - strlen(TITULO));

    mostrar_linhas(tam_formatacao_tabela);

    // Calcular a quantidade de espaços em branco para centralizar o texto
    // e mostrar linhas com o texto centralizado
    // se o tamanho de espacos_em_branco for ímpar é preciso adicionar 
    // mais um de espaco no final para manter a formatação
    if (espacos_em_branco % 2 == 0) {
        espacos_em_branco /= 2;
        printf("| %*s%s%*s |\n", espacos_em_branco, "", TITULO, espacos_em_branco, "");
    } else {
        espacos_em_branco /= 2;
        printf("| %*s%s%*s |\n", espacos_em_branco, "", TITULO, espacos_em_branco+1, "");
    }

    mostrar_linhas(tam_formatacao_tabela);

    // Mostrar as linhas com os nomes das tabelas
    for (int i = 0; i < qtd_tabelas; i++) {
        printf("| %-*s |\n", tam_formatacao_tabela, nomes_tabelas[i]);
    }

    mostrar_linhas(tam_formatacao_tabela);
}

int mostrar_tabela() {
    char **qtd_tabelas_existentes = NULL;
    char *nome_tabela;
    int tam_formatacao_tabela = strlen(TITULO);
    int qtd_tabelas = 0;
    struct dirent *de;

    //printf("%s\n", DB_FILES_PATH);
    DIR *dr = opendir(DB_FILES_PATH);
    
    while ((de = readdir(dr)) != NULL) {
        if (strstr(de->d_name, ".txt") != NULL) {
            nome_tabela = strtok(de->d_name, ".");

            if (strlen(nome_tabela) > tam_formatacao_tabela) {
                tam_formatacao_tabela = strlen(nome_tabela);
            }

            // Realoca o vetor de ponteiros para acomodar mais uma string
            qtd_tabelas_existentes = (char **)realloc(qtd_tabelas_existentes, (qtd_tabelas + 1) * sizeof(char *));

            // Aloca memória para a string atual
            qtd_tabelas_existentes[qtd_tabelas] = (char *)malloc((strlen(nome_tabela) + 1) * sizeof(char));

            strcpy(qtd_tabelas_existentes[qtd_tabelas], nome_tabela);

            qtd_tabelas++;
        }
    }

    formatar_tabelas(qtd_tabelas_existentes, tam_formatacao_tabela, qtd_tabelas);

    for (int i = 0; i < qtd_tabelas; i++) {
        free(qtd_tabelas_existentes[i]);
    }

    free(qtd_tabelas_existentes);
}
