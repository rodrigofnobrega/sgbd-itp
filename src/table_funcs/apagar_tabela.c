#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../../includes/apagar_tabela.h"
#include "../../includes/utils/file_utils.h"
#include "../../includes/utils.h"

int apagar_tabela(char *nome_tabela) {
    DIR *dir;
    struct dirent *entrada;
    int tabela_existe = 0; // "Bool" que indica se uma tabala existe

    dir = opendir(DB_PATH);
    if (dir == NULL) {
        perror("Erro ao abrir o diretório.");
        return -1;
    }

    char *path_tabela = definir_caminho_tabela(nome_tabela); // Montando o caminho para a tabela
    // Concatenando .txt para verificar se o arquivo da tabela existe no diretório
    strcat(nome_tabela, ".txt"); 

    // O loop irá percorrer todos os arquivos do diretório,
    // se a tabela existir será chamado a função remove para excluir o arquivo da tabela
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
