
### README

# Listador de Arquivos em Diretórios

Este projeto é um programa simples em C que lista todos os arquivos regulares em um ou mais diretórios especificados pelo usuário. Ele utiliza a biblioteca padrão do C para manipulação de diretórios e strings.

---

## Como funciona

1. O programa solicita ao usuário uma lista de diretórios, separados por espaço.
2. Para cada diretório fornecido, o programa tenta abri-lo.
3. Caso o diretório seja acessível, o programa lista todos os arquivos regulares (não inclui subdiretórios ou arquivos especiais).
4. Os resultados são exibidos no formato `<diretório>/<nome_do_arquivo>`.

---

## Pré-requisitos

- Um compilador C (como `gcc`).
- Sistema operacional baseado em Unix para suporte completo a `dirent.h`. Em sistemas Windows, pode ser necessário ajustar a lógica.

---

## Estrutura do Código

### Arquivo principal: `listar_arquivos.c`

- **Função `listarArquivos`:**
  Recebe o caminho de um diretório como argumento, abre o diretório e lista os arquivos regulares.
  
- **Função `main`:**
  Lê a entrada do usuário, separa os diretórios fornecidos por espaços e chama a função `listarArquivos` para cada um deles.

---

## Como compilar

1. Salve o código em um arquivo chamado `listar_arquivos.c`.
2. Compile o programa usando o seguinte comando no terminal:

   ```bash
   gcc listar_arquivos.c -o listar_arquivos
   ```

---

## Como executar

1. Após compilar o programa, execute-o no terminal com o comando:

   ```bash
   ./listar_arquivos
   ```

2. Digite os diretórios que deseja listar, separados por espaço, e pressione Enter. Exemplo:

   ```plaintext
   Digite uma lista de diretórios separados por espaço: /home/user/docs /var/log /tmp
   ```

3. O programa exibirá os arquivos encontrados em cada diretório informado.

---

## Exemplo de saída

Entrada:

```plaintext
Digite uma lista de diretórios separados por espaço: /home/user/docs /var/log
```

Saída:

```plaintext
/home/user/docs/arquivo1.txt
/home/user/docs/arquivo2.pdf
/var/log/syslog
/var/log/kern.log
```

---

## Possíveis Erros

- **Erro ao abrir o diretório**: ocorre quando o caminho fornecido não existe ou o programa não tem permissões para acessá-lo.
  
  Exemplo:
  
  ```plaintext
  Erro ao abrir o diretório /caminho/inexistente
  ```

---

## Melhorias Futuras

- Implementar suporte à listagem de subdiretórios de forma recursiva.
- Adicionar filtros para listar arquivos por tipo ou extensão.
- Melhorar o tratamento de erros e mensagens ao usuário.

---