/*
=========================================================================================================
Arquivo: criar_linha.c
Data modificação: 15 de dezembro de 2023
Descrição: O objetivo desse código é adicionar as linhas, ou tuplas, para o banco de dados. Demonstrando ao 
usuário como está formatado as colunas do banco de dados e assim requisitando que o usário digite as linhas
de acordo com essa formtação. Ademais, ele realiza tratamento de erro quanto ao tipo do dado digitado e se 
está relacionado corretamente com o da coluna.
=========================================================================================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../../includes/utils.h"
#include "../../includes/utils/file_utils.h"
#define MAX_TAMANHO_LINHA 100

/*--------------------------------------------------------------------------------
Função: Printa na tela uma linha horizontal de delimitação formatadas para o tamanho dos caracters do banco.
Paramêtros: 
    -Array contendo o tamanho das colunas;
    -Quantidade de colunas;
*/
void mostrar_line(int *tam_colunas, int qtd_colunas) {
    printf("+");
    for (int i = 0; i < qtd_colunas; i++) {
        for (int j = 0; j < tam_colunas[i] + 2; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}
/*--------------------------------------------------------------------------------
Função: Printa a tabela em si do banco de dados, utiliza a função mostrar linhas para
formatação.
    -Array contendo o nome das colunas;
    -Array contendo os tipos das colunas;
    -Quantidade de colunas;
*/
void formatar_tabelas(char **nomes_colunas, int *tipos_colunas, int qtd_colunas) {
    int tam_colunas[qtd_colunas];
    for (int i = 0; i < qtd_colunas; i++) {
        tam_colunas[i] = strlen(nomes_colunas[i])+9;
    }

    mostrar_line(tam_colunas, qtd_colunas);
    printf("|");
    for (int i = 0; i < qtd_colunas; i++) {
        switch (tipos_colunas[i]) {
            case INT:
                sprintf(nomes_colunas[i], "%s(INT)", nomes_colunas[i]);
                printf(" %-*s |", tam_colunas[i], nomes_colunas[i]); 
                break;
            case FLOAT:
                sprintf(nomes_colunas[i], "%s(FLOAT)", nomes_colunas[i]);
                printf(" %-*s |", tam_colunas[i], nomes_colunas[i]); 
                break;
            case DOUBLE:
                sprintf(nomes_colunas[i], "%s(DOUBLE)", nomes_colunas[i]); 
                printf(" %-*s |", tam_colunas[i], nomes_colunas[i]);
                break;
            case CHAR:
                sprintf(nomes_colunas[i], "%s(CHAR)", nomes_colunas[i]); 
                printf(" %-*s |", tam_colunas[i], nomes_colunas[i]);
                break;
            case STRING:
                sprintf(nomes_colunas[i], "%s(STRING)", nomes_colunas[i]); 
                printf(" %-*s |", tam_colunas[i], nomes_colunas[i]);
                break;
            default:
                break;
        }
    }
    printf("\n");

    mostrar_line(tam_colunas, qtd_colunas);
    printf("|");
    for (int j = 0; j < qtd_colunas; j++) {
        printf(" %-*s |", tam_colunas[j], "...");
    }
    printf("\n");

    mostrar_line(tam_colunas, qtd_colunas);
}

/*--------------------------------------------------------------------------------
Função: Define o tipo do dado a ser coletado pela.
Paramêtros: 
    -Linha lida do banco de dados;
    -Tipo da coluna;
    -Tipo variante para receber os dados;
*/
Dados definindo_dados(char *linha, int col_type, Dados col_dados){
    switch(col_type){
        case INT:
            sscanf(linha,"%d", &col_dados.inteiro);
            break;
        case FLOAT:
            sscanf(linha,"%f", &col_dados.flutuante);
            break;
        case DOUBLE:
            sscanf(linha,"%lf", &col_dados.real);
            break;
        case CHAR:
            sscanf(linha," %c", &col_dados.caracter);
            break;
        case STRING:
            col_dados.string = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
            sscanf(linha,"%s", col_dados.string);
            break;
    }
    return col_dados;
}
/*--------------------------------------------------------------------------------
Função: Adiciona as linhas ao banco de dados.
*/
void criar_linha() {
    // Declaração de variáveis
    char banco_nome[STRING_MAX_SIZE];
    FILE *arquivo_ler;
    FILE *arquivo_escrever;

    // Solicita o nome do arquivo que receberá as novas linhas
    printf("Digite o nome do arquivo que desejas adicionar as linhas: ");
    fgets(banco_nome, STRING_MAX_SIZE, stdin);

    // Remove o caractere de nova linha, se existir
    int string_length = strlen(banco_nome);
    if (banco_nome[string_length - 1] == '\n') {
        banco_nome[string_length - 1] = '\0';
    }

    // Abre o arquivo para leitura
    arquivo_ler = abrir_arquivo(banco_nome, 'r');

    // Processa a primeira linha para determinar os tipos de dados das colunas
    // e os nomes das colunas
    int tam_titulo = strlen("Coluna Nome");
    char linha[MAX_TAMANHO_LINHA];

    if (fgets(linha, MAX_TAMANHO_LINHA, arquivo_ler) == NULL) {
        perror("Erro ao ler a primeira linha");
        fclose(arquivo_ler);
        return;
    }

    int pos = 0;
    int aux = 1;
    int *col_types = (int *)malloc(sizeof(int) * aux);

    while (sscanf(linha + pos, "%d;", &col_types[aux - 1]) == 1) {
        if (sizeof(col_types[aux - 1] / 4) > tam_titulo) {
            tam_titulo = col_types[aux - 1];
        }
        pos += strcspn(linha + pos, ";") + 1;
        aux++;
        col_types = realloc(col_types, sizeof(int) * aux * 2);
    }

    // Processa a segunda linha para obter os nomes das colunas
    if (fgets(linha, MAX_TAMANHO_LINHA, arquivo_ler) == NULL) {
        perror("Erro ao ler a segunda linha");
        free(col_types);
        fclose(arquivo_ler);
        return;
    }

    pos = 0;
    aux = 1;
    char **col_names = (char **)malloc(sizeof(char *) * aux);
    col_names[aux - 1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);

    while (sscanf(linha + pos, "%[^;\n];", col_names[aux - 1]) == 1) {
        if (strlen(col_names[aux - 1]) > tam_titulo) {
            tam_titulo = strlen(col_names[aux - 1]);
        }
        pos += strcspn(linha + pos, ";") + 1;
        aux++;
        col_names = realloc(col_names, sizeof(char *) * 2 * aux);
        col_names[aux - 1] = (char *)malloc(sizeof(char) * STRING_MAX_SIZE);
    }

    // Formata as tabelas com os nomes e tipos de colunas
    formatar_tabelas(col_names, col_types, aux - 1);

    // Salva o último ID da tabela para fins de comparação com a entrada do usuário
    int ultimo_id;
    if (fgets(linha, BUFFER_MAX_SIZE, arquivo_ler) == NULL) {
        ultimo_id = 0;
    } else {
        while (fscanf(arquivo_ler, "%d", &ultimo_id) == 1) {}
    }

    fclose(arquivo_ler);

    // Abre o arquivo para escrita (modo 'a' - append)
    arquivo_escrever = abrir_arquivo(banco_nome, 'a');

    // Solicita a quantidade de linhas a serem adicionadas
    int qtd_linhas;
    printf("\nDigite quantas linhas irá adicionar a cada coluna acima: ");
    scanf("%d", &qtd_linhas);
    getchar();

    // Aloca espaço para armazenar os dados das novas linhas
    Dados *col_dados = (Dados *)malloc(sizeof(Dados) * qtd_linhas * aux - 1);

    // Loop para receber e escrever as novas linhas no arquivo
    for (int i = 0; i < qtd_linhas; i++) {
        printf("Digite a %dª linha: ", i + 1);

        fgets(linha, MAX_TAMANHO_LINHA, stdin);

        // Verifica se a chave primária digitada é um inteiro
        int id;
        if (sscanf(linha, "%d", &id) == 0) {
            printf("O id precisa obrigatoriamente ser inteiro.\n");
            break;
        } else if (id <= ultimo_id) {
            printf("O id precisa ser maior que o último da lista ID:[%d], ou maior que 0: \n", ultimo_id);
            break;
        }

        // Remove o caractere de nova linha, se existir
        string_length = strlen(linha);
        if (linha[string_length - 1] == '\n') {
            linha[string_length - 1] = '\0';
        }

        // Escreve a nova linha no arquivo
        fprintf(arquivo_escrever, "\n");
        char *token = strtok(linha, " ");
        while (token != NULL) {
            fprintf(arquivo_escrever, "%s;", token);
            token = strtok(NULL, " ");
        }
    }

    // Libera a memória alocada
    free(col_types);
    free(col_names);
    free(col_dados);

    // Fecha o arquivo
    fclose(arquivo_escrever);
}