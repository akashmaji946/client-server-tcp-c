/* common.h */

#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 4
#define MAX_MESSAGE_LENGTH 1024
#define LOCALHOST "127.0.0.1"

// define colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

void panic(const char *message) {
    printf(RED);
    perror(message);
    printf(RESET);
    fflush(stdout);
    exit(1);
}
void relax(const char *message) {
    printf(MAGENTA);
    printf("%s\n", message);
    printf(RESET);
    fflush(stdout);
}

void bzero(void *s, size_t n) {
    memset(s, 0, n);
}

void bcopy(const void *src, void *dest, size_t n) {
    memcpy(dest, src, n);
}

#endif /* COMMON_H */