#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define API_KEY "sua_chave_api_aqui"
#define CITY "Nova Friburgo"
#define URL_FORMAT "http://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric"

// Estrutura para armazenar os dados da resposta
struct string {
    char *ptr;
    size_t len;
};

// Função para inicializar a estrutura string
void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

// Função de callback para escrever os dados recebidos
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    struct string s;

    char url[256];
    snprintf(url, sizeof(url), URL_FORMAT, CITY, API_KEY);

    init_string(&s);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("%s\n", s.ptr);
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    free(s.ptr);

    return 0;
}
