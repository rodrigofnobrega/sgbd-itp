#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../../includes/utils.h"
#include "../../includes/utils/file_utils.h"

int pesquisar_valor(){
    FILE *arquivo;
    char banco_nome[STRING_MAX_SIZE];

    printf("Digite o nome do arquivo: ");
    fgets(banco_nome, 100, stdin);

    int string_lenght = strlen(banco_nome);
    if(banco_nome[string_lenght-1] == '\n'){
        banco_nome[string_lenght-1] = '\0';
    }

    arquivo = abrir_arquivo(banco_nome, 'r');

    int tipo_coluna;
    int index_coluna;
    char nome_coluna[STRING_MAX_SIZE];

    printf("Digite o nome da coluna: ");
    scanf("%s", nome_coluna);
    getchar();

    char buffer[BUFFER_MAX_SIZE];
    fgets(buffer, BUFFER_MAX_SIZE, arquivo); 

    int aux = 1;
    int pos = 0;
    int *coluna_tipos = (int *)malloc(sizeof(int) * aux);
    while(sscanf(buffer + pos, "%d;", &coluna_tipos[aux-1]) == 1){
        pos += strcspn(buffer + pos, ";") + 1;
        aux++;
        coluna_tipos = realloc(coluna_tipos, sizeof(int) * 2 * aux);
    }
    
    fgets(buffer, BUFFER_MAX_SIZE, arquivo);

    pos = 0;
    aux = 1;
    char **coluna_nomes = (char **)malloc(sizeof(char *) * aux);
    coluna_nomes[aux-1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
    while (sscanf(buffer + pos, "%[^;\n];", coluna_nomes[aux-1]) == 1) {
        if(strcmp(nome_coluna, coluna_nomes[aux-1]) == 0){
            tipo_coluna = coluna_tipos[aux-1];
            index_coluna = aux-1;
        }
        pos += strcspn(buffer + pos, ";") + 1;
        aux++;
        coluna_nomes = realloc(coluna_nomes, sizeof(char *) * 2 * aux);
        coluna_nomes[aux-1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
    }   

    printf("Digite o valor que deseja pesquisar na coluna: ");
    switch(tipo_coluna){
        Dados valor;
        case INT:
            scanf("%d", &valor.inteiro);
            while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
                aux = 0;
                char *token = strtok(buffer, ";");
                while(token != NULL){
                    if(aux == index_coluna){
                        int comp;
                        sscanf(token, "%d", &comp);
                        if(valor.inteiro == comp){
                            printf("%d\n", valor.inteiro);
                        }
                    }
                    token = strtok(NULL, ";");
                    aux++;
                }
                free(token);
            };
            return 0;
        case FLOAT:
            scanf("%d", &valor.inteiro);
            while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
                aux = 0;
                char *token = strtok(buffer, ";");
                while(token != NULL){
                    if(aux == index_coluna){
                        int comp;
                        sscanf(token, "%d", &comp);
                        if(valor.inteiro == comp){
                            printf("%d\n", valor.inteiro);
                        }
                    }
                    token = strtok(NULL, ";");
                    aux++;
                }
                free(token);
            };
            return 0;
        case DOUBLE:
            scanf("%d", &valor.inteiro);
            while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
                aux = 0;
                char *token = strtok(buffer, ";");
                while(token != NULL){
                    if(aux == index_coluna){
                        int comp;
                        sscanf(token, "%d", &comp);
                        if(valor.inteiro == comp){
                            printf("%d\n", valor.inteiro);
                        }
                    }
                    token = strtok(NULL, ";");
                    aux++;
                }
                free(token);
            };
            return 0;
        case CHAR:
            scanf("%d", &valor.inteiro);
            while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
                aux = 0;
                char *token = strtok(buffer, ";");
                while(token != NULL){
                    if(aux == index_coluna){
                        int comp;
                        sscanf(token, "%d", &comp);
                        if(valor.inteiro == comp){
                            printf("%d\n", valor.inteiro);
                        }
                    }
                    token = strtok(NULL, ";");
                    aux++;
                }
                free(token);
            };
            return 0;
        case STRING:
            scanf("%s", valor.string);
            while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
                aux = 0;
                char *token = strtok(buffer, ";");
                while(token != NULL){
                    if(aux == index_coluna){
                        char comp[100];
                        sscanf(token, "%s", comp);
                        if(strcmp(valor.inteiro, comp) == 0){
                            printf("%s\n", valor.string);
                        }
                    }
                    token = strtok(NULL, ";");
                    aux++;
                }
                free(token);
            };
            return 0;
        default:
            printf("\nErro de tipo. ");
            return 0;
    }
    fclose(arquivo);
    free(arquivo);
    for(int i = 0; i < sizoef(coluna_nomes); i++){
        free(coluna_nomes[i]);
    }
    free(coluna_nomes);
    free(coluna_tipos);
}