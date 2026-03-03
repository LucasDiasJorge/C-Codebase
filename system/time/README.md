# Projeto: Conversão de Data ISO 8601 para Timestamp com Milissegundos

Este projeto tem como objetivo fornecer uma função para converter uma string de data no formato ISO 8601 para um timestamp Unix (em segundos) com o tratamento de milissegundos.

## Funcionalidades

1. **Conversão de Data ISO 8601 para Timestamp**: O projeto converte uma string ISO 8601 (`YYYY-MM-DDTHH:MM:SS.sss`) para um timestamp Unix (segundos desde a época Unix). 
2. **Trata a parte dos milissegundos**: A função é capaz de capturar milissegundos da string ISO 8601 e integrá-los ao timestamp.
3. **Exibição da Hora Atual e Data Atual**: Exibe a hora e data do sistema no momento da execução do programa.

## Requisitos

- Sistema operacional que suporte a biblioteca padrão do C.
- Compilador C compatível com as funções de manipulação de data e hora.

## Estrutura do Projeto

- **`convertToTimestamp`**: Função que converte uma string ISO 8601 para um timestamp Unix.
- **`time_now`**: Função que retorna a hora atual do sistema no formato `HH:MM:SS`.
- **`date_today`**: Função que retorna a data de hoje no formato `Mmm dd yyyy`.

## Como Usar

### Compilação e Execução

1. Clone o repositório ou baixe o código-fonte.
2. Compile o código com um compilador C (por exemplo, GCC):

   ```bash
   gcc -o timestamp_converter timestamp_converter.c
   ```

3. Execute o programa:

   ```bash
   ./timestamp_converter
   ```

### Exemplo de Saída

A saída exibirá o timestamp Unix correspondente à string ISO 8601 fornecida, bem como a hora e data atuais:

```bash
Timestamp: 1705441691
Time Now: 19:10:15
Date Today: Dec 1 2024
```

## Detalhes Técnicos

- O código usa a função `strptime` para analisar a string ISO 8601 e a estrutura `tm` para armazenar os componentes de data e hora.
- Os milissegundos, se presentes, são extraídos e convertidos em segundos, e somados ao valor de `tm_sec`.
- O timestamp final é calculado usando a função `mktime`.

## Possíveis Melhorias

- **Precisão dos Milissegundos**: O código atualmente ignora a parte dos microsegundos (parte após os milissegundos), o que poderia ser uma melhoria para lidar com maior precisão.
- **Tratamento de Fuso Horário**: O código não considera fusos horários e assume que o horário fornecido está no formato UTC.
- **Validação de Entradas**: Melhorias no tratamento de erros e validação de entradas podem ser feitas.