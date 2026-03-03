# Debugging Utility in C

Este projeto é um exemplo simples de como implementar funcionalidades de debug em programas em C. Ele registra mensagens no console dependendo do modo `--debug` ativado ou desativado.

## Funcionalidades

- **Modo Debug:** Exibe logs detalhados sobre a execução do programa.
- **Inicialização:** Mostra informações de compilação, como o arquivo, data, hora e linha.
- **Log Personalizado:** Permite registrar mensagens personalizadas com timestamp.

## Estrutura do Código

### Principais Funções

1. **`debugging(char *message)`**
   - Registra uma mensagem no console, incluindo a data, hora e a mensagem de log.
   - É executada apenas se o modo debug estiver ativado.

2. **`init()`**
   - Exibe informações de inicialização (como o nome do arquivo e a data de compilação) ao iniciar o programa.

3. **`main(int argc, char *argv[])`**
   - Gerencia os argumentos da linha de comando e inicia o programa.
   - Ativa o modo debug se o argumento `--debug` for fornecido.

## Como Usar

1. **Compilar o programa:**
   ```bash
   gcc -o debugging_program main.c
   ```

2. **Executar o programa:**
   - Modo normal:
     ```bash
     ./debugging_program
     ```
   - Modo debug:
     ```bash
     ./debugging_program --debug
     ```

3. **Interagir com o programa:**
   - O programa aguarda que você pressione `Enter` para finalizar.

## Exemplos de Saída

### Modo Normal
```plaintext
# Nenhuma mensagem de log será exibida.
```

### Modo Debug
```plaintext
=====Starting=====
File: main.c
Date: Jan 05 2025
Time: 10:00:00
Line: 25
ANSI: 1
=====Starting=====

	Log (Jan 05 2025): Press "Enter" to stop;

	Log (Jan 05 2025): Stopping;

	Log (Jan 05 2025): Exiting;
```

## Dependências

Nenhuma biblioteca adicional é necessária além das bibliotecas padrão do C.

## Melhorias Futuras

- Adicionar suporte para diferentes níveis de log (e.g., `INFO`, `WARN`, `ERROR`).
- Salvar logs em um arquivo.
- Melhorar o formato de data/hora para facilitar a leitura.