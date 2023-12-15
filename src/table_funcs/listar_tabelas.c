/*
=========================================================================================================
Arquivo: listar_tabelas.c
Data modificação: 15 de dezembro de 2023
Descrição: Este código tem como finalidade listar e exibir de forma formatada as tabelas existentes no diretório do banco de dados.
           As tabelas são identificadas pelos arquivos de texto (.txt) presentes no diretório.
=========================================================================================================
*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../includes/utils.h"

// Define o título que será exibido no topo da tabela
#define TITULO "TABELAS EXISTENTES"

/*--------------------------------------------------------------------------------
Função: Exibe linhas verticais 
Parâmetros:
    - tam_formatacao_tabela: Tamanho máximo de formatação da tabela, servirá para printar a quantidade suficiente de traços.
*/
void exibir_linhas(int tam_formatacao_tabela) {
    printf("+");
    // Somando 2 em tam_formatacao_tabela para manter a formatação 
    // ao printar o + ao início e fim da linha
    for (int i = 0; i < tam_formatacao_tabela + 2; i++) {
        printf("-");
    }
    printf("+\n");
}

/*--------------------------------------------------------------------------------
Função: Organiza e exibe tabelas formatadas.
Parâmetros:
    - nomes_tabelas: Vetor contendo os nomes das tabelas a serem exibidas.
    - tam_formatacao_tabela: Tamanho máximo de formatação da tabela.
    - qtd_tabelas: Quantidade de tabelas a serem exibidas.
*/
void organizar_tabelas(char **nomes_tabelas, int tam_formatacao_tabela, int qtd_tabelas) {
    // Calcula a quantidade de espaços em branco para centralizar o texto
    int espacos_em_branco = (tam_formatacao_tabela - strlen(TITULO));

    // Exibe linhas horizontais para formatar a tabela
    exibir_linhas(tam_formatacao_tabela);

    // Exibe o título centralizado na tabela
    if (espacos_em_branco % 2 == 0) {
        espacos_em_branco /= 2;
        printf("| %*s%s%*s |\n", espacos_em_branco, "", TITULO, espacos_em_branco, "");
    } else {
        espacos_em_branco /= 2;
        printf("| %*s%s%*s |\n", espacos_em_branco, "", TITULO, espacos_em_branco+1, "");
    }

    // Exibe linhas horizontais após o título
    exibir_linhas(tam_formatacao_tabela);

    // Mostra as linhas com os nomes das tabelas
    for (int i = 0; i < qtd_tabelas; i++) {
        printf("| %-*s |\n", tam_formatacao_tabela, nomes_tabelas[i]);
    }

    // Exibe linhas horizontais no final da tabela
    exibir_linhas(tam_formatacao_tabela);
}

/*--------------------------------------------------------------------------------
Função: Mostra todas as tabelas
*/
void mostrar_tabelas() {
    char **nomes_tabelas_existentes = NULL;
    char *nome_tabela;
    int tam_formatacao_tabela = strlen(TITULO);
    int qtd_tabelas = 0;
    struct dirent *de;

    // Abre o diretório para leitura
    DIR *dr = opendir(DB_PATH);

    // Lê cada entrada no diretório
    while ((de = readdir(dr)) != NULL) {
        // Verifica se a entrada é um arquivo de texto
        if (strstr(de->d_name, ".txt") != NULL) {
            // Extrai o nome da tabela do nome do arquivo
            nome_tabela = strtok(de->d_name, ".");

            // Atualiza o tamanho máximo de formatação da tabela
            if (strlen(nome_tabela) > tam_formatacao_tabela) {
                tam_formatacao_tabela = strlen(nome_tabela);
            }

            // Realoca o vetor de ponteiros para acomodar mais uma string
            nomes_tabelas_existentes = (char **)realloc(nomes_tabelas_existentes, (qtd_tabelas + 1) * sizeof(char *));

            // Aloca memória para a string atual e a copia
            nomes_tabelas_existentes[qtd_tabelas] = (char *)malloc((strlen(nome_tabela) + 1) * sizeof(char));
            strcpy(nomes_tabelas_existentes[qtd_tabelas], nome_tabela);

            // Incrementa a contagem de tabelas
            qtd_tabelas++;
        }
    }

    closedir(dr);

    // Chama a função para organizar e exibir as tabelas
    organizar_tabelas(nomes_tabelas_existentes, tam_formatacao_tabela, qtd_tabelas);

    for (int i = 0; i < qtd_tabelas; i++) {
        free(nomes_tabelas_existentes[i]);
    }

    free(nomes_tabelas_existentes);
}
