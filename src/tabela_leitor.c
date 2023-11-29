#include <stdio.h>
#include <string.h>

void substituirCaractere(char *string) {
    char caractereSubstituir = ';';
    // Percorre a string
    for (int i = 0; string[i] != '\0'; ++i) {
        // Se encontrar o caractere antigo, substitui pelo novo
        if (string[i] == caractereSubstituir) {
            string[i] = ' ';
        }
    }
}

int lerArquivo() {
    char *result;
    char linha[101];
    FILE *arquivo = fopen("teste.txt", "rt");
    char *pedaco;
    int i;

    i = 1;
    while (!feof(arquivo)) {
        result = fgets(linha, 100, arquivo);
        if (result) {
            // substituirCaractere(linha);
            // printf("Linha %d:", i);
            pedaco = strtok(linha, ";");

            while(pedaco != NULL) {
                if (pedaco[strlen(pedaco)-1] == '\n') {
                    pedaco[strlen(pedaco)-1] = '\0';
                }
                printf(" %-20s |", pedaco);

                pedaco = strtok(NULL, ";");
            }
            printf("\n");
            // Use o especificador de largura para alinhar as colunas
            // printf("%-12s%-12s%-12s\n", linha, "", "");

            i++;
        }
    }
    fclose(arquivo);

    return 0;
}

int main() {
    lerArquivo();
    return 0;
}
