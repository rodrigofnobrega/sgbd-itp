#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/utils/string_utils.h"
#include "../../includes/utils.h"
#include "../../includes/apagar_linha.h"

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
    default:
        free(caminho_tabela);
        return NULL;
    }

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        free(caminho_tabela);
        return NULL;
    }

    free(caminho_tabela);
    return arquivo;
}

int remover_linha(const char *nome_tabela, const char *chave_primaria) {
    char linha[MAX_TAMANHO_LINHA];
    int linha_apagada = 0;
    FILE *arquivo_leitura;
    FILE *arquivo_escrita;

    arquivo_leitura = abrir_arquivo(nome_tabela, 'r');
    arquivo_escrita = abrir_arquivo("temp", 'w');

    for (int i = 0; fgets(linha, sizeof(linha), arquivo_leitura) != NULL; i++) {
        char valor_coluna[STRING_MAX_SIZE];

        if (sscanf(linha, "%[^;]", valor_coluna) == 1) {
            if (i > 1 && strcmp(chave_primaria, valor_coluna) == 0) {
                linha_apagada = 1;
                continue;
            } else {
                fprintf(arquivo_escrita, "%s", linha);
            }
        } else {
            printf("Erro ao ler a coluna\n");
        }
    }

    fclose(arquivo_leitura);
    fclose(arquivo_escrita);

    char *caminho_tabela_orig = definir_caminho_tabela(nome_tabela);
    char *caminho_tabela_temp = definir_caminho_tabela("temp");

    remove(caminho_tabela_orig);
    rename(caminho_tabela_temp, caminho_tabela_orig);

    free(caminho_tabela_orig);
    free(caminho_tabela_temp);

    return linha_apagada;
}
