# ⏰ Timestamp - Conversão de Timestamps

Este módulo demonstra como converter entre timestamps Unix e datas legíveis em C.

## 📝 Descrição

O programa implementa funções para converter timestamps Unix (segundos desde 1970) para formato de data legível e vice-versa.

## 📁 Estrutura

```
Timestamp/
└── main.c      # Funções de conversão
```

## 🔧 Funções Implementadas

### Timestamp para Data

```c
void timestamp_to_date(time_t timestamp) {
    struct tm *time_components = localtime(&timestamp);
    char time_str[100];
    
    strftime(time_str, sizeof(time_str), "%d/%m/%Y", time_components);
    printf("Data: %s\n", time_str);
}
```

### Data para Timestamp

```c
time_t date_to_timestamp(const char *date_str) {
    struct tm time_components = {0};
    
    strptime(date_str, "%d/%m/%Y", &time_components);
    return mktime(&time_components);
}
```

## 🚀 Compilação e Execução

```bash
gcc -o timestamp main.c
./timestamp
```

## 📤 Exemplo de Uso

```c
// Timestamp atual
time_t now = time(NULL);
printf("Timestamp atual: %ld\n", now);

// Converter timestamp para data
timestamp_to_date(1706745600);  // 01/02/2024

// Converter data para timestamp
time_t ts = date_to_timestamp("15/03/2024");
printf("Timestamp: %ld\n", ts);
```

## 💡 Formatos de Data (strftime)

| Especificador | Descrição | Exemplo |
|---------------|-----------|---------|
| `%Y` | Ano (4 dígitos) | 2024 |
| `%m` | Mês (01-12) | 03 |
| `%d` | Dia (01-31) | 15 |
| `%H` | Hora (00-23) | 14 |
| `%M` | Minutos (00-59) | 30 |
| `%S` | Segundos (00-59) | 45 |
| `%A` | Dia da semana | Friday |
| `%B` | Nome do mês | March |

## 📊 Estrutura tm

```c
struct tm {
    int tm_sec;    // Segundos (0-60)
    int tm_min;    // Minutos (0-59)
    int tm_hour;   // Horas (0-23)
    int tm_mday;   // Dia do mês (1-31)
    int tm_mon;    // Mês (0-11)
    int tm_year;   // Anos desde 1900
    int tm_wday;   // Dia da semana (0-6)
    int tm_yday;   // Dia do ano (0-365)
    int tm_isdst;  // Horário de verão
};
```

## 💡 Conceitos Demonstrados

| Conceito | Descrição |
|----------|-----------|
| `time_t` | Tipo para timestamps |
| `struct tm` | Estrutura de tempo decomposto |
| `localtime()` | Converte para hora local |
| `gmtime()` | Converte para UTC |
| `mktime()` | Converte tm para timestamp |
| `strftime()` | Formata data como string |
| `strptime()` | Parse de string para tm |

## ⚠️ Cuidados

### Timezone

```c
// localtime() usa timezone do sistema
struct tm *local = localtime(&timestamp);

// gmtime() sempre retorna UTC
struct tm *utc = gmtime(&timestamp);
```

### Ano 2038

```c
// Em sistemas 32-bit, time_t estoura em 2038
// Use sistemas 64-bit ou time64_t
```

### Thread Safety

```c
// localtime() não é thread-safe, use:
struct tm result;
localtime_r(&timestamp, &result);  // Versão thread-safe
```

## 🔄 Operações Comuns

### Adicionar dias

```c
time_t add_days(time_t t, int days) {
    return t + (days * 24 * 60 * 60);
}
```

### Diferença entre datas

```c
double diff_days(time_t t1, time_t t2) {
    return difftime(t2, t1) / (24 * 60 * 60);
}
```

## 📚 Referências

- [time.h - C Reference](https://en.cppreference.com/w/c/chrono)
- [strftime - Format](https://en.cppreference.com/w/c/chrono/strftime)
- [Unix Timestamp](https://en.wikipedia.org/wiki/Unix_time)
