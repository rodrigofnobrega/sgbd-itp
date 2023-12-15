#include <stdio.h>
#include <string.h>
#include "../../includes/utils.h"

void leitura_arquivo(FILE *arquivo, char buffer[], int index_coluna){
    while(fgets(buffer, BUFFER_MAX_SIZE, arquivo) != NULL){
        int aux = 0;
        char *token = strtok(buffer, ";");
        while(token != NULL){
            if(aux == index_coluna){

            }
            token = strtok(NULL, ";");
            aux++;
        }
        free(token);
    }
}

void pesquisa_int(Dados valor, char *token, int index_coluna, int pesquisa_opt){
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
void pesquisa_float(Dados valor, FILE *arquivo, char buffer[], int index_coluna, int pesquisa_opt){
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
}
void pesquisa_double(Dados valor, FILE *arquivo, char buffer[], int index_coluna, int pesquisa_opt){
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
}
void pesquisa_char(Dados valor, FILE *arquivo, char buffer[], int index_coluna, int pesquisa_opt){
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
}
void pesquisa_string(Dados valor, FILE *arquivo, char buffer[], int index_coluna, int pesquisa_opt){
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
}