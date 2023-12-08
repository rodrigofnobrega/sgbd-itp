#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#define TITULO "TABELAS EXISTENTES"
#define DB_FILES_PATH "../database/"

void exibir_linhas(int tamformatacao_tabela) {
    printf("+");
    for (int i = 0; i < tamformatacao_tabela + 2; i++) {
        printf("-");
    }
    printf("+\n");
}

void organizar_tabelas(char **nomes_tabelas, int tam_formatacao_tabela, int qtd_tabelas) {
    int espacos_em_branco = (tam_formatacao_tabela - strlen(TITULO));

    exibir_linhas(tam_formatacao_tabela);

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

    exibir_linhas(tam_formatacao_tabela);

    // Mostrar as linhas com os nomes das tabelas
    for (int i = 0; i < qtd_tabelas; i++) {
        printf("| %-*s |\n", tam_formatacao_tabela, nomes_tabelas[i]);
    }

    exibir_linhas(tam_formatacao_tabela);
}

int mostrar_tabelas() {
    char **qtd_tabelas_existentes = NULL;
    char *nome_tabela;
    int tam_formatacao_tabela = strlen(TITULO);
    int qtd_tabelas = 0;
    struct dirent *de;

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

    organizar_tabelas(qtd_tabelas_existentes, tam_formatacao_tabela, qtd_tabelas);

    for (int i = 0; i < qtd_tabelas; i++) {
        free(qtd_tabelas_existentes[i]);
    }

    free(qtd_tabelas_existentes);
}
