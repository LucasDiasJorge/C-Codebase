#include <stdio.h>
#include <time.h>

// Função para converter timestamp em data
void timestamp_to_date(time_t timestamp) {
    struct tm *time_components = localtime(&timestamp);
    char time_str[100];

    // Formatando timestamp em uma string de data
    strftime(time_str, sizeof(time_str), "%d/%m/%Y", time_components);
    printf("Data correspondente: %s\n", time_str);
}

// Função para converter data em timestamp
time_t date_to_timestamp(const char *date_str) {
    struct tm time_components = {0};

    // Analisando a string de data
    strptime(date_str, "%d/%m/%Y", &time_components);

    // Convertendo os componentes de data em um timestamp
    time_t timestamp = mktime(&time_components);
    return timestamp;
}

int main() {
    struct tm time_components = {0};
    time_t timestamp;
    char time_str[100];

    // Atribuindo componentes de tempo
    time_components.tm_year = 2024 - 1900; // Ano - 1900
    time_components.tm_mon = 1; // Mês (0 - 11)
    time_components.tm_mday = 7; // Dia do mês (1 - 31)
    time_components.tm_hour = 12; // Hora (0 - 23)
    time_components.tm_min = 30; // Minuto (0 - 59)
    time_components.tm_sec = 0; // Segundo (0 - 60)

    // Convertendo componentes de tempo em timestamp
    timestamp = mktime(&time_components);

    // Formatando timestamp em uma string
    strftime(time_str, sizeof(time_str), "%c", &time_components);
    printf("Data e hora fornecidas: %s\n", time_str);

    // Convertendo timestamp em data
    timestamp_to_date(timestamp);

    // Convertendo data em timestamp
    const char *date_str = "01/01/2023";
    time_t converted_timestamp = date_to_timestamp(date_str);
    printf("Timestamp correspondente: %ld\n", converted_timestamp);

    return 0;
}
