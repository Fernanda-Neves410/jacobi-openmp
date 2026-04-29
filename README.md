# jacobi-openmp

Este projeto implementa o método iterativo de Jacobi nas versões sequencial e paralela, utilizando OpenMP para análise de desempenho em arquiteturas de memória compartilhada.

O trabalho tem como objetivo explorar paralelismo de dados, sincronização entre threads, análise de desempenho (tempo, speedup e eficiência) e limitações do paralelismo.

## Funcionalidades

* Versão sequencial do método de Jacobi
* Versão paralela utilizando OpenMP
* Execução com diferentes números de threads
* Cálculo de tempo de execução, speedup e eficiência
* Critério de convergência baseado no erro máximo

## Pré-requisitos

Para compilar e executar o projeto, é necessário:

* Compilador C++ com suporte a OpenMP (g++)
* Sistema operacional Linux, Windows (MinGW) ou WSL

## Compilação

Para compilar o projeto:

```
g++ -Wall -Wextra -O2 -fopenmp src/*.cpp -o main
```

No Windows:

```
g++ -Wall -Wextra -O2 -fopenmp src/*.cpp -o main.exe
```

## Execução

No Linux:

```
./main
```

No Windows:

```
main.exe
```

## Parâmetros

Os parâmetros podem ser alterados diretamente no arquivo main.cpp:

* Tamanho da matriz (n): define a dimensão do sistema linear
* Número máximo de iterações (max_iter): define o limite de iterações
* Número de threads:

```
vector<int> num_threads_teste = {1, 2, 4, 6, 8, 12};
```

## Detalhes da implementação

A matriz utilizada é diagonalmente dominante, garantindo a convergência do método.

A paralelização ocorre no laço principal de cálculo do vetor solução, utilizando a diretiva:

```
#pragma omp parallel for reduction(max:erro_max)
```

O escalonamento adotado é static e o uso de reduction evita condições de corrida no cálculo do erro.

## Saída do programa

O programa apresenta:

* tempo de execução sequencial
* tempo de execução paralela
* speedup
* eficiência
* número de iterações até convergência

## Observações

O desempenho melhora até um certo número de threads, dependendo do hardware.

Para matrizes menores, o overhead da paralelização pode reduzir os ganhos.

A paralelização não altera o resultado numérico, apenas o tempo de execução.

## Autores

Fernanda das Neves Merqueades Santos
Kauê Peixoto Fernandes
