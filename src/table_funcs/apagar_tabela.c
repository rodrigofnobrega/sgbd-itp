/*
=========================================================================================================
Arquivo: apagar_tabela.c
Data: 15 de dezembro de 2023
Descrição: O objetivo deste código é excluir uma tabela previamente criada pelo usuário.
           Requer apenas o nome da tabela a ser excluída.
=========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../../includes/apagar_tabela.h"
#include "../../includes/utils/file_utils.h"
#include "../../includes/utils.h"

/*--------------------------------------------------------------------------------
Função: apaga os dados de uma tabela existente no diretório do banco de dados.
Parâmetros:
    - Nome da tabela a ser excluída.
Retorno:
    - Retorna 1 se a tabela foi excluída com sucesso, 0 se a tabela não existe, -1 em caso de erro.
*/
int apagar_tabela(char *nome_tabela) {
    DIR *dir;
    struct dirent *entrada;
    int tabela_existe = 0; // Indicador booleano para verificar se uma tabela existe

    dir = opendir(DB_PATH);
    if (dir == NULL) {
        perror("Erro ao abrir o diretório.");
        return -1;
    }

    char *path_tabela = definir_caminho_tabela(nome_tabela); // Montando o caminho para a tabela
    // Adicionando a extensão .txt para verificar se o arquivo da tabela existe no diretório
    strcat(nome_tabela, ".txt"); 

    // O loop percorre todos os arquivos do diretório,
    // se a tabela existir, a função remove é chamada para excluir o arquivo da tabela
    while ((entrada = readdir(dir)) != NULL) {
        if (strcmp(entrada->d_name, nome_tabela) == 0) {
            if (remove(path_tabela) == 0) {
                tabela_existe = 1;
            } else {
                perror("Erro ao remover tabela");
            }
        }
    }

    closedir(dir);

    free(path_tabela);
    
    return tabela_existe; 
}
