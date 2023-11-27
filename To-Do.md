# Descrição da Criação das Operações

1. **Criar uma tabela**  
   - os tipos de dados para as colunas poderão ser os tipos primitivos em C ( char, int, float e double) e strings
   - os valores deverão ser armazenados em arquivo
   - na criação da tabela deverá ser solicitado um nome de coluna para ser a chave primária. 
     - A chave primária deverá ser obrigatoriamente do tipo inteiro sem sinal
2. **Listar todas as tableas**
   - deverá mostrar para o usuário as tabelas existentes
3. **Criar uma nova linha na tabela**
   - Usuário deve informar o nome na tabela
   - Sistema deve solicitar os valores de cada uma das colunas
   - sistema deve verificar a chave primária
     - Em uma tabela deve existir um e apenas um valor de chave primária. Se o usuário informar uma chave que já existe, sistema deve emitir uma mensagem de erro e não deve inserir o registro
4. **Listar todos os dados de uma tabela**
   - Usuário deve informar qual a tabela para serem listados os dados
   - os dados deverão ser obtidos a partir do arquivo que armazena
5. **Pesquisar valor em uma tabela**
   - Usuário deverá informar o nome da tabela onde realizará a pesquisa
   - Sistema deverá fornecer as colunas disponíveis na tabela o usuário deverá selecionar uma delas
   - Sistema deverá solicitar o valor para pesquisar, disponibilizando algumas opções
     - valores maior que o valor informado
     - valores maior ou igual que o valor informado
     - valores igual o valor informado
     - valores menor que o valor informado
     - valores menor ou igual que o valor informado
     - valores próximo ao valor informado
       - Se aokuca aoebas se a coluna for do tipo string
6. **Apagar uma tupla (registro ou linha) de uma tabela**
   - Usuário deve informar o nome da tabela e a chave primária da tupla a ser apagada
7. **Apagar uma tabela**
   - usuário deverá fornecer o nome da tabela a ser apagada