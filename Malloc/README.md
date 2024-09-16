# Implementação Personalizada de `malloc` e `free` em C

Este projeto implementa uma versão simplificada das funções `malloc` e `free` em C, gerenciando a alocação dinâmica de memória no heap sem depender das funções padrão fornecidas pela linguagem.

## Visão Geral

- **`my_malloc`**: Aloca dinamicamente um bloco de memória do heap, similar à função `malloc` padrão. Ele busca blocos livres na lista livre (`freeList`) e, caso não haja blocos disponíveis, expande o heap usando a função `sbrk`.
- **`my_free`**: Libera a memória alocada, marcando o bloco como livre para reutilização futura. A funcionalidade de "coalescing" (junção de blocos adjacentes livres) pode ser implementada para melhorar o gerenciamento de memória.

## Funcionalidades

- Alocação de blocos de memória com base no tamanho solicitado.
- Manutenção de uma lista de blocos livres para reutilização eficiente.
- Expansão do heap quando necessário usando `sbrk`.
- Liberação de blocos de memória para reutilização.

## Estrutura do Código

### `Block`

Cada bloco de memória alocado contém as seguintes informações:
- **`size`**: Tamanho do bloco alocado.
- **`free`**: Indicador de se o bloco está livre ou ocupado.
- **`next`**: Ponteiro para o próximo bloco na lista de blocos.

### Funções

1. **`my_malloc(size_t size)`**: Aloca um bloco de memória do tamanho especificado.
    - Primeiro, procura por blocos livres na lista livre.
    - Se nenhum bloco livre estiver disponível, a função expande o heap e cria um novo bloco.
    - Retorna um ponteiro para o espaço de dados utilizável.

2. **`my_free(void *ptr)`**: Libera o bloco de memória referenciado por `ptr`.
    - Marca o bloco como livre, permitindo que ele seja reutilizado em futuras chamadas de alocação.

3. **`findFreeBlock(size_t size)`**: Procura por um bloco livre com tamanho suficiente na lista livre.
    - Retorna o primeiro bloco livre que pode ser reutilizado ou `NULL` se não houver blocos disponíveis.

4. **`extendHeap(size_t size)`**: Expande o heap e aloca um novo bloco de memória quando nenhum bloco livre é encontrado.
    - Usa a função `sbrk` para solicitar mais memória ao sistema.

## Compilação e Execução

### Compilação

Compile o código com o seguinte comando:

```bash
gcc -o custom_malloc main.c
```

### Execução

Após a compilação, você pode executar o programa da seguinte forma:

```bash
./custom_malloc
```

Se o código estiver correto, ele alocará espaço para 10 inteiros, preencherá o array com números múltiplos de 2 e imprimirá os resultados.

### Exemplo de Saída

```bash
0 2 4 6 8 10 12 14 16 18
```

## Limitações

- O código não implementa a lógica de "coalescing", que uniria blocos adjacentes livres para evitar fragmentação.
- Não há gerenciamento de blocos pequenos ou realocação eficiente, como em implementações mais sofisticadas de `malloc`.
- A função `my_malloc` não possui a capacidade de redimensionar blocos já alocados, como `realloc`.

## Próximos Passos

- **Coalescing**: Implementar a lógica de coalescência para combinar blocos de memória adjacentes que estão livres.
- **Divisão de Blocos**: Implementar a capacidade de dividir um bloco grande em dois menores quando apenas uma parte do bloco é necessária.
- **`realloc`**: Adicionar uma função `my_realloc` para redimensionar blocos de memória já alocados.