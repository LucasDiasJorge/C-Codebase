### Projeto: Demonstrativo de Limpeza de Memória com `initMem`

---

#### Descrição

Este projeto é uma aplicação simples em C que demonstra o uso de uma macro personalizada chamada `initMem`. A macro utiliza a função `memset` para inicializar (ou limpar) blocos de memória, atribuindo o valor zero a cada byte de arrays alocados. 

O programa exibe o estado da memória de três buffers antes e depois da chamada de `initMem`, mostrando os valores armazenados em formato hexadecimal.

---

#### Objetivo

- Demonstrar como inicializar áreas de memória usando a função padrão `memset` encapsulada em uma macro (`initMem`).
- Ajudar a entender a representação dos dados em memória antes e depois da inicialização.

---

#### Funcionalidades

1. **Visualização da Memória**  
   A função `printMemory` imprime o conteúdo de um bloco de memória em formato hexadecimal.

2. **Macro `initMem`**  
   Define um atalho para a função `memset` que inicializa qualquer buffer passado com zeros.

3. **Buffers Demonstrativos**  
   Três buffers (`buffer`, `container`, `total_response`) são criados, preenchidos com valores não definidos, e depois inicializados.

---

#### Estrutura do Código

1. **Macros**  
   ```c
   #define initMem(p) memset((p), 0, sizeof(p))
   ```
   Cria um atalho para inicializar blocos de memória com zeros.

2. **Função Auxiliar**  
   ```c
   void printMemory(const char *name, const char *p, size_t size);
   ```
   Função que recebe um nome de buffer, seu endereço e tamanho, imprimindo os valores em memória no formato hexadecimal.

3. **Main**  
   - Criação de buffers.
   - Exibição do estado da memória antes e depois da inicialização.
   - Uso da macro `initMem`.

---

#### Exemplo de Saída

A execução deste programa resultará em uma saída semelhante a esta:

```
Before initMem()
Buffer (Hexadecimal):
XX XX XX XX ...  // Valores não inicializados (indefinidos)
Container (Hexadecimal):
XX XX XX XX ...  // Valores não inicializados (indefinidos)
Total Response (Hexadecimal):
XX XX XX XX ...  // Valores não inicializados (indefinidos)

After initMem()
Buffer (Hexadecimal):
00 00 00 00 ...  // Valores zerados
Container (Hexadecimal):
00 00 00 00 ...  // Valores zerados
Total Response (Hexadecimal):
00 00 00 00 ...  // Valores zerados
```

---

#### Como Executar

1. **Compilar**  
   Use um compilador como `gcc` para compilar o código:
   ```bash
   gcc -o memory_demo memory_demo.c
   ```

2. **Executar**  
   Execute o programa gerado:
   ```bash
   ./memory_demo
   ```

---

#### Requisitos

- Compilador compatível com C (ex.: GCC ou Clang).
- Sistema com suporte para execução de binários C.

---

#### Possíveis Expansões

- Adicionar opções para inicializar a memória com valores diferentes de zero.
- Ampliar a função `printMemory` para exibir valores no formato ASCII.
- Implementar testes automatizados para verificar o comportamento da macro `initMem`.