#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/utils/file_utils.h"
#include "../../includes/utils.h"

char *definir_caminho_tabela(const char *nome_tabela) {
    char *caminho_tabela = malloc(strlen(DB_PATH) + strlen(nome_tabela) + 5);

    if (caminho_tabela == NULL) {
        perror("Erro ao alocar memória para caminho_tabela\n");
        exit(EXIT_FAILURE);
    }

    sprintf(caminho_tabela, "%s%s.txt", DB_PATH, nome_tabela);

    return caminho_tabela;
}

FILE *abrir_arquivo(const char *nome_tabela, char modo_abertura) {
    FILE *arquivo;

    char *caminho_tabela = definir_caminho_tabela(nome_tabela);

    switch (modo_abertura) {
        case 'r':
            arquivo = fopen(caminho_tabela, "r");
            break;
        case 'w':
            arquivo = fopen(caminho_tabela, "w");
            break;
        case 'a':
            arquivo = fopen(caminho_tabela, "a");
            break;
        default:
            fprintf(stderr, "Modo de abertura inválido: %c\n", modo_abertura);
            arquivo =  NULL;
    }

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        free(caminho_tabela);
        return NULL;
    }

    free(caminho_tabela);

    return arquivo;
}