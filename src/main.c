#include <stdio.h>
#include "..\includes\criar_tabela.h"
#include "..\includes\criar_linha.h"
#include "..\includes\listar_tabelas.h"

int main(){
    int option;
    do{
        printf("1. Criar Tabela\n2. Criar Linhas\n3. Listar Tabelas\n4. Listar Todos os Dados\n5. Pesquisar Valor\n6. Apagar Linha\n7. Apagar Tabela\n0. Sair\nDigite sua escolha: ");
        scanf("%d", &option);
        getchar();
        switch(option){
            case 1:
                criar_tabela();
                break;
            case 2:
                criar_linha(); 
                break;
            case 3:
                mostrar_tabelas();
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