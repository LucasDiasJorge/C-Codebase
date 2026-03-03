# Guia de Uso do GCC e Técnicas de Otimização

Este guia irá introduzir você ao uso do GCC (GNU Compiler Collection) e a algumas técnicas de otimização comuns como `-O2`.

## Sumário

- [Introdução ao GCC](#introdução-ao-gcc)
- [Instalação](#instalação)
- [Compilação Básica](#compilação-básica)
- [Níveis de Otimização](#níveis-de-otimização)
  - [-O0](#-O0)
  - [-O1](#-O1)
  - [-O2](#-O2)
  - [-O3](#-O3)
  - [-Os](#-Os)
- [Outras Opções Úteis](#outras-opções-úteis)
- [Referências](#referências)

## Introdução ao GCC

O GCC é um compilador amplamente utilizado para compilar código C, C++, e outras linguagens. Ele é conhecido por sua robustez e pelas várias opções de otimização que oferece.

## Instalação

Para instalar o GCC no seu sistema, você pode usar o gerenciador de pacotes da sua distribuição Linux. Por exemplo:

### Ubuntu/Debian

```sh
sudo apt-get update
sudo apt-get install gcc
```

### Fedora

```sh
sudo dnf install gcc
```

## Compilação básica

Para compilar um programa em C com o GCC, use o seguinte comando:

```sh
gcc -o meu_programa meu_programa.c
```

Aqui, -o especifica o nome do arquivo executável que será gerado (meu_programa), e meu_programa.c é o arquivo fonte a ser compilado.

## Níveis de Otimização

O GCC oferece vários níveis de otimização que podem ser ativados usando flags específicas:

### -O0

Este é o nível de otimização padrão. Nenhuma otimização é realizada, o que pode ser útil para depuração.

```sh
gcc -O0 -o meu_programa meu_programa.c
```

### -O1

Habilita otimizações básicas que não aumentam significativamente o tempo de compilação.

```sh
gcc -O1 -o meu_programa meu_programa.c
```

### -O2

Habilita um conjunto mais abrangente de otimizações que melhoram o desempenho sem aumentar muito o tempo de compilação.

```sh
gcc -O2 -o meu_programa meu_programa.c
```

### -O3

Inclui todas as otimizações do nível -O2 e adiciona outras que podem aumentar ainda mais o desempenho, mas podem também aumentar o tempo de compilação e o tamanho do executável.

```sh
gcc -O3 -o meu_programa meu_programa.c
```

### -Os

Otimiza o código para reduzir o tamanho do executável, útil para sistemas com recursos limitados.

```sh
gcc -Os -o meu_programa meu_programa.c
```

## Outras Opções Úteis

Além das opções de otimização, o GCC oferece várias outras flags úteis:

- '-g': Inclui informações de depuração no executável.

- '-Wall': Habilita a maioria dos avisos de compilação para ajudar a identificar possíveis problemas no código.

- '-Werror': Trata avisos como erros, forçando a correção de todos os avisos antes da compilação.

- '-w': Desabilita todos os avisos de compilação.

### Documentação GCC
Doc ref.: https://gcc.gnu.org/onlinedocs/gcc-14.1.0/gcc/