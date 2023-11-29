#include <stdio.h>

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
    FILE *arquivo = fopen( "teste.txt", "rt");
    int i;

    i=1;
    while (!feof(arquivo)) {
        result = fgets(linha, 100, arquivo);
        if (result) {
            substituirCaractere(linha);
            printf("Linha %d: %s",i,linha);
            i++;
        }
    }
    fclose(arquivo);

    return 0; 
}

int main(){ 
    lerArquivo();
    return 0;
}