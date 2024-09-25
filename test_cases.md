# TC01: Arquivos não existentes

**Objetivo:** Verificar se o programa encerra corretamente quando um arquivo não existe.

## Steps:
1. Excluir um dos arquivos de entrada (por exemplo, `aluno.txt` ou `professor.txt` ).
2. Executar o programa.
3. Verificar se o programa imprime uma mensagem de erro e encerra.

**Resultado esperado:** O programa deve imprimir uma mensagem de erro, como "Arquivo aluno.txt faltando", e encerrar.
</br></br>
# TC02: Arquivos com formato incorreto

**Objetivo:** Verificar se o programa lê corretamente os arquivos com formato correto.

## Steps:
1. Criar um arquivo com formato incorreto (por exemplo, `aluno.txt` com o conteúdo:  
   `"123 3 DSM 22 Camilla Borba 234 3 AMS 25 Mauricio Oliveira 976 3 AMS 24 Maria Clara Diniz 723 3 LOG 23 Pedro Alves"`  
   sem a linha com a quantidade de alunos).
2. Executar o programa.
3. Verificar se o programa imprime uma mensagem de erro e encerra.

**Resultado esperado:** O programa deve imprimir uma mensagem de erro e encerrar.
