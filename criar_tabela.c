#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define STRING_MAX_SIZE 100

typedef enum tipos {
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING
} ColunaTipos;

typedef struct coluna {
    ColunaTipos coluna_tipo;
    char *coluna_nome;

    int *celulas_int;
    float *celulas_float;
    char **celulas_string;
} Coluna;

typedef struct tabela {
    Coluna *colunas;
    char tabela_nome[STRING_MAX_SIZE];
} Tabela;

void definir_tipo(int enum_type, Tabela *banco_de_dados, int aux){
    switch(enum_type){
        case INT:
            banco_de_dados->colunas[aux].coluna_tipo = INT;
            break;
        case FLOAT:
            banco_de_dados->colunas[aux].coluna_tipo = FLOAT;
            break;
        case DOUBLE:
            banco_de_dados->colunas[aux].coluna_tipo = DOUBLE;
            break;
        case CHAR:
            banco_de_dados->colunas[aux].coluna_tipo = CHAR;
            break;
        case STRING:
            banco_de_dados->colunas[aux].coluna_tipo = STRING;
            break;
        default:
            printf("~Digite um valor válido\n");
    }
}

void salvar_arquivo(Tabela *banco_de_dados, int aux) {

    char nome[STRING_MAX_SIZE];
    sprintf(nome, "%s.txt", banco_de_dados->tabela_nome);

    FILE *arquivo;
    arquivo = fopen(nome, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return; 
    }
    for(int i = 0; i < aux; i++){
        fprintf(arquivo, "%d;", banco_de_dados->colunas[i].coluna_tipo);
    }
    fprintf(arquivo, "\n");
    for(int i = 0; i < aux; i++){
        fprintf(arquivo, "%s;", banco_de_dados->colunas[i].coluna_nome);
    }

    fclose(arquivo);
}

int main() {
    Tabela *banco_de_dados = (Tabela *)malloc(sizeof(Tabela));
    size_t str_length;
    
    printf("$Digite o nome do banco de dados: ");
    fgets(banco_de_dados->tabela_nome, STRING_MAX_SIZE, stdin);
    str_length = strlen(banco_de_dados->tabela_nome);
    if(banco_de_dados->tabela_nome[str_length-1] == '\n'){
        banco_de_dados->tabela_nome[str_length-1] = '\0';
    }
    
    int aux = 1;
    banco_de_dados->colunas = (Coluna *)malloc(sizeof(Coluna) * 2 * aux);
    
    
    char key_input[STRING_MAX_SIZE];
    printf("$Nome da coluna de chave primária: ");
    fgets(key_input, STRING_MAX_SIZE, stdin);
    str_length = strlen(key_input);
    if (key_input[str_length-1] == '\n') {
        key_input[str_length-1] = '\0';
    }
    banco_de_dados->colunas[aux - 1].coluna_tipo = INT;
    banco_de_dados->colunas[aux - 1].coluna_nome = (char *)malloc(sizeof(char) * (str_length + 1));
    strcpy(banco_de_dados->colunas[aux - 1].coluna_nome, key_input);

    do {
        printf("$Nome da %dº coluna(digite 'fim' para finalizar): ", aux);
        char input[STRING_MAX_SIZE];
        fgets(input, STRING_MAX_SIZE, stdin);

        str_length = strlen(input);
        if (input[str_length - 1] == '\n') {
            input[str_length - 1] = '\0';
        }

        if (strcmp(input, "fim") == 0) {
            break;
        }

        banco_de_dados->colunas[aux].coluna_nome = (char *)malloc(sizeof(char) * (str_length + 1));
        if (banco_de_dados->colunas[aux].coluna_nome == NULL) {
            fprintf(stderr, "Memory allocation for coluna_nome failed\n");
            exit(EXIT_FAILURE);
        }
        strcpy(banco_de_dados->colunas[aux].coluna_nome, input);

        char tipo_entrada[STRING_MAX_SIZE];
        printf("$Tipo da %dº coluna(INT, FLOAT, DOUBLE, CHAR, STR): ", aux);

        if (fgets(tipo_entrada, sizeof(tipo_entrada), stdin) == NULL) {
            fprintf(stderr, "Erro ao ler a entrada\n");
            exit(EXIT_FAILURE);
        }

        str_length = strlen(tipo_entrada);
        if (str_length > 0 && tipo_entrada[str_length - 1] == '\n') {
        tipo_entrada[str_length - 1] = '\0';
        }

        int enum_type = (strcmp(tipo_entrada, "INT") == 0) ? 0 :
                (strcmp(tipo_entrada, "FLOAT") == 0) ? 1 :
                (strcmp(tipo_entrada, "DOUBLE") == 0) ? 2 :
                (strcmp(tipo_entrada, "CHAR") == 0) ? 3 :
                (strcmp(tipo_entrada, "STR") == 0) ? 4 : -1;

        definir_tipo(enum_type, banco_de_dados, aux);  

        aux++;
        banco_de_dados->colunas = realloc(banco_de_dados->colunas, sizeof(Coluna) * (aux + 1));
        if (banco_de_dados->colunas == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
    } while (1);
    salvar_arquivo(banco_de_dados, aux);
    for (int i = 0; i < aux; i++) {
        free(banco_de_dados->colunas[i].coluna_nome);
        
    }
    
    free(banco_de_dados->colunas);
    free(banco_de_dados);
    return 0;
}
