#ifndef UTILS_H
#define UTILS_H
#define STRING_MAX_SIZE 100
#define BUFFER_MAX_SIZE 100
#define DB_PATH "../database/"

//Esse associara os inteiros 0, 1, 2, 3, 4 aos respectivos tipos descritos dentro das chaves
//com isso definirémos os tipos de dados trabalhados no banco de dados
typedef enum tipos {
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING
} ColunaTipos;

//Estrutura para armazenar o tipo e nome da coluna digitados pelo usuário
typedef struct coluna {
    ColunaTipos coluna_tipo;
    char *coluna_nome;
} Coluna;

//Estrutura para armazenar o nome do banco de dados e sua quantidade de colunas
typedef struct tabela {
    Coluna *colunas;
    char tabela_nome[STRING_MAX_SIZE];
} Tabela;

//Estrutura dinâmica utilizada para armazenar os dados propriamente dito do banco de dados
//usaremos quando necessitar de dinamismo na escrita e leitura dos dados
typedef union coluna_dados{
    int inteiro;
    float flutuante;
    double real;
    char caracter;
    char *string;
} Dados;

#endif