#ifndef UTILS_H
#define UTILS_H

typedef enum tipos{
    INTEIROS,
    FLOAT,
    STRING
} ColunaTipos;

typedef union coluna{
    ColunaTipos coluna_tipo;
    char *coluna_nome;

    int **celulas_int;
    float **celulas_float;
    char **celulas_string;
} Coluna;

typedef struct tabela{
    Coluna *colunas;
    char *tabela_nome;
} Tabela;

#endif