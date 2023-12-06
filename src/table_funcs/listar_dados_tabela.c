#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100
#define TITULO "DADOS DA TABELA"
#define DB_PATH "../database/"

int contarColunas(char *linha) {
    int numColunas = 0;
    char *token = strtok(linha, ";"); // Assumindo ponto e vírgula como delimitador

    while (token != NULL) {
        numColunas++;
        token = strtok(NULL, ";");
    }

    return numColunas;
}

void exibir_linhas(int tamformatacao_tabela) {
    printf("+");
    for (int i = 0; i < tamformatacao_tabela + 2; i++) {
        printf("-");
    }
    printf("+\n");
}

void organizar_tabelas(char *valor, int tam_formatacao_tabela, int qtd_linahs) {
    int espacos_em_branco = (tam_formatacao_tabela - strlen(TITULO));

    exibir_linhas(tam_formatacao_tabela);

    // Calcular a quantidade de espaços em branco para centralizar o texto
    // e mostrar linhas com o texto centralizado
    // se o tamanho de espacos_em_branco for ímpar é preciso adicionar 
    // mais um de espaco no final para manter a formatação
    if (espacos_em_branco % 2 == 0) {
        espacos_em_branco /= 2;
        printf("| %*s%s%*s |\n", espacos_em_branco, "", TITULO, espacos_em_branco, "");
    } else {
        espacos_em_branco /= 2;
        printf("| %*s%s%*s |\n", espacos_em_branco, "", TITULO, espacos_em_branco+1, "");
    }

    exibir_linhas(tam_formatacao_tabela);

    // Mostrar as linhas com os nomes das tabelas
    printf("| %-*s |\n", tam_formatacao_tabela, valor);

    exibir_linhas(tam_formatacao_tabela);
}

void mostrar_conteudo_arquivo(char *nomeArquivo) {
    FILE *arquivo;
    char linha[MAX_BUFFER_SIZE]; // Vetor que vai pegar toda a linha
    char **dados; // Vetor que vai armazenar os dados
    int *tam_formatacao_colunas; // Vetor que vai armazenar o tamanho máximo de cada coluna
    int contador; // Contador pra acessar o tamanho máximo de cada coluna do vetor tam_formatacao_colunas
    int qtd_colunas;

    char caminhoArquivo[MAX_BUFFER_SIZE];
    snprintf(caminhoArquivo, sizeof(caminhoArquivo), "%s%s", DB_PATH, nomeArquivo);

    arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    
    qtd_colunas = contarColunas(fgets(linha, sizeof(linha), arquivo));
    tam_formatacao_colunas = (int *)malloc(sizeof(int) * qtd_colunas);
    dados = (char **)malloc(sizeof(char) * qtd_colunas);
    fseek(arquivo, 0, SEEK_SET); // Voltando o arquivo para o início

    // O código fgets(linha, sizeof(linha), arquivo) pega uma linha completa da tabela
    for (int i = 0; fgets(linha, sizeof(linha), arquivo) != NULL; i++) {
        // Separando o valor da linha para pegar o valor de cada coluna
        char *token = strtok(linha, ";");

        while (token != NULL) {
            // Garantindo que contando não irá acessar um valor acima
            // do tamanho do vetor tam_formatacao_colunas
            if (contador > qtd_colunas) {
                contador = 0;
                break;
            }
            if (i = 0) {
                // Adicionando os tamanhos das colunas
                tam_formatacao_colunas[contador] = strlen(token);
            }
            else if (strlen(linha) > tam_formatacao_colunas[contador]) {
                tam_formatacao_colunas[contador] = strlen(linha);
            }
            contador++;
            token = strtok(NULL, ";");
        }

        dados = (char **)realloc(dados, sizeof(char) * qtd_colunas);
    }

    fclose(arquivo);
}

    int main() {
        mostrar_conteudo_arquivo("Teste.txt");
    }
