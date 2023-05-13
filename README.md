# SOLVE_THIS: Resolvedor de Expressão Numérica
SOLVE_THIS é um programa que recebe expressões matemáticas em notação infixa ou posfixa e possibilita tanto a sua solução quanto a conversão entre as duas notações.
Esse programa é o produto de uma atividade prática da disciplina de Estruturas de Dados do [Departamento de Ciência da Computação da UFMG](https://dcc.ufmg.br/).

## Sumário
- [Compilação](#Compilação)
- [Execução](#Execução)
- [Documentação](#Documentação)

# Compilação
SOLVE_THIS pode ser compilado com o seguinte comando:

``` sh
$ make build
```

# Execução
Para executar o programa, há duas opções:
- Execução de forma interativa. Para isso, execute o comando:

``` sh
$ make run_interactive
```

Dessa maneira, o programa iniciará. Digite ``HELP`` e pressione ``enter`` para visualizar a lista de comandos possíveis.

- Execução com a passagem de um arquivo que contém a sequência de comandos desejados

``` sh
$ make run < caminho/do/arquivo
```

OBS.: O arquivo deve estar estruturado de forma que haja um comando por linha. Veja alguns exemplos em [tests/inputs](https://github.com/luk3rr/SOLVE_THIS/tree/main/tests/inputs).

# Documentação
A primeira versão da documentação bem como o enunciado desse trabalho pode ser lida [aqui](https://github.com/luk3rr/SOLVE_THIS/tree/main/docs).
