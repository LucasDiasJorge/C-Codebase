# Projeto: Demonstração de Cores e Estilos ANSI no Terminal

Este projeto demonstra como usar códigos de escape ANSI em C para exibir texto colorido, aplicar estilos (negrito, itálico, sublinhado) e alterar a cor de fundo no terminal.

## Descrição

O código fonte utiliza **códigos ANSI** para controlar a aparência do texto impresso no terminal. O programa exibe exemplos de cores de texto, estilos e cores de fundo, permitindo que você veja como cada código afeta a saída no terminal.

## Como funciona

Os códigos ANSI são sequências especiais que alteram o estilo do texto no terminal. Eles são definidos como constantes no início do programa. Durante a execução, diferentes chamadas de `printf` utilizam esses códigos para imprimir texto com várias formatações.

### Cores de Texto:
- Preto
- Vermelho
- Verde
- Amarelo
- Azul
- Magenta
- Ciano
- Branco

### Estilos de Texto:
- Negrito
- Itálico
- Sublinhado

### Cores de Fundo:
- Preto
- Vermelho
- Verde
- Amarelo
- Azul
- Magenta
- Ciano
- Branco

## Como Compilar e Executar

1. **Clone o repositório** (se aplicável) ou copie os arquivos do projeto.
2. Compile o código utilizando um compilador C, como o `gcc`:
   ```bash
   gcc -o demo demo.c
   ```
3. Execute o binário gerado:
   ```bash
   ./demo
   ```

## Saída Esperada

A saída será uma série de linhas demonstrando o texto em várias cores, estilos e cores de fundo. Por exemplo:

```
## Print color ##
=> This text is BLACK!
=> This text is RED!
=> This text is GREEN!
=> This text is YELLOW!
...

## Print style ##
=> This text is BOLD!
=> This text is ITALIC!
=> This text is UNDERLINE!

## Print background ##
=> This BG is BLACK!
=> This BG is RED!
=> This BG is GREEN!
=> This BG is YELLOW!
...
```

## Requisitos

- Um compilador C (por exemplo, `gcc`)
- Um terminal compatível com sequências ANSI (como o terminal padrão do Linux ou MacOS)