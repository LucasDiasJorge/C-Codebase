#include <string.h>
#include "../include/platform.h"

#ifdef _WIN32
    #include <windows.h>
    #include <stdlib.h>
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <pwd.h>
#endif

SystemInfo* get_system_info(void) {
    SystemInfo *info = (SystemInfo *)malloc(sizeof(SystemInfo));
    
    if (info == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return NULL;
    }

#ifdef _WIN32
    info->os_name = "Windows";
    info->os_type = "Microsoft";
    info->separator = "\\";
#else
    info->os_name = "Linux";
    info->os_type = "GNU/Linux";
    info->separator = "/";
#endif

    return info;
}

void print_system_info(SystemInfo *info) {
    if (info == NULL) return;
    
    printf("=== INFORMAÇÕES DO SISTEMA ===%s", NEWLINE);
    printf("SO: %s%s", info->os_name, NEWLINE);
    printf("Tipo: %s%s", info->os_type, NEWLINE);
    printf("Separador de caminho: %s%s", info->separator, NEWLINE);
    printf("%s", NEWLINE);
}

void free_system_info(SystemInfo *info) {
    if (info != NULL) {
        free(info);
    }
}

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause_program(void) {
#ifdef _WIN32
    system("pause");
#else
    printf("Pressione ENTER para continuar...");
    fflush(stdout);
    getchar();
#endif
}

const char* get_home_directory(void) {
#ifdef _WIN32
    return getenv("USERPROFILE");
#else
    return getenv("HOME");
#endif
}
