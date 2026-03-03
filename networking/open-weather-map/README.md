# ☁️ Open Weather Map - Cliente de API de Clima

Este módulo demonstra como consumir a API do OpenWeatherMap usando libcurl em C.

## 📝 Descrição

O programa faz requisições HTTP à API do OpenWeatherMap para obter dados meteorológicos em tempo real de uma cidade específica.

## 📁 Estrutura

```
Open-Weather-Map/
└── main.c      # Cliente da API de clima
```

## 🔧 Pré-requisitos

### 1. Instalar libcurl

**Ubuntu/Debian:**
```bash
sudo apt-get install libcurl4-openssl-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install libcurl-devel
```

**Windows (MinGW):**
```bash
pacman -S mingw-w64-x86_64-curl
```

### 2. Obter API Key

1. Crie uma conta em [OpenWeatherMap](https://openweathermap.org/api)
2. Obtenha sua API Key gratuita
3. Substitua `"sua_chave_api_aqui"` no código

## 🔧 Como Funciona

### Estrutura de Resposta
```c
struct string {
    char *ptr;
    size_t len;
};
```
Armazena a resposta HTTP dinamicamente.

### Callback de Escrita
```c
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
    // Realoca memória conforme dados chegam
    // Concatena novos dados à string
}
```

### Fluxo Principal
1. Inicializa libcurl
2. Configura URL com cidade e API key
3. Faz requisição GET
4. Processa resposta JSON
5. Limpa recursos

## 🚀 Compilação e Execução

```bash
gcc -o weather main.c -lcurl
./weather
```

## 📤 Saída Esperada (JSON)

```json
{
  "coord": {"lon": -42.53, "lat": -22.28},
  "weather": [{"main": "Clouds", "description": "scattered clouds"}],
  "main": {
    "temp": 22.5,
    "feels_like": 22.8,
    "humidity": 78
  },
  "name": "Nova Friburgo"
}
```

## ⚙️ Configuração

| Constante | Descrição | Valor Padrão |
|-----------|-----------|--------------|
| `API_KEY` | Chave de acesso à API | `"sua_chave_api_aqui"` |
| `CITY` | Cidade para consulta | `"Nova Friburgo"` |
| `URL_FORMAT` | Template da URL | URL da API |

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| libcurl | Biblioteca para requisições HTTP |
| Callbacks | Funções de callback para processar dados |
| Alocação Dinâmica | `malloc()` e `realloc()` |
| APIs REST | Consumo de APIs web |

## 🔒 Segurança

⚠️ **IMPORTANTE:** Nunca commite API keys no código!

**Solução recomendada - Variáveis de ambiente:**
```c
const char *api_key = getenv("OPENWEATHER_API_KEY");
if (api_key == NULL) {
    fprintf(stderr, "API key não configurada!\n");
    return 1;
}
```

**Configurar variável:**
```bash
export OPENWEATHER_API_KEY="sua_chave_aqui"
```

## 🔄 Possíveis Extensões

1. **Parser JSON:** Usar cJSON ou json-c para extrair dados específicos
2. **Cache:** Armazenar resultados para evitar requisições repetidas
3. **Múltiplas cidades:** Consultar várias cidades em sequência
4. **Previsão:** Usar endpoint de forecast para previsão de 5 dias

## 📊 Endpoints Úteis

| Endpoint | Descrição |
|----------|-----------|
| `/weather` | Clima atual |
| `/forecast` | Previsão 5 dias |
| `/air_pollution` | Qualidade do ar |

## 📚 Referências

- [OpenWeatherMap API Docs](https://openweathermap.org/api)
- [libcurl Tutorial](https://curl.se/libcurl/c/libcurl-tutorial.html)
- [cJSON Parser](https://github.com/DaveGamble/cJSON)
