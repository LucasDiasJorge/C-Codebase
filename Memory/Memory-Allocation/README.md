# Projeto de Inicialização de Memória e Impressão de Buffer

Este projeto demonstra como inicializar e imprimir o conteúdo de buffers de memória em linguagem C. Ele utiliza a função `memset` para zerar as áreas de memória e a função `printf` para exibir o conteúdo de variáveis em formato hexadecimal. A ideia é visualizar como os buffers de memória se comportam antes e depois de serem inicializados.

## Descrição do Código

O código consiste em:

1. **Definição de Memória Inicial**:
   - A função `initMem(p)` é um macro que utiliza `memset` para inicializar a memória apontada por `p` com zeros. A ideia é garantir que o conteúdo da memória seja "limpo" antes de usá-la.

2. **Função `printMemory`**:
   - Esta função recebe um nome (para identificação), um ponteiro para a memória (`p`), e o tamanho da memória a ser impressa (`size`). Ela percorre a memória e imprime cada byte no formato hexadecimal.

3. **Variáveis e Inicialização**:
   - O programa define três buffers: `buffer`, `container`, e `total_response`, cada um com 1024 bytes.
   - Antes de qualquer modificação, o conteúdo desses buffers é impresso.
   - Em seguida, as variáveis são inicializadas com zeros usando a função `initMem()`.
   - Após a inicialização, o conteúdo dos buffers é impresso novamente.

4. **Objetivo**:
   - O objetivo principal é mostrar como o conteúdo da memória muda após a inicialização com zeros.

## Como Funciona

### Passo 1: Impressão antes de `initMem()`
Antes da inicialização, o conteúdo dos buffers `buffer`, `container`, e `total_response` é impresso em formato hexadecimal. O conteúdo pode conter dados aleatórios, pois a memória não foi inicializada explicitamente.

### Passo 2: Inicialização com `initMem()`
Os buffers são então inicializados com zeros usando o macro `initMem()`. Isso efetivamente zera todo o conteúdo da memória alocada para as variáveis.

### Passo 3: Impressão depois de `initMem()`
Após a inicialização, os buffers são impressos novamente. Como eles foram zerados, cada byte dos buffers será exibido como `00` em formato hexadecimal.

## Saída Esperada

Ao rodar o programa, a saída deve ser semelhante a:

```
Before initMem()
Buffer (Hexadecimal):
<conteúdo aleatório de 1024 bytes>

Container (Hexadecimal):
<conteúdo aleatório de 1024 bytes>

Total Response (Hexadecimal):
<conteúdo aleatório de 1024 bytes>

After initMem()
Buffer (Hexadecimal):
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ... (1024 bytes de 00)

Container (Hexadecimal):
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ... (1024 bytes de 00)

Total Response (Hexadecimal):
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ... (1024 bytes de 00)
```

### Explicação da Saída:
- **Antes de `initMem()`**: O conteúdo de cada buffer é imprevisível e pode conter valores aleatórios, pois a memória não foi explicitamente inicializada.
- **Após `initMem()`**: Todos os buffers exibem valores `00` em hexadecimal, pois a inicialização com `memset` zerou a memória.

## Como Compilar e Executar

1. **Compilação**:
   Se você estiver utilizando um compilador `gcc`, basta usar o seguinte comando:
   ```
   gcc -o memory_init memory_init.c
   ```

2. **Execução**:
   Para executar o programa compilado:
   ```
   ./memory_init
   ```

## Conclusão

Este projeto oferece uma maneira simples de entender como a memória é manipulada em C, especialmente quando se trata de inicialização e visualização do conteúdo de buffers. O uso do `memset` para garantir que a memória seja limpa antes de usá-la é uma prática comum para evitar problemas de dados lixo.