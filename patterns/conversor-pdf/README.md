# 📄 Conversor PDF - Conversão de Documentos

Este módulo demonstra como converter documentos para PDF usando LibreOffice via linha de comando em C.

## 📝 Descrição

O programa utiliza o LibreOffice em modo headless (sem interface gráfica) para converter arquivos de planilhas e documentos para o formato PDF.

## 📁 Estrutura

```
Conversor-pdf/
├── main.c          # Código do conversor
├── file.xlms       # Arquivo de exemplo para conversão
└── html/
    ├── index.html  # Página HTML de exemplo
    └── main.c      # Conversor para HTML
```

## 🔧 Pré-requisitos

### Instalação do LibreOffice

**Ubuntu/Debian:**
```bash
sudo apt-get install libreoffice
```

**Fedora/RHEL:**
```bash
sudo dnf install libreoffice
```

**Windows:**
- Baixe e instale do [site oficial](https://www.libreoffice.org/download/download/)
- Adicione ao PATH: `C:\Program Files\LibreOffice\program\`

## 🔧 Como Funciona

### Função `convert_to_pdf()`

```c
void convert_to_pdf(const char *input_file) {
    char command[256];
    snprintf(command, sizeof(command), 
             "libreoffice --headless --convert-to pdf \"%s\"", 
             input_file);
    int result = system(command);
    // ...
}
```

**Parâmetros do LibreOffice:**
- `--headless`: Executa sem interface gráfica
- `--convert-to pdf`: Especifica o formato de saída
- O arquivo PDF é criado no mesmo diretório

## 🚀 Compilação e Execução

```bash
gcc -o conversor main.c
./conversor
```

## 📤 Saída Esperada

```
File 'file.xlms' converted to PDF successfully.
```

## 📊 Formatos Suportados

| Entrada | Extensões |
|---------|-----------|
| Documentos | .doc, .docx, .odt, .rtf |
| Planilhas | .xls, .xlsx, .ods, .csv |
| Apresentações | .ppt, .pptx, .odp |
| Imagens | .jpg, .png, .bmp |
| HTML | .html, .htm |

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `system()` | Execução de comandos externos |
| `snprintf()` | Formatação segura de strings |
| Automação | Processamento em lote |

## 🔄 Melhorias Possíveis

1. **Conversão em lote:**
```c
void convert_directory(const char *dir_path) {
    // Iterar sobre todos os arquivos
}
```

2. **Especificar diretório de saída:**
```bash
libreoffice --headless --convert-to pdf --outdir /output/ input.xlsx
```

3. **Tratamento de erros robusto:**
```c
if (access(input_file, F_OK) != 0) {
    fprintf(stderr, "Arquivo não encontrado: %s\n", input_file);
    return -1;
}
```

## ⚠️ Notas

- O arquivo `file.xlms` deveria ser `file.xlsx` (possível erro de digitação)
- LibreOffice precisa estar instalado e no PATH
- A conversão pode demorar para arquivos grandes

## 📚 Referências

- [LibreOffice Command Line](https://help.libreoffice.org/latest/en-US/text/shared/guide/start_parameters.html)
- [Batch Conversion](https://wiki.documentfoundation.org/Converting_files)
