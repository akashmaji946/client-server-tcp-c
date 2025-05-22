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


typedef struct {
    int client_id;
    char message[MAX_MESSAGE_LENGTH];
} Message;

void panic(const char *message) {
    perror(message);
    fflush(stdout);
    exit(1);
}
void relax(const char *message) {
    printf("%s\n", message);
    fflush(stdout);
}

void bzero(void *s, size_t n) {
    memset(s, 0, n);
}

void bcopy(const void *src, void *dest, size_t n) {
    memcpy(dest, src, n);
}

#endif /* COMMON_H */