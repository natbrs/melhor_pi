# TC01: Arquivos não existentes

**Objetivo:** Verificar se o programa encerra corretamente quando um arquivo não existe.

## Steps:

1. Excluir um dos arquivos de entrada (por exemplo, `aluno.txt`,`professor.txt` ou `PI_AMS.txt` ).
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

# TC03: Validando CPF válido

**Objetivo:** Verificar se o programa permite votar com um CPF válido.

## Steps:

1.  Criar um arquivo `comissao.txt` com um CPF inválido (por exemplo, "123.456.789-01").
2.  Selecione a opção "a) Iniciar voto"
3.  Selecione a opção "a) Entrar com voto"
4.  Insira um CPF que seja inválido (por exemplo, "123.456.789-01")

- Verifique se o programa imprime uma mensagem de erro e encerra.

**Resultado esperado:** O programa deve imprimir uma mensagem de erro, como "CPF 123.456.789-01 inválido", e encerrar.

# TC04: Validando CPF válido

**Objetivo:** Verificar se o programa valida corretamente os CPFs.

## Steps:

1.  Criar um arquivo `comissao.txt` com um CPF válido (por exemplo, "393.486.442-20").
2.  Selecione a opção "a) Iniciar voto"
3.  Selecione a opção "a) Entrar com voto"
4.  Insira o CPF válido.

- Verifique se o programa permite votar com o CPF válido e imprime a mensagem "Voto registrado com sucesso".

**Resultado esperado:** O programa deve permitir votar e imprimir a mensagem "Voto registrado com sucesso".

# TC05: Votação com CPF já votado

**Objetivo:** Verificar se o programa não permite votar com um CPF que já votou.

## Steps:

1.  Criar um arquivo `comissao.txt` com um CPF válido (por exemplo, "393.486.442-20").
2.  Selecione a opção "a) Iniciar voto"
3.  Selecione a opção "a) Entrar com voto"
4.  Insira um CPF que seja válido (por exemplo, "393.486.442-20")

- Verifique se o programa não permite votar novamente com o mesmo CPF.

**Resultado esperado:** O programa deve permitir votar e imprimir a mensagem "Voto registrado com sucesso".

# TC06: Votação com código de PI inválido

**Objetivo:** Verifique se o programa não permite votar com um código de PI inválido.

## Steps:

1. Selecionar a opção "a) Entrar com voto"
2. Insira um código de PI inválido.

- Verifique se o programa permite votar com o código de PI inválido.

**Resultado esperado:** O programa deve imprimir uma mensagem de erro, como "TG nao encontrado. Tente novamente.", e encerrar.

# TC07: Votação com código de PI válido

**Objetivo:** Verifique se o programa permite votar com um código de PI válido.

## Steps:

1. Criar um arquivo `comissao.txt` com um código de PI válido.
2. Selecionar a opção "a) Entrar com voto"
3. Insira um código de PI válido.

- Verifique se o programa permite votar com o código de PI válido.

**Resultado esperado:** O programa deve permitir votar e imprimir a mensagem "Voto registrado com sucesso".

# TC07: Suspender votação

**Objetivo:** Verifique se o programa gera o arquivo "parcial.txt" corretamente ao suspender a votação.

## Steps:

1.  Selecione a opção "a) Iniciar voto"
2.  Selecione a opção "a) Entrar com voto"
3.  Insira um código de PI válido.

- Verifique se o arquivo "parcial.txt" é gerado corretamente.

**Resultado esperado:** O arquivo "parcial.txt" deve ser gerado corretamente com os votos registrados até o momento.

# TC08: Concluir Votação

**Objetivo:** Verifique se o programa gera o arquivo "resultado.txt" corretamente ao concluir a votação.

## Steps:

1.  Selecione a opção "a) Iniciar voto"
2.  Selecione a opção "a) Entrar com voto"
3.  Realize uma votação
4.  Selecionar a opção "c) Concluir votação".

- Verifique se o arquivo "resultado.txt" é gerado corretamente.

**Resultado esperado:** O arquivo "resultado.txt" deve ser gerado corretamente com os resultados da votação.

# TC09: Continuar votação gravada

**Objetivo:** Verificar se o programa carrega corretamente os votos salvos anteriormente.

## Steps:

Steps:

1. Criar um arquivo "parcial.txt" com votos salvos anteriormente.
2. Executar o programa.
3. Selecionar a opção "b) Continuar votação gravada".

- Verifique se o programa carrega corretamente os votos salvos anteriormente.

**Resultado esperado:** O programa deve carregar os votos realizados anteriormente feitos pelo eleitor.
