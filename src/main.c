/*
===============================================================================
Arquivo: main.c
Data: 13 de dezembro de 2023
Descrição: Função principal que serve como ponto de entrada do programa.
           Oferece um menu interativo para realizar operações em um banco de dados.
           O programa continuará a ser executado até que o usuário escolha a opção 0 (Sair).
===============================================================================
*/
#include <stdio.h>
#include "../includes/criar_tabela.h"
#include "../includes/criar_linha.h"
#include "../includes/apagar_tabela.h"
#include "../includes/apagar_linha.h"
#include "../includes/listar_tabelas.h"
#include "../includes/listar_dados_tabela.h"
#include "../includes/pesquisar_valor.h"

int main(){
    int option;
    char nome_tabela[STRING_MAX_SIZE];
    char chave_primaria[STRING_MAX_SIZE];
    do{
        printf("1. Criar Tabela\n2. Criar Linhas\n3. Listar Tabelas\n4. Listar Todos os Dados\n5. Pesquisar Valor\n6. Apagar Linha\n7. Apagar Tabela\n0. Sair\nDigite sua escolha: ");
        scanf("%d", &option);
        getchar();
        printf("\e[1;1H\e[2J");
        switch(option){
            case 1:
                criar_banco_de_dados();
                break;
            case 2:
                criar_linha(); 
                break;
            case 3:
                mostrar_tabelas();
                break;
            case 4:
                listar_dados();
                break;
            case 5:
                pesquisar_valor();
                break;
            case 6:
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
                int apagou_tabela = apagar_tabela();
                if (apagou_tabela == 1) {
                    printf("Tabela apagada com sucesso");
                } else if (apagou_tabela == 0) {
                    printf("Tabela não encontrada\n");
                } else if (apagou_tabela == -1) {
                    printf("Erro ao encontrar diretório da tabela\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                return;
            default:
                printf("Erro! Digite uma opção válida.\n");
        }
        printf("Pressione qualquer tecla para continuar");
        getchar();
        printf("\e[1;1H\e[2J");
    } while(option != 0);   

}