#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAXIMO_STRING 50

int CriarLinhas(char ***linhas, int quantidade_coluna) {
    char aux_valor_linha[TAMANHO_MAXIMO_STRING];
    int quantidade_valores_por_linha = 0;
    int quantidade_linhas = 0;

    *linhas = (char **)malloc(sizeof(char *) * 1);

    printf("ADICIONE AS LINHAS: \n");

    for (int i = 0; ; i++) {
        scanf(" %s", aux_valor_linha);
        
        if (strcmp(aux_valor_linha, "fim") == 0) {
            break;
        }

        strcat(aux_valor_linha, ";");

        (*linhas)[i] = (char *)malloc(strlen(aux_valor_linha) * sizeof(char));

        strcpy((*linhas)[i], aux_valor_linha);

        // Substituindo caso exista \n no final da string por \0
        if ((*linhas)[i][strlen(aux_valor_linha) - 1] == '\n') {
            (*linhas)[i][strlen(aux_valor_linha) - 1] = '\0';
        }

        // A condição está verificando se a quantidade de elementos digitados é igual a quantidade de colunas
        // se for igual vai adicionar uma quebra de linha e pular para a próxima linha
        if ((i+1) % quantidade_coluna == 0) {
            (*linhas)[i] = (char *)realloc((*linhas)[i], (strlen((*linhas)[i]) + 2) * sizeof(char));
            strcat((*linhas)[i], "\n");
        
            quantidade_linhas++;
        }

        quantidade_valores_por_linha++;

        *linhas = (char **)realloc(*linhas, sizeof(char *) * (quantidade_valores_por_linha + 1));
    }

    return quantidade_linhas;
}

int CriarColunas(char ***nome_colunas) {
    char aux_nome_coluna[TAMANHO_MAXIMO_STRING]; // Variável auxiliar para pegar o tamanho de string e alocar a memória exata no vetor 'nome_colunas'
    int quantidade_colunas = 0;

    *nome_colunas = (char **)malloc(sizeof(char *) * 1);
    
    printf("ADICIONE AS COLUNAS: \n");

    for (int i = 0; ; i++) {
        scanf(" %s", aux_nome_coluna);

        if (strcmp(aux_nome_coluna, "fim") == 0) {
            if (i > 0) {
                // Alocar mais um byte de espaço para adicionar o \n à última coluna inserida 
                (*nome_colunas)[i - 1] = (char *)realloc((*nome_colunas)[i - 1], (strlen((*nome_colunas)[i - 1]) + 2) * sizeof(char));
                strcat((*nome_colunas)[i - 1], "\n");
            }

            break;
        }

        strcat(aux_nome_coluna, ";");

        (*nome_colunas)[i] = (char *)malloc(strlen(aux_nome_coluna) * sizeof(char));

        strcpy((*nome_colunas)[i], aux_nome_coluna);

        // Substituindo caso exista \n no final da string por \0
        if ((*nome_colunas)[i][strlen(aux_nome_coluna) - 1] == '\n') {
            (*nome_colunas)[i][strlen(aux_nome_coluna) - 1] = '\0';
        }

        quantidade_colunas++;

        // Alocando memória para o vetor conseguir adicionar mais uma coluna
        // Talvez seja melhor alocar a memória depois de saber que vai existir mais uma coluna?
        *nome_colunas = (char **)realloc(*nome_colunas, sizeof(char *) * (quantidade_colunas + 1));
    }

    return quantidade_colunas;
}

void criarTabela() {
    // nome_tabela ainda não foi usada mas será necessária no futuro
    char nome_tabela[50];
    // Vetor para armazenar todas as colunas informadas pelo usuário
    char **colunas;
    // Vetor que armazena o valor de cada coluna, talvez seja melhor renomea-la
    char **linhas;

    int quantidade_colunas = 3;
    int quantidade_linhas = 3;
    
    // O nome do arquivo hard-coded pode ser substituida
    // pela concatenação da variável 'nome_tabela' + .txt
    FILE *arquivo = fopen("tabela.txt", "w");

    quantidade_colunas = CriarColunas(&colunas);

    // Salvando no arquivo as colunas
    for (int i = 0; colunas[i] != NULL; i++)
    {
        fprintf(arquivo, "%s", colunas[i]);
    }

    quantidade_linhas = CriarLinhas(&linhas, quantidade_colunas);

    // Salvando no arquivo o valor das colunas
    for (int i = 0; linhas[i] != NULL; i++)
    {
        fprintf(arquivo, "%s", linhas[i]); 
    }
}


