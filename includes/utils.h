#ifndef UTILS_H
#define UTILS_H

#define STRING_MAX_SIZE 100
#define MAX_TAMANHO_LINHA 100
#define DB_PATH "../database/"

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

typedef union coluna_dados{
    int inteiro;
    float flutuante;
    double real;
    char caracter;
    char *string;
} Dados;

#endif