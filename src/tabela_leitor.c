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
    FILE *arquivo = fopen("tabela.txt", "rt");
    char *pedaco;
    int i;

    i = 1;
    // Não sei para que serve a função feof()
    while (!feof(arquivo)) {
        result = fgets(linha, 100, arquivo);
        if (result) {
            // Divide a string no ';'
            pedaco = strtok(linha, ";");

            // Enquanto existir string vai mostrar um pedaço da string no console
            while(pedaco != NULL) {
                if (pedaco[strlen(pedaco)-1] == '\n') {
                    pedaco[strlen(pedaco)-1] = '\0';
                }
                printf(" %-20s |", pedaco);

                pedaco = strtok(NULL, ";");
            }
            printf("\n");

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
