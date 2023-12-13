#include <stdio.h>
#include <string.h>
#include <ctype.h>

void upper_string(char *string) {
    while (*string) {
        *string = toupper(*string);
        string++;
    }
}

void remover_quebra_linha(char *string) {
    int tamanho_string = strlen(string);

    if (string[tamanho_string-1] == '\n') {
        string[tamanho_string-1] = '\0';
    }
}
