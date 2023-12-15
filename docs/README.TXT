Padrões de código usados no projeto:
	- Nome de função: Segue o padrão snake_case e o idioma é português.
	- Nome de variável: Segue o padrão snake_case e o idioma é português.
	- Uso das chaves: Foi utilizada a convenção da linguagem C.
	- Nome de arquivo: Segue o padrão snake_case e o idioma é o português.
	- Define: Todas as letras em maiúsculo e o idioma é o portugês.
	- Includes: Mesmo nome do arquivo base.

Como compilar o projeto:
    Usuários de Linux e MacOS:
        Para compilar o  programa é preciso estar no diretório inicial do 'sgbd', aonde contém o arquivo Makefile, e executar o comando 'make', a aplicação será compilada automaticamente e o binário estará localizado no diretório 'bin' com o nome 'sgbd.bin'. 

	Usuários de Windows:
		[...]        

Como executar:
    Para executar o siga a sequência de comandos descrita abaixo:
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

	OBS: Ao fim da execução de cada funcionalidade é necessário pressionar qualquer tecla para voltar ao menu inicial
			
	Em seguida Aparecerá um prompt perguntando o que você quer fazer, para executar alguma das opções basta digitar o número dela e teclar 'Enter'.
	Após isso, dependendo da sua escolha será pedido mais informações, que serão detalahadas abaixo.
	
	Opção 1 (Criar Tabela):
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
					
	Opção 2 (Criar Linhas):
		Irá pedir o nome da tabela que irá ser modificada, a quantidade de linhas que serão adicionadas e os valores de cada linha.
		
		Exemplo:
			Digite o nome do arquivo que desejas adicionar as linhas: Teste
			Digite quantas linhas ira adicionar a cada coluna: 2
			Digite a 1ª linha: 1 Nome1
			Digite a 2ª linha: 2 Nome2
			
		OBS: O valor de cada coluna tem que ser separada por espaço, como mostrado acima.			

	Opção 3 (Listar Tabelas):
		Listará todas as tabelas existentes criadas

	Opção 4 (Listar Todos os Dados):
		Irá pedir o nome da tabela que irá mostrar os dados e os dados serão mostrados em forma de tabela.
		OBS: Para funcionar corretamente é preciso que o nome seja igual ao da tabela existente, se não o programa não irá encontrar a tabela

		Exemplo:
			Digite o nome do Banco de Dados: Teste
			
			+-------------+---------------+----------------+
			| ID(INT)     | NOME(STRING)  | IDADE(INT)     |
			+-------------+---------------+----------------+
			| 1           | George        | 50             |
			+-------------+---------------+----------------+
			| 7           | Jaicir        | 50             |
			+-------------+---------------+----------------+

	Opção 5 (Pesquisar Valor):
		Irá pedir o nome da tabela, o nome da coluna que a pesquisa será feita e o valor que deseja pesquisar.
		Em seguida será mostrado um menu com opções de pesquisa, basta selecionar alguma das opções que o programa irá retornar o valor se ele existir.

		Exemplo:
			Digite o nome da tabela: Teste
			Digite o nome da coluna: NOME
			Digite o valor que deseja pesquisar na coluna: Jaicir
			1. Valores maior que o valor informado
			2. Valores maior ou igual que o valor informado
			3. Valores igual ao valor informado
			4. Valores menor que o valor informado
			5. Valores menor ou igual que o valor informado
			6. Valores próximo ao valor informado (se aplica apenas se a coluna for do tipo string)
			Digite o tipo de pesquisa: 3
			Valores encontrados: [Jaicir]

	Opção 6 (Apagar Linha):
		Irá pedir o nome da tabela e a chave primária da linha a ser apagada.

		Exemplo:
			Informe o nome da tabela: Teste
			Informe a chave primária da linha: 4
			Linha apagada com sucesso

	Opção 7 (Apagar Tabela):
		Irá pedir o nome da tabela que será apagada.
		
		Exemplo:
			Informe o nome da tabela: Teste
			Tabela apagada com sucesso

	Opção 0 (Sair):
		Irá finalizar a execução do programa.