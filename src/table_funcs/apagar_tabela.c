#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "../../includes/apagar_tabela.h"
#include "../../includes/utils.h"

#define DB_FILES_PATH "database/"

int apagar_tabela() {
    DIR *dir;
    struct dirent *entrada;
    int tabela_existe = 0;
    char nome_tabela[STRING_MAX_SIZE];
    char path_tabela[STRING_MAX_SIZE];

    dir = opendir(DB_FILES_PATH);
    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return -1;
    }

    printf("Informe o nome da tabela: ");
    scanf(" %[^\n]", nome_tabela);
    getchar(); 
    strcat(nome_tabela, ".txt");
    sprintf(path_tabela, "database/%s", nome_tabela);

    while ((entrada = readdir(dir)) != NULL) {
        if (strcmp(entrada->d_name, nome_tabela) == 0) {
            if (remove(path_tabela) == 0) {
                printf("Tabela apagada com sucesso.\n", path_tabela);
                tabela_existe = 1;
            } else {
                perror("Erro ao remover tabela");
            }
        }
    }

    closedir(dir);
    
    return tabela_existe; 
}
