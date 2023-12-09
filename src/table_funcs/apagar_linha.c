#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/utils.h"
#include "../../includes/utils/string_utils.h"
#include "../../includes/utils/file_utils.h"
#include "../../includes/apagar_linha.h"

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
