# Fundamentos de Redes de Computadores

## Trabalho 1 part 1

Trata-se de uma simulação do modelo de Referência OSI pela construção de um protótipo de camada de enlace de dados. É uma implementação contendo protocolo em modo simplex, diálogo ponto-a-ponto, stop-and-wait e orientado à conexão.

### Executar

Para utilizar esse projeto basta clonar esse [repositorio](https://github.com/giovannabbottino/frc.git) e rodar os seguintes comandos. Deve-se ter CPP instalado. Não esqueça de entrar na pasta trabalho_1_part1.

Para buildar de o seguinte comando:
~~~
$ make all
~~~

Para rodar, lembre-se de colocar o valor da pdu, do seguinte modo:
~~~
$ make run pdu=VALOR
~~~

Esse VALOR deve ser um número inteiro.

## Trabalho 1 part 2

Trata-se de uma simulação do modelo de Referência OSI pela construção de um protótipo de camada de enlace de dados. É uma implementação contendo protocolo em modo full-duplex, diálogo ponto-a-ponto, stop-and-wait e orientado à conexão.

### Executar

Para utilizar esse projeto basta clonar esse [repositorio](https://github.com/giovannabbottino/frc.git) e rodar os seguintes comandos. Deve-se ter CPP instalado. Não esqueça de entrar na pasta trabalho_1_part2.

Para buildar de o seguinte comando:
~~~
$ make all
~~~

Para rodar, lembre-se de colocar o valor da pdu. Além disso, recomendamos abrir em dois terminais diferentes:
~~~
$ bin/server
$ bin/client $(pdu)
~~~

Esse VALOR deve ser um número inteiro.
