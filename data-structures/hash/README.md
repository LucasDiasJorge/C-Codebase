# 🔐 Geração de Hash SHA-256 em C

## 📖 Conceito

Este projeto demonstra como **gerar hashes SHA-256** usando a biblioteca OpenSSL em C. Hashes criptográficos são fundamentais em segurança da informação, integridade de dados e criptografia.

## 🎯 Objetivos de Aprendizado

- Entender conceitos de hash criptográfico
- Usar a biblioteca OpenSSL em C
- Implementar função de hash SHA-256
- Compreender representação hexadecimal
- Aprender sobre integridade de dados

## 🔧 Compilação

```bash
gcc main.c -o executable -lssl -lcrypto
```

### Dependências: OpenSSL
```bash
# Ubuntu/Debian
sudo apt-get install libssl-dev

# Fedora/RHEL
sudo dnf install openssl-devel

# macOS
brew install openssl
```

## 💻 Implementação

O programa utiliza a biblioteca OpenSSL para:
1. **Inicializar** contexto SHA-256
2. **Processar** dados de entrada
3. **Finalizar** e obter hash
4. **Exibir** resultado em hexadecimal

### Fluxo Principal:
```c
SHA256_CTX sha256;                              // Contexto
SHA256_Init(&sha256);                           // Inicializar
SHA256_Update(&sha256, input, strlen(input));   // Processar
SHA256_Final(hash, &sha256);                    // Finalizar
```

## 🚀 Execução

```bash
./executable
# Digite uma string: Hello World
# Hash gerado: a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e
```

## 🔍 O que é SHA-256?

- **SHA**: Secure Hash Algorithm
- **256**: Produz hash de 256 bits (32 bytes)
- **Unidirecional**: Impossível reverter
- **Determinístico**: Mesmo input = mesmo hash
- **Collision-resistant**: Extremamente seguro

## 🎯 Aplicações Práticas

- **Blockchain**: Bitcoin, Ethereum
- **Verificação de Integridade**: Checksums
- **Autenticação**: Hash de senhas (com salt)
- **Digital Signatures**: Assinatura de documentos

## ⚡ Conceitos Demonstrados

- **Bibliotecas Externas**: Linkagem com OpenSSL
- **Criptografia**: Algoritmos de hash
- **Hexadecimal**: Representação de dados binários
- **String Processing**: Manipulação de entrada
- **Security**: Fundamentos de segurança da informação

Este exemplo demonstra conceitos fundamentais de criptografia e serve como base para aplicações de segurança mais complexas.