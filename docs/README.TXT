Como compilar o projeto:
    Usuários de Linux e MacOS:
        Para compilar o  programa é preciso estar no diretório inicial do 'sgbd', aonde contém o arquivo Makefile, e executar o comando 'make', a aplicação será compilada automaticamente e o binário estará localizado no diretório 'bin' com o nome 'sgbd.bin'. 
        
	Usuários de Windows:
		[...]        

Como executar:
    Para executar o binário a partir do diretório inicial basta rodar o comando './bin/sgbd.bin'.
    Para executar o binário no diretório bin é só seguir a sequência de comando abaixo:
    	1) cd bin/
    	2) ./sgbd.bin

Como o programa funciona:
	Quando a aplicação for executada será exibido o menu abaixo:
			1. Criar Tabela
			2. Criar Linhas
			3. Listar Tabelas
			4. Listar Todos os Dados
			5. Pesquisar Valor
			6. Apagar Linha
			7. Apagar Tabela
			0. Sair
			
	Logo em seguida Aparecerá um prompt perguntando o que você quer fazer, para executar alguma das opções basta digitar o número dela e teclar 'Enter'.
	Após isso, dependendo da sua escolha será pedido mais informações, que serão detalahadas abaixo.
	
	Opção 1:
		Irá pedir o nome da tabela, a coluna que irá servir de chave primária e em seguida as colunas com seus respectivos tipos, basta informar o que se pede e para finalizar digigar 'fim'.
		
		Exemplo:
			$Digite o nome do banco de dados: Teste
			$Nome da coluna de chave primária: Id
			$Nome da 1º coluna(digite 'fim' para finalizar): Nome
			$Tipo da 1º coluna(INT, FLOAT, DOUBLE, CHAR, STR): STR
			$Nome da 2º coluna(digite 'fim' para finalizar): Idade
			$Tipo da 2º coluna(INT, FLOAT, DOUBLE, CHAR, STR): INT
			$Nome da 3º coluna(digite 'fim' para finalizar): fim
			TABELA CRIADA.
			
		Ao finalizar a criação da tabela ela irá ser salva no diretório 'database' e para voltar ao menu basta apertar qualquer tecla.
		
	Opção 2:
		Irá pedir o nome da tabela que irá ser modificada, a quantidade de linhas que serão adicionadas e os valores de cada linha.
		
		Exemplo:
			Digite o nome do arquivo que desejas adicionar as linhas: Teste
			Digite quantas linhas ira adicionar a cada coluna: 2
			Digite a 1ª linha: 1 Nome1
			Digite a 2ª linha: 2 Nome2
			
		Ao finalizar basta apertar qualquer tecla para voltar ao menu.
		OBS: O valor de cada coluna tem que ser separada por espaço, como mostrado acima.



			
