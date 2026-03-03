#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_RESPONSE_SIZE 1024

// Função de callback para receber os dados da requisição
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    strcat(data, (char *)ptr);
    return size * nmemb;
}

int main() {
    CURL *curl;
    CURLcode res;

    // Inicialização do libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        char response[MAX_RESPONSE_SIZE] = "";

        // URL da requisição GET
        char url[] = "http://localhost:8010/api/v1/ping";

        // Configuração da requisição
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        // Execução da requisição
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Erro ao realizar a requisição: %s\n", curl_easy_strerror(res));
        } else {
            // Exibindo a resposta obtida
            printf("Resposta da requisição GET: %s\n", response);
        }

        // Finalização do libcurl
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Erro ao inicializar o libcurl.\n");
        return 1;
    }

    // Finalização do libcurl global
    curl_global_cleanup();

    return 0;
}