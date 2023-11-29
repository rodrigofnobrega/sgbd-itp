#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura do registro
typedef struct {
    int id;
    char nome[50];
    float salario;
} Registro;

int main() {
    FILE *arquivo;
    char nome_arquivo[] = "meudatabase.cdb";

    arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Leitura do registro do arquivo
    Registro registro_lido;
    while (fread(&registro_lido, sizeof(Registro), 1, arquivo) == 1) {
        
        printf("ID: %d, Nome: %s, Salario: %.2f\n", registro_lido.id, registro_lido.nome, registro_lido.salario);
    }
    
    fclose(arquivo);

    return 0;
}
