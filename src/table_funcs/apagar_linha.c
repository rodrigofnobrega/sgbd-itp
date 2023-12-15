#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/utils.h"
#include "../../includes/utils/string_utils.h"
#include "../../includes/utils/file_utils.h"
#include "../../includes/apagar_linha.h"

int remover_linha(const char *nome_tabela, const char *chave_primaria) {
    char linha[BUFFER_MAX_SIZE];
    int linha_apagada = 0; // "Bool" que indica se uma linha foi apagada ou não
    FILE *arquivo_leitura;
    FILE *arquivo_escrita;

    // Abrindo tabela original como leitura e a tabela auxiliar como escrita
    arquivo_leitura = abrir_arquivo(nome_tabela, 'r');
    arquivo_escrita = abrir_arquivo("temp", 'w');

    // Loop 'for' que irá procurar pela chave primária informada pelo usuário,
    // se encontrar a chave primária o programa vai pular essa execução do loop
    // e não escreverá essa linha no arquivo auxiliar
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

    // Definindo os caminhos para a tabela original e a tabela auxiliar
    char *caminho_tabela_orig = definir_caminho_tabela(nome_tabela);
    char *caminho_tabela_temp = definir_caminho_tabela("temp"); 

    // Removendo a tabela original e renomeando a tabela auxiliar para o nome da tabela original
    remove(caminho_tabela_orig);
    rename(caminho_tabela_temp, caminho_tabela_orig);

    free(caminho_tabela_orig);
    free(caminho_tabela_temp);

    // Retorna 1 se a linha foi apagada e retorna 2 se a linha não foi apagada
    return linha_apagada;
}
