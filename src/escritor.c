#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    float salario;
} Registro;

int main() {
    FILE *arquivo;
    char nome_arquivo[] = "meudatabase.cdb";

    arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

    Registro registro;
    registro.id = 1;
    strcpy(registro.nome, "Joao");
    registro.salario = 2500.0;

    fwrite(&registro, sizeof(Registro), 1, arquivo);
    
    fclose(arquivo);

    printf("Arquivo '%s' criado com sucesso.\n", nome_arquivo);
    
    return 0;
}
