#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/platform.h"

#define RESET   "\x1b[0m"
#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"

int tests_run = 0;
int tests_passed = 0;

void test_assert(int condition, const char *test_name) {
    tests_run++;
    if (condition) {
        printf("%s[✓ PASSOU]%s %s%s", GREEN, RESET, test_name, NEWLINE);
        tests_passed++;
    } else {
        printf("%s[✗ FALHOU]%s %s%s", RED, RESET, test_name, NEWLINE);
    }
}

void test_platform_detection(void) {
    printf("%s=== TESTES DE DETECÇÃO DE PLATAFORMA ===%s%s", YELLOW, RESET, NEWLINE);
    
    SystemInfo *info = get_system_info();
    test_assert(info != NULL, "Alocação de SystemInfo");
    
    if (info) {
        test_assert(info->os_name != NULL, "Nome do SO definido");
        test_assert(info->os_type != NULL, "Tipo do SO definido");
        test_assert(info->separator != NULL, "Separador definido");
        
#ifdef _WIN32
        test_assert(strcmp(info->os_name, "Windows") == 0, "SO identificado como Windows");
#else
        test_assert(strcmp(info->os_name, "Linux") == 0, "SO identificado como Linux");
#endif
        
        free_system_info(info);
    }
    
    printf("%s", NEWLINE);
}

void test_home_directory(void) {
    printf("%s=== TESTES DE DIRETÓRIO HOME ===%s%s", YELLOW, RESET, NEWLINE);
    
    const char *home = get_home_directory();
    test_assert(home != NULL, "Diretório home obtido");
    test_assert(strlen(home) > 0, "Diretório home não está vazio");
    
    printf("%s", NEWLINE);
}

void test_newline_constant(void) {
    printf("%s=== TESTES DE CONSTANTES ===%s%s", YELLOW, RESET, NEWLINE);
    
    test_assert(NEWLINE != NULL, "NEWLINE constante definida");
    
#ifdef _WIN32
    test_assert(strcmp(NEWLINE, "\r\n") == 0, "NEWLINE é \\r\\n em Windows");
#else
    test_assert(strcmp(NEWLINE, "\n") == 0, "NEWLINE é \\n em Linux");
#endif
    
    printf("%s", NEWLINE);
}

void test_platform_macros(void) {
    printf("%s=== TESTES DE MACROS DE PLATAFORMA ===%s%s", YELLOW, RESET, NEWLINE);
    
#ifdef _WIN32
    test_assert(PLATFORM_WINDOWS == 1, "PLATFORM_WINDOWS definido");
    test_assert(PLATFORM_LINUX == 0, "PLATFORM_LINUX não definido em Windows");
#else
    test_assert(PLATFORM_LINUX == 1, "PLATFORM_LINUX definido");
    test_assert(PLATFORM_WINDOWS == 0, "PLATFORM_WINDOWS não definido em Linux");
#endif
    
    printf("%s", NEWLINE);
}

void print_summary(void) {
    printf("%s╔════════════════════════════════════════╗%s", YELLOW, RESET);
    printf("%s║           RESUMO DOS TESTES            ║%s", NEWLINE, NEWLINE);
    printf("%s║ Total de testes: %-22d ║%s", NEWLINE, tests_run, NEWLINE);
    printf("%s║ Testes passando: %-22d ║%s", NEWLINE, tests_passed, NEWLINE);
    printf("%s║ Taxa de sucesso: %.1f%%         ║%s", NEWLINE, 
           (tests_run > 0) ? ((float)tests_passed / tests_run) * 100 : 0, NEWLINE);
    printf("%s╚════════════════════════════════════════╝%s%s", NEWLINE, RESET, NEWLINE);
}

int main(void) {
    printf("%s╔════════════════════════════════════════╗%s", YELLOW, RESET);
    printf("%s║    TESTES DE CROSS-COMPILATION        ║%s", NEWLINE, NEWLINE);
    printf("%s╚════════════════════════════════════════╝%s%s", NEWLINE, RESET, NEWLINE);
    
    test_platform_detection();
    test_home_directory();
    test_newline_constant();
    test_platform_macros();
    
    print_summary();
    
    return (tests_passed == tests_run) ? EXIT_SUCCESS : EXIT_FAILURE;
}
