/*
=========================================================================================================
Arquivo: pesquisar_valor.c
Data modificação: 15 de dezembro de 2023
Descrição: O objetivo desse código é pesquisar em algum banco de dados pre-existinte valores digitados pelo
usuário e realizar lógicas de (maior que, menor que, igual que) para todos os valores da coluna que o usuário
escolheu para realizar a pesquisa.
=========================================================================================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../../includes/utils.h"
#include "../../includes/utils/file_utils.h"
#include "../../includes/utils/string_utils.h"
#include "../../includes/utils/search_utils.h"

/*--------------------------------------------------------------------------------
Função: Escanea a opção escolhida do usuário para pesquisa nos dados da coluna.
*/
int pesquisa_options(){
    int pesquisa_opt;
    printf("1. Valores maior que o valor informado\n2. Valores maior ou igual que o valor informado\n3. Valores igual ao valor informado\n4. Valores menor que o valor informado\n5. Valores menor ou igual que o valor informado\n6. Valores próximo ao valor informado (se aplica apenas se a coluna for do tipo string)\n");
    printf("Digite o tipo de pesquisa: ");
    scanf("%d", &pesquisa_opt);
    getchar();
    return pesquisa_opt;
}

/*--------------------------------------------------------------------------------
Função: Principal que realiza todas as operações de leitura, pesquisa e análise, além de importar do search_utils funções para 
tratar dos tipos dinâmicos dos dados.
*/
int pesquisar_valor() {
    FILE *arquivo;
    char banco_nome[STRING_MAX_SIZE];

    // Solicita o nome do arquivo
    printf("Digite o nome do arquivo: ");
    fgets(banco_nome, 100, stdin);

    // Remove o caractere de nova linha, se existir
    int string_length = strlen(banco_nome);
    if (banco_nome[string_length - 1] == '\n') {
        banco_nome[string_length - 1] = '\0';
    }

    // Abre o arquivo para leitura
    arquivo = abrir_arquivo(banco_nome, 'r');

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        return -1;
    }

    // Variáveis para armazenar informações da coluna
    int tipo_coluna;
    int index_coluna;
    char nome_coluna[STRING_MAX_SIZE];

    // Solicita o nome da coluna
    printf("Digite o nome da coluna: ");
    scanf("%s", nome_coluna);
    upper_string(nome_coluna);
    getchar();

    char buffer[BUFFER_MAX_SIZE];
    fgets(buffer, BUFFER_MAX_SIZE, arquivo);

    int aux = 1;
    int pos = 0;
    int *coluna_tipos = (int *)malloc(sizeof(int) * aux);

    // Processa a primeira linha para determinar os tipos de dados das colunas
    while (sscanf(buffer + pos, "%d;", &coluna_tipos[aux - 1]) == 1) {
        pos += strcspn(buffer + pos, ";") + 1;
        aux++;
        coluna_tipos = realloc(coluna_tipos, sizeof(int) * 2 * aux);
    }

    fgets(buffer, BUFFER_MAX_SIZE, arquivo);

    int coluna_erro = 0;
    pos = 0;
    aux = 1;
    char **coluna_nomes = (char **)malloc(sizeof(char *) * aux);
    coluna_nomes[aux - 1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);

    // Processa a segunda linha para obter os nomes das colunas
    while (sscanf(buffer + pos, "%[^;\n];", coluna_nomes[aux - 1]) == 1) {
        if (strcmp(nome_coluna, coluna_nomes[aux - 1]) == 0) {
            tipo_coluna = coluna_tipos[aux - 1];
            index_coluna = aux - 1;
            coluna_erro = 1;
        }
        pos += strcspn(buffer + pos, ";") + 1;
        aux++;
        coluna_nomes = realloc(coluna_nomes, sizeof(char *) * 2 * aux);
        coluna_nomes[aux - 1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
    }

    // Verifica se o nome da coluna é válido
    if (coluna_erro == 0) {
        printf("Nome da coluna inválida. ");
        free(coluna_tipos);
        fclose(arquivo);
        free(arquivo);
        for (int i = 0; i < sizeof(coluna_nomes); i++) {
            free(coluna_nomes[i]);
        }
        free(coluna_nomes);
        return -1;
    }

    // Variável para armazenar o valor a ser pesquisado
    Dados valor;

    // Solicita o valor que deseja pesquisar na coluna
    printf("Digite o valor que deseja pesquisar na coluna: ");
    int pesquisa_opt;

    // Realiza a pesquisa conforme o tipo da coluna
    switch (tipo_coluna) {
        case INT:
            if (scanf("%d", &valor.inteiro) != 1) {
                printf("Valor digitado não corresponde ao tipo da coluna. ");
                break;
            };
            pesquisa_opt = pesquisa_options();
            printf("Valores encontrados: ");
            pesquisa_int(valor, arquivo, buffer, index_coluna, pesquisa_opt);
            break;
        case FLOAT:
            if (scanf("%f", &valor.flutuante) != 1) {
                printf("Valor digitado não corresponde ao tipo da coluna. ");
                break;
            };
            pesquisa_opt = pesquisa_options();
            printf("Valores encontrados: ");
            pesquisa_float(valor, arquivo, buffer, index_coluna, pesquisa_opt);
            break;
        case DOUBLE:
            if (scanf("%lf", &valor.real) != 1) {
                printf("Valor digitado não corresponde ao tipo da coluna. ");
                break;
            };
            pesquisa_opt = pesquisa_options();
            printf("Valores encontrados: ");
            pesquisa_double(valor, arquivo, buffer, index_coluna, pesquisa_opt);
            break;
        case CHAR:
            if (scanf("%c", &valor.caracter) != 1) {
                printf("Valor digitado não corresponde ao tipo da coluna. ");
                break;
            };
            pesquisa_opt = pesquisa_options();
            printf("Valores encontrados: ");
            pesquisa_char(valor, arquivo, buffer, index_coluna, pesquisa_opt);
            break;
        case STRING:
            valor.string = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
            if (scanf("%s", valor.string) != 1) {
                printf("Valor digitado não corresponde ao tipo da coluna. ");
                break;
            };
            pesquisa_opt = pesquisa_options();
            printf("Valores encontrados: ");
            pesquisa_string(valor, arquivo, buffer, index_coluna, pesquisa_opt);
            break;
        default:
            printf("\nErro de tipo. ");
            break;
    }

    printf("\n");

    // Fecha o arquivo e libera a memória alocada
    fclose(arquivo);

    for (int i = 0; i < (aux-1); i++) {
        free(coluna_nomes[i]);
    }
    
    free(coluna_nomes);
    free(coluna_tipos);
    return 0;
}