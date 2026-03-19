#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdio.h>
#include <stdlib.h>

/* Detecção de plataforma */
#ifdef _WIN32
    #define PLATFORM_WINDOWS 1
    #define PLATFORM_LINUX 0
    #define NEWLINE "\r\n"
#else
    #define PLATFORM_WINDOWS 0
    #define PLATFORM_LINUX 1
    #define NEWLINE "\n"
#endif

/* Funções de plataforma */
typedef struct {
    const char *os_name;
    const char *os_type;
    const char *separator;
} SystemInfo;

SystemInfo* get_system_info(void);
void print_system_info(SystemInfo *info);
void free_system_info(SystemInfo *info);

/* Funções portáveis */
void clear_screen(void);
void pause_program(void);
const char* get_home_directory(void);

#endif // PLATFORM_H
