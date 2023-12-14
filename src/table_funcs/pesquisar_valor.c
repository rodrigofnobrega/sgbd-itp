#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../../includes/utils.h"
#include "../../includes/utils/file_utils.h"

pesquisa_options(){
    int pesquisa_opt;
    printf("1. Valores maior que o valor informado\n2. Valores maior ou igual que o valor informado\n3. Valores igual ao valor informado\n4. Valores menor que o valor informado\n5. Valores menor ou igual que o valor informado\n6. Valores próximo ao valor informado (se aplica apenas se a coluna for do tipo string)\n");
    printf("Digite o tipo de pesquisa: ");
    scanf("%d", &pesquisa_opt);
    getchar();
    return pesquisa_opt;
}

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
    int pesquisa_opt;
    switch(tipo_coluna){
        Dados valor;
        case INT:
            if(scanf("%d", &valor.inteiro) != 1){
                printf("Valor digitado não corresponde ao tipo da coluna. ");
                break;
            };
            pesquisa_opt = pesquisa_options();
            printf("Valores encontrados: ");
            while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
                int aux = 0;
                char *token = strtok(buffer, ";");
                while(token != NULL){
                    if(aux == index_coluna){
                        int comp;
                        sscanf(token, "%d", &comp);
                        switch(pesquisa_opt){
                            case 1:
                                if(valor.inteiro < comp){
                                    printf("[%d] ",comp);
                                }
                                break;
                            case 2:
                                if(valor.inteiro <= comp){
                                    printf("[%d] ", comp);
                                }
                                break;
                            case 3:
                                if(valor.inteiro == comp){
                                    printf("[%d] ", comp);
                                }
                                break;
                            case 4:
                                if(valor.inteiro > comp){
                                    printf("[%d] ", comp);
                                }
                                break;
                            case 5:
                                if(valor.inteiro >= comp){
                                    printf("[%d] ", comp);
                                }
                                break;
                            default:
                                printf("Opção incorreta. ");
                                break;
                        }
                    }
                    token = strtok(NULL, ";");
                    aux++;
                }
                free(token);
            };
            break;
        case FLOAT:
            if(scanf("%f", &valor.flutuante) != 1){
                printf("Valor digitado não corresponde ao tipo da coluna. ");
                break;
            };
            pesquisa_opt = pesquisa_options();
            printf("Valores encontrados: ");
            while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
                int aux = 0;
                char *token = strtok(buffer, ";");
                while(token != NULL){
                    if(aux == index_coluna){
                        float comp;
                        sscanf(token, "%f", &comp);
                        switch(pesquisa_opt){
                            case 1:
                                if(valor.flutuante < comp){
                                    printf("[%f] ",comp);
                                }
                                break;
                            case 2:
                                if(valor.flutuante <= comp){
                                    printf("[%f] ", comp);
                                }
                                break;
                            case 3:
                                if(valor.flutuante == comp){
                                    printf("[%f] ", comp);
                                }
                                break;
                            case 4:
                                if(valor.flutuante > comp){
                                    printf("[%f] ", comp);
                                }
                                break;
                            case 5:
                                if(valor.flutuante >= comp){
                                    printf("[%f] ", comp);
                                }
                                break;
                            default:
                                printf("Opção incorreta. ");
                                break;
                        }
                    }
                    token = strtok(NULL, ";");
                    aux++;
                }
                free(token);
            };
            break;
        case DOUBLE:
            if(scanf("%lf", &valor.real) != 1){
                printf("Valor digitado não corresponde ao tipo da coluna. ");
                break;
            };
            pesquisa_opt = pesquisa_options();
            printf("Valores encontrados: ");
            while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
                int aux = 0;
                char *token = strtok(buffer, ";");
                while(token != NULL){
                    if(aux == index_coluna){
                        double comp;
                        sscanf(token, "%lf", &comp);
                        switch(pesquisa_opt){
                            case 1:
                                if(valor.real < comp){
                                    printf("[%lf] ",comp);
                                }
                                break;
                            case 2:
                                if(valor.real <= comp){
                                    printf("[%lf] ", comp);
                                }
                                break;
                            case 3:
                                if(valor.real == comp){
                                    printf("[%lf] ", comp);
                                }
                                break;
                            case 4:
                                if(valor.real > comp){
                                    printf("[%lf] ", comp);
                                }
                                break;
                            case 5:
                                if(valor.real >= comp){
                                    printf("[%lf] ", comp);
                                }
                                break;
                            default:
                                printf("Opção incorreta. ");
                                break;
                        }
                    }
                    token = strtok(NULL, ";");
                    aux++;
                }
                free(token);
            };
            break;
        case CHAR:
            if(scanf("%c", &valor.caracter) != 1){
                printf("Valor digitado não corresponde ao tipo da coluna. ");
                break;
            };
            pesquisa_opt = pesquisa_options();
            printf("Valores encontrados: ");
            while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
                int aux = 0;
                char *token = strtok(buffer, ";");
                while(token != NULL){
                    if(aux == index_coluna){
                        char comp;
                        sscanf(token, "%c", &comp);
                        switch(pesquisa_opt){
                            case 1:
                                if(valor.caracter < comp){
                                    printf("[%c] ",comp);
                                }
                                break;
                            case 2:
                                if(valor.caracter <= comp){
                                    printf("[%c] ", comp);
                                }
                                break;
                            case 3:
                                if(valor.caracter == comp){
                                    printf("[%c] ", comp);
                                }
                                break;
                            case 4:
                                if(valor.caracter > comp){
                                    printf("[%c] ", comp);
                                }
                                break;
                            case 5:
                                if(valor.caracter >= comp){
                                    printf("[%c] ", comp);
                                }
                                break;
                            default:
                                printf("Opção incorreta. ");
                                break;
                        }
                    }
                    token = strtok(NULL, ";");
                    aux++;
                }
                free(token);
            };
            break;
        case STRING:
            valor.string = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
            if(scanf("%s", valor.string) != 1){
                printf("Valor digitado não corresponde ao tipo da coluna. ");
                break;
            };
            pesquisa_opt = pesquisa_options();
            printf("Valores encontrados: ");
            while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
                int aux = 0;
                char *token = strtok(buffer, ";");
                while(token != NULL){
                    if(aux == index_coluna){
                        char comp[STRING_MAX_SIZE];
                        sscanf(token, "%s", comp);
                        switch(pesquisa_opt){
                            case 1:
                                if(strcmp(valor.string, comp) < 0){
                                    printf("[%s] ", comp);
                                }
                                break;
                            case 2:
                                if(strcmp(valor.string, comp) < 0 || strcmp(valor.string, comp) == 0){
                                    printf("[%s] ", comp);
                                }
                                break;
                            case 3:
                                if(strcmp(valor.string, comp) == 0){
                                    printf("[%s] ", comp);
                                }
                                break;
                            case 4:
                                if(strcmp(valor.string, comp) > 0){
                                    printf("[%s] ", comp);
                                }
                                break;
                            case 5:
                                if(strcmp(valor.string, comp) > 0 || strcmp(valor.string, comp) == 0){
                                    printf("[%s] ", comp);
                                }
                                break;
                            case 6:
                                if((strlen(valor.string) - strlen(comp)) == 1){
                                    printf("[%s] ", comp);
                                }
                                break;
                            default:
                                printf("Opção incorreta. ");
                                break;
                        }
                    }
                    token = strtok(NULL, ";");
                    aux++;
                }
                free(token);
            };
            break;
        default:
            printf("\nErro de tipo. ");
            break;
    }
    printf("\n");
    fclose(arquivo);
    free(arquivo);
    for(int i = 0; i < sizeof(coluna_nomes); i++){
        free(coluna_nomes[i]);
    }
    free(coluna_nomes);
    free(coluna_tipos);
}