#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_MAXIMO_STRING 50

char* processarString(char *entrada) {
    // Calcula o comprimento da string
    size_t len = strlen(entrada);

    // Aloca espaço para a nova string (comprimento - 1 para remover o ';')
    char *novaString = (char*)malloc(len);

    if (novaString == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    if (entrada[len - 1] == '\n') {
        entrada[len - 1] = '\0';
    }

    // Copia os caracteres da entrada para a nova string, excluindo o ';'
    for (size_t i = 0, j = 0; i < len; i++) {
        if (entrada[i] != ';') {
            novaString[j++] = entrada[i];
        }
    }

    // Adiciona o caractere nulo ao final da nova string
    novaString[len - 1] = '\0';

    return novaString;
}

int lerLinhas(char ***linhas, char ***colunas, int quantidade_coluna) {
    char aux_valor_linha[TAMANHO_MAXIMO_STRING];
    int quantidade_valores_por_linha = 0;
    int quantidade_linhas = 0;

    *linhas = (char **)malloc(sizeof(char *) * 1);

    printf("CRIANDO LINHAS (digite 'fim' para parar) \n");

    for (int i = 0; ; i++) {
        printf("Criando a linha %d\n", quantidade_linhas+1);
        
        for (int j = 0; j < quantidade_coluna; j++) {        
            printf("Valor da coluna %2s: ", processarString((*colunas)[j]));
            scanf(" %s", aux_valor_linha);
            
            if (strcmp(aux_valor_linha, "fim") == 0) {
                return quantidade_linhas;
            }

            strcat(aux_valor_linha, ";");

            (*linhas)[quantidade_valores_por_linha] = (char *)malloc(strlen(aux_valor_linha) * sizeof(char));

            strcpy((*linhas)[quantidade_valores_por_linha], aux_valor_linha);

            // Substituindo caso exista \n no final da string por \0
            if ((*linhas)[quantidade_valores_por_linha][strlen(aux_valor_linha) - 1] == '\n') {
                (*linhas)[quantidade_valores_por_linha][strlen(aux_valor_linha) - 1] = '\0';
            }

            // A condição está verificando se a quantidade de elementos digitados é igual a quantidade de colunas
            // se for igual vai adicionar uma quebra de linha e pular para a próxima linha
            if ((quantidade_valores_por_linha+1) % quantidade_coluna == 0) {
                (*linhas)[quantidade_valores_por_linha] = (char *)realloc((*linhas)[quantidade_valores_por_linha], (strlen((*linhas)[quantidade_valores_por_linha]) + 2) * sizeof(char));
                strcat((*linhas)[quantidade_valores_por_linha], "\n");
            
                quantidade_linhas++;
            }

            quantidade_valores_por_linha++;

            *linhas = (char **)realloc(*linhas, sizeof(char *) * (quantidade_valores_por_linha + 1));
        }
    }

    return quantidade_linhas;
}

int lerColunas(char ***nome_colunas) {
    char aux_nome_coluna[TAMANHO_MAXIMO_STRING]; // Variável auxiliar para pegar o tamanho de string e alocar a memória exata no vetor 'nome_colunas'
    int quantidade_colunas = 0;

    *nome_colunas = (char **)malloc(sizeof(char *) * 1);
    
    printf("CRIANDO COLUNAS (digite 'fim' para parar) \n");

    printf("Informe o nome da coluna para ser a chave primária\n");
    for (int i = 0; ; i++) {
        printf("Nome da coluna %2d: ", i+1);
        scanf(" %s", aux_nome_coluna);

        if (strcmp(aux_nome_coluna, "fim") == 0) {
            if (i > 0) {
                // Alocar mais um byte de espaço para adicionar o \n à última coluna inserida 
                (*nome_colunas)[i - 1] = (char *)realloc((*nome_colunas)[i - 1], (strlen((*nome_colunas)[i - 1]) + 2) * sizeof(char));
                strcat((*nome_colunas)[i - 1], "\n");
            }

            break;
        }

        strcat(aux_nome_coluna, ";");

        (*nome_colunas)[i] = (char *)malloc(strlen(aux_nome_coluna) * sizeof(char));

        strcpy((*nome_colunas)[i], aux_nome_coluna);

        // Substituindo caso exista \n no final da string por \0
        if ((*nome_colunas)[i][strlen(aux_nome_coluna) - 1] == '\n') {
            (*nome_colunas)[i][strlen(aux_nome_coluna) - 1] = '\0';
        }

        quantidade_colunas++;

        // Alocando memória para o vetor conseguir adicionar mais uma coluna
        // Talvez seja melhor alocar a memória depois de saber que vai existir mais uma coluna?
        *nome_colunas = (char **)realloc(*nome_colunas, sizeof(char *) * (quantidade_colunas + 1));
    }

    return quantidade_colunas;
}

void criarTabela() {
    // nome_tabela ainda não foi usada mas será necessária no futuro
    char nome_tabela[50];
    // Vetor para armazenar todas as colunas informadas pelo usuário
    char **colunas;
    // Vetor que armazena o valor de cada coluna, talvez seja melhor renomea-la
    char **linhas;

    int quantidade_colunas = 0;
    int quantidade_linhas = 0;

    printf("Informe o nome da tabela: ");
    scanf(" %s", &nome_tabela);

    strcat(nome_tabela, ".txt");

    // O nome do arquivo hard-coded pode ser substituida
    // pela concatenação da variável 'nome_tabela' + .txt
    FILE *arquivo = fopen(nome_tabela, "w");

    quantidade_colunas = lerColunas(&colunas);

    // Salvando no arquivo as colunas
    for (int i = 0; colunas[i] != NULL; i++)
    {
        fprintf(arquivo, "%s", colunas[i]);
    }

    quantidade_linhas = lerLinhas(&linhas, &colunas, quantidade_colunas);

    // Salvando no arquivo o valor das colunas
    for (int i = 0; linhas[i] != NULL; i++)
    {
        fprintf(arquivo, "%s", linhas[i]); 
    }
}

//IMPORTANTE
// Na função acredito que seja necessário liberar as memórias alocadas
// para os vetores colunas e linhas

// Acredito que seja necessário renomear as variáveis e funções para nomes melhores,
// que deixe mais explícito as suas funcionalidades

int main() {
    // Função para criar uma tabela
    /* Ainda falta implementar
    * Chave primária
    * Nome da tabela
    * Tipo de cada coluna
     */
    criarTabela(); 


    /* Código para adicionar novas linhas em uma tabela já existente 
    
    FILE *arquivo = fopen("tabela.txt", "a");
    char **linhas;
    lerLinhas(&linhas, 3);
    for (int i = 0; linhas[i] != NULL; i++)
    {
        fprintf(arquivo, "%s", linhas[i]); 
    }
 */
    return 0;
}