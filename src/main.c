#include <stdio.h>
#include "../includes/criar_tabela.h"
#include "../includes/criar_linha.h"
#include "../includes/apagar_tabela.h"
#include "../includes/listar_tabelas.h"
#include "../includes/apagar_linha.h"

int main(){
    int option;
    do{
        printf("1. Criar Tabela\n2. Criar Linhas\n3. Listar Tabelas\n4. Listar Todos os Dados\n5. Pesquisar Valor\n6. Apagar Linha\n7. Apagar Tabela\n0. Sair\nDigite sua escolha: ");
        scanf("%d", &option);
        getchar();
        printf("\e[1;1H\e[2J");
        switch(option){
            case 1:
                criar_tabela();
                break;
            case 2:
                criar_linha(); 
                printf("LINHA CRIADA.\n");
                break;
            case 3:
                mostrar_tabelas();
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                char nome_tabela[STRING_MAX_SIZE];
                char chave_primaria[STRING_MAX_SIZE];

                printf("Informe o nome da tabela: ");
                fgets(nome_tabela, sizeof(nome_tabela), stdin);
                remover_quebra_linha(nome_tabela);

                printf("Informe a chave primária da linha: ");
                fgets(chave_primaria, sizeof(chave_primaria), stdin);
                remover_quebra_linha(chave_primaria);

                if (remover_linha(nome_tabela, chave_primaria) == 1) {
                    printf("Linha apagada com sucesso\n");
                } else {
                    printf("Linha não encontrada\n");
                }
                break;
            case 7:
                if (apagar_tabela() == 0) {
                    printf("Tabela não encontrada\n");
                } else if (apagar_tabela() == -1) {
                    printf("Erro ao apagar tabela\n");
                }
                break;
            case 0:
                printf("Saindo...");
                break;
            default:
                printf("Erro! Digite uma opção válida.\n");
        }
        printf("Pressione qualquer tecla para continuar");
        getchar();
        printf("\e[1;1H\e[2J");
    } while(option != 0);   

}