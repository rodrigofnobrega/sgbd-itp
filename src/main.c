#include <stdio.h>
#include "..\includes\create.h"

int main(){
    int option;
    do{
        printf("1. Criar Tabela\n2. Listar Tabelas\n3. Criar Linha\n4. Listar Todos os Dados\n5. Pesquisar Valor\n6. Apagar Linha\n7. Apagar Tabela\n0. Sair\nDigite sua escolha: ");
        scanf("%d", &option);
        switch(option){
            case 1:
                criarTabela();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 0:
                printf("Saindo...");
                break;
            default:
                printf("Erro! Digite uma opção válida.\n");
        }

    } while(option != 0);   

}