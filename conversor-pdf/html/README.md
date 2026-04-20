# 🌐 HTML to PDF - Conversão de HTML para PDF

Este módulo demonstra como converter arquivos HTML para PDF usando `wkhtmltopdf` em C.

## 📝 Descrição

O programa utiliza a ferramenta `wkhtmltopdf` via `system()` para converter um arquivo HTML em documento PDF.

## 📁 Estrutura

```
html/
├── main.c        # Programa de conversão
├── index.html    # Arquivo HTML de exemplo
└── output.pdf    # PDF gerado (saída)
```

## 🔧 Pré-requisitos

### Instalar wkhtmltopdf

**Ubuntu/Debian:**
```bash
sudo apt-get install wkhtmltopdf
```

**Windows:**
Download de: https://wkhtmltopdf.org/downloads.html

**macOS:**
```bash
brew install wkhtmltopdf
```

## 🔧 Como Funciona

### Código Principal

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *htmlFilePath = "index.html";
    const char *pdfFilePath = "output.pdf";

    // Construir comando
    char command[256];
    snprintf(command, sizeof(command), "wkhtmltopdf %s %s", htmlFilePath, pdfFilePath);

    // Executar comando
    int result = system(command);

    if (result == 0) {
        printf("PDF successfully created: %s\n", pdfFilePath);
    } else {
        printf("Failed to create PDF. Error code: %d\n", result);
    }

    return 0;
}
```

## 🚀 Compilação e Execução

```bash
gcc -o html2pdf main.c
./html2pdf
```

## 📤 Exemplo de Uso

**Entrada (index.html):**
```html
<!DOCTYPE html>
<html>
<head>
    <title>Exemplo</title>
</head>
<body>
    <h1>Hello, PDF!</h1>
    <p>Este é um exemplo de conversão.</p>
</body>
</html>
```

**Saída:**
```
PDF successfully created: output.pdf
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `system()` | Execução de comandos externos |
| `snprintf()` | Formatação segura de strings |
| Integração | Uso de ferramentas CLI |
| Retorno de erro | Verificação de sucesso |

## 🔄 Opções Avançadas do wkhtmltopdf

```c
// Com opções adicionais
snprintf(command, sizeof(command), 
    "wkhtmltopdf "
    "--page-size A4 "
    "--margin-top 10mm "
    "--margin-bottom 10mm "
    "--encoding UTF-8 "
    "%s %s", 
    htmlFilePath, pdfFilePath);
```

### Opções Comuns

| Opção | Descrição |
|-------|-----------|
| `--page-size` | Tamanho da página (A4, Letter) |
| `--orientation` | Retrato ou Paisagem |
| `--margin-*` | Margens (top, bottom, left, right) |
| `--encoding` | Codificação do HTML |
| `--grayscale` | PDF em tons de cinza |
| `--lowquality` | Compressão para arquivos menores |

## ⚠️ Cuidados

### Validação de Entrada

```c
// Verificar se arquivo HTML existe
FILE *f = fopen(htmlFilePath, "r");
if (f == NULL) {
    perror("Arquivo HTML não encontrado");
    return 1;
}
fclose(f);
```

### Escapar Caminhos

```c
// Para caminhos com espaços, usar aspas
snprintf(command, sizeof(command), 
    "wkhtmltopdf \"%s\" \"%s\"", 
    htmlFilePath, pdfFilePath);
```

## 🔄 Alternativas

| Biblioteca | Descrição |
|------------|-----------|
| libharu | Biblioteca C nativa para PDF |
| PDFlib | Biblioteca comercial |
| Cairo + Pango | Renderização avançada |

## 📚 Referências

- [wkhtmltopdf Documentation](https://wkhtmltopdf.org/usage/wkhtmltopdf.txt)
- [system() - C Reference](https://en.cppreference.com/w/c/program/system)
