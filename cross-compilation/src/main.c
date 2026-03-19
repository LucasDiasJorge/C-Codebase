#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/platform.h"

void print_welcome(void) {
    printf("╔════════════════════════════════════════════════════════╗%s", NEWLINE);
    printf("║     PROJETO DE CROSS-COMPILATION EM C                 ║%s", NEWLINE);
    printf("║     Linux ↔ Windows                                    ║%s", NEWLINE);
    printf("╚════════════════════════════════════════════════════════╝%s%s", NEWLINE, NEWLINE);
}

void print_compiler_info(void) {
    printf("=== INFORMAÇÕES DO COMPILADOR ===%s", NEWLINE);
    
#ifdef __GNUC__
    printf("Compilador: GCC%s", NEWLINE);
    printf("Versão: %d.%d.%d%s", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__, NEWLINE);
#endif

#ifdef _WIN32
    printf("Alvo: Windows (64-bit)%s", NEWLINE);
#else
    printf("Alvo: Linux/Unix%s", NEWLINE);
#endif

    printf("Data de compilação: %s %s%s", __DATE__, __TIME__, NEWLINE);
    printf("%s", NEWLINE);
}

void print_system_capabilities(void) {
    printf("=== CAPACIDADES DO SISTEMA ===%s", NEWLINE);
    
    printf("Tamanho de tipos:%s", NEWLINE);
    printf("  - sizeof(int): %zu bytes%s", sizeof(int), NEWLINE);
    printf("  - sizeof(long): %zu bytes%s", sizeof(long), NEWLINE);
    printf("  - sizeof(float): %zu bytes%s", sizeof(float), NEWLINE);
    printf("  - sizeof(double): %zu bytes%s", sizeof(double), NEWLINE);
    printf("  - sizeof(void*): %zu bytes%s", sizeof(void*), NEWLINE);
    printf("%s", NEWLINE);
}

void demo_system_calls(void) {
    printf("=== DEMONSTRAÇÃO DE CHAMADAS DE SISTEMA ===%s", NEWLINE);
    
    SystemInfo *info = get_system_info();
    if (info) {
        print_system_info(info);
        free_system_info(info);
    }
    
    const char *home = get_home_directory();
    printf("Diretório home: %s%s", home ? home : "Desconhecido", NEWLINE);
    printf("%s", NEWLINE);
}

void demo_statistics(void) {
    printf("=== ESTATÍSTICAS SIMPLES ===%s", NEWLINE);
    
    srand(time(NULL));
    int numeros[10];
    int soma = 0, media;
    
    printf("Números aleatórios: ");
    for (int i = 0; i < 10; i++) {
        numeros[i] = rand() % 100;
        printf("%d ", numeros[i]);
        soma += numeros[i];
    }
    
    media = soma / 10;
    printf("%s", NEWLINE);
    printf("Soma: %d%s", soma, NEWLINE);
    printf("Média: %d%s", media, NEWLINE);
    printf("%s", NEWLINE);
}

int main(void) {
    print_welcome();
    print_compiler_info();
    print_system_capabilities();
    demo_system_calls();
    demo_statistics();
    
    printf("=== FIM DO PROGRAMA ===%s", NEWLINE);
    printf("Compilação cruzada bem-sucedida! ✓%s", NEWLINE);
    
    return EXIT_SUCCESS;
}
