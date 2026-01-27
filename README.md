# 📚 C Programming Educational Codebase

Este repositório contém uma coleção educacional abrangente de programas e exemplos em linguagem C, cobrindo conceitos fundamentais e avançados da programação em C. O código está organizado didaticamente em diferentes diretórios, cada um focando em tópicos específicos como gerenciamento de memória, manipulação de arquivos, programação de rede, estruturas de dados e muito mais.

## 🎯 Objetivo

Este projeto foi desenvolvido com propósito educacional para:
- Demonstrar conceitos fundamentais da linguagem C
- Apresentar técnicas avançadas de programação
- Fornecer exemplos práticos e funcionais
- Servir como referência para estudantes e desenvolvedores

## 📖 Como Usar Este Repositório

Cada diretório contém:
- Código fonte comentado
- README específico explicando os conceitos
- Exemplos práticos de uso
- Instruções de compilação

## 🗂️ Estrutura do Projeto

### 🔰 **Beginner** - Conceitos Básicos
- **Inverter Número**: Algoritmos básicos de manipulação numérica
- **Goto**: Uso do comando goto (com explicações sobre quando evitar)
- **Strings**: Manipulação básica de strings

### 🤖 **Automatus** - Autômatos Finitos (DFA)
- Exemplo de autômato finito determinístico para reconhecer tokens/palavras (por exemplo: `for`, `float`, `char`)

### 🧠 **Memory** - Gerenciamento de Memória
- **Malloc**: Implementação personalizada de alocador de memória
- **Memory-Allocation**: Técnicas de alocação dinâmica
- **Memory-pool**: Pool de memória para otimização
- **Memory-usage**: Monitoramento de uso de memória
- **Pointers**: Manipulação avançada de ponteiros

### 🌐 **Network** - Programação de Rede
- **Socket-request**: Cliente socket básico
- **Handle-Client**: Servidor para múltiplos clientes
- **HTTP**: Manipulação de protocolos HTTP
- **Mac-Address**: Obtenção de endereço MAC

### 📁 **Files** - Manipulação de Arquivos
- **Create**: Criação de arquivos
- **Delete**: Remoção de arquivos
- **Reader**: Leitura de diferentes tipos de arquivo
- **Properties**: Manipulação de arquivos de configuração
- **Stats**: Estatísticas de arquivos

### ⚙️ **Assembly** - Interface C/Assembly
- **Method-1**: Integração básica C/Assembly
- **Method-2**: Técnicas avançadas de integração

### 🏗️ **Design Patterns** - Padrões de Projeto
- **Observer**: Implementação do padrão Observer em C

### 🔧 **Advanced Topics** - Tópicos Avançados
- **Garbage-Collector**: Coletor de lixo personalizado
- **Hash**: Implementação de tabelas hash
- **Union**: Uso avançado de unions
- **Enum**: Enumerações e suas aplicações

### 🛠️ **Utilities** - Utilitários
- **Debugging**: Técnicas de debug
- **Preprocessors**: Uso avançado de preprocessadores
- **GCC**: Otimizações do compilador
- **Optimization-Tips**: Dicas de otimização

### 🎨 **Miscellaneous** - Diversos
- **Colored-Output**: Saída colorida no terminal
- **Calculator**: Implementação de calculadora
- **JSON**: Manipulação de JSON em C
- **Time**: Manipulação de tempo e timestamps

## 📋 Índice de Navegação Rápida

### 🔰 Para Iniciantes
- **[Beginner/](Beginner/)** - Conceitos básicos e primeiros programas
  - [Inverter Número](Beginner/inverter-numero-README.md) - Algoritmos matemáticos básicos
  - [Goto](Beginner/Goto/) - Comando goto e suas limitações
  - [Strings](Beginner/Strings/) - Manipulação básica de strings

### 🤖 Autômatos
- **[Automatus/](Automatus/)** - Autômato finito determinístico (DFA) em C

### 🧠 Gerenciamento de Memória
- **[Memory/](Memory/)** - Técnicas avançadas de gerenciamento de memória
  - [Malloc Personalizado](Memory/Malloc/) - Implementação de alocador customizado
  - [Memory Pool](Memory/Memory-pool/) - Pool de memória para performance
  - [Ponteiros Avançados](Memory/Pointers/) - Manipulação complexa de ponteiros

### 🌐 Programação de Rede
- **[Network/](Network/)** - Sockets e comunicação de rede
  - [Socket Client](Network/socket-request/) - Cliente TCP com HTTP
  - [Servidor Multi-cliente](Network/Handle-Client/) - Concorrência em servidores
  - [HTTP Headers](Network/http-header/) - Manipulação de protocolos web

### 🔧 Assembly e Baixo Nível
- **[Assembly/](Assembly/)** - Integração C/Assembly
  - [Inline Assembly](Assembly/method-1/) - Assembly embutido no C
  - [Assembly Externo](Assembly/method-2/) - Funções Assembly separadas

### 📁 Manipulação de Arquivos
- **[Files/](Files/)** - I/O e sistema de arquivos
  - [Criação de Arquivos](Files/Create/) - Criação e escrita de arquivos
  - [Leitura de Arquivos](Files/Reader/) - Técnicas de leitura
  - [Propriedades](Files/Properties/) - Metadados e atributos

### 🎯 Padrões de Projeto
- **[Observer/](Observer/)** - Padrão Observer em C
- **[Shared-Hashtable/](Shared-Hashtable/)** - Hashtable compartilhada
- **[Enum/](Enum/)** - Enumerações avançadas
- **[Union/](Union/)** - Unions e otimização de memória

### 🔐 Criptografia e Hash
- **[Hash/](Hash/)** - Algoritmos de hash SHA-256
- **[Garbage-Collector/](Garbage-Collector/)** - Coletor de lixo personalizado

### 🛠️ Ferramentas e Utilitários
- **[Debugging/](Debugging/)** - Técnicas de debug
- **[GCC/](GCC/)** - Otimizações do compilador
- **[Preprocessors/](Preprocessors/)** - Uso avançado de preprocessadores
- **[Optimization-Tips/](Optimization-Tips/)** - Dicas de otimização

### 🎨 Projetos Diversos
- **[Colored-Output/](Colored-Output/)** - Saída colorida no terminal
- **[JSON/](Json/)** - Manipulação de JSON em C
- **[Time/](Time/)** - Manipulação de tempo e timestamps
- **[Miscellaneous/](Miscellaneous/)** - Projetos variados e utilitários

## 🚀 Começando

### Pré-requisitos
```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# Fedora/RHEL
sudo dnf groupinstall "Development Tools"

# Windows (MinGW)
# Instale o MinGW ou use WSL
```

### Compilação Básica
```bash
cd [diretório-do-exemplo]
gcc -o programa main.c
./programa
```

### Compilação com Debugging
```bash
gcc -g -Wall -Wextra -o programa main.c
gdb ./programa
```

## 📚 Conceitos Abordados

| Categoria | Conceitos | Dificuldade |
|-----------|-----------|-------------|
| **Básicos** | Variáveis, loops, condicionais | ⭐ |
| **Intermediário** | Ponteiros, structs, arrays | ⭐⭐ |
| **Avançado** | Gerenciamento de memória, networking | ⭐⭐⭐ |
| **Expert** | Assembly, garbage collection, otimizações | ⭐⭐⭐⭐ |

## 🤝 Contribuindo

1. Faça fork do projeto
2. Crie uma branch para sua feature
3. Commit suas mudanças
4. Push para a branch
5. Abra um Pull Request

## 📄 Licença

Este projeto é open source e está disponível sob a licença MIT.

## 📞 Contato

Para dúvidas ou sugestões, abra uma issue no repositório.

---

💡 **Dica**: Comece pelos exemplos em `Beginner/` e avance gradualmente para os tópicos mais complexos!