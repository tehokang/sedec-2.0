#ifndef __TEHO_WORLD__
#define __TEHO_WORLD__

#include <stdio.h>
#define SECTION_PRINT printf

#define SECTION_DEBUG(fmt, ...) \
    do { \
        printf("\033[37;32m"); \
        printf("[%-20s]", __FUNCTION__); \
        printf ( fmt, ##__VA_ARGS__); \
        printf("\033[0m"); \
    } while(0)

#define SECTION_HL_DEBUG(fmt, ...) \
    do { \
        printf("\033[37;31m"); \
        printf("[%-20s]", __FUNCTION__); \
        printf ( fmt, ##__VA_ARGS__); \
        printf("\033[0m"); \
    } while(0)

#endif

