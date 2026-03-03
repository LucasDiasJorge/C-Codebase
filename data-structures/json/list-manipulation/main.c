#include <stdio.h>
#include <stdlib.h>
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
    char response[MAX_RESPONSE_SIZE] = "";

    if (curl) {
        // URL da requisição GET
        char url[] = "http://localhost:8891/api/v2/user";

        // Configuração da requisição
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, "user:user");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        // Execução da requisição
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Erro ao realizar a requisição: %s\n", curl_easy_strerror(res));
        } else {
            // Exibindo a resposta obtida
           // printf("Resposta da requisição GET: %s\n", response);
        }

        // Finalização do libcurl
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Erro ao inicializar o libcurl.\n");
        return 1;
    }

    // Tokeniza a string para separar os elementos
    char *token;
    char *copy = strdup(response); // Faz uma cópia da string para não modificar a original
    token = strtok(copy, "[],"); // Divide a string pelos colchetes [] e pela vírgula

    // Percorre os itens na lista
    while (token != NULL) {
        // Remove as aspas em excesso
        char *cleaned_string = strdup(token);
        memmove(cleaned_string, cleaned_string+1, strlen(cleaned_string));
        cleaned_string[strlen(cleaned_string)-1] = '\0'; // Remove a última aspas e a vírgula

        printf("%s\n", cleaned_string);

        free(cleaned_string); // Libera a memória alocada
        token = strtok(NULL, "[],"); // Avança para o próximo item na lista
    }

    free(copy); // Libera a memória alocada pela cópia da string

    return 0;
}
