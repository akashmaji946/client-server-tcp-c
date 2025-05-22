/* client.c */

#include "common.h"

int main(int argc, char *argv[]) {
    
    // we assume we use localhost(127.0.0.1)
    if(argc != 3) {
        panic("Usage: ./client <server_ip> <port>");
    }
    // get the port number
    int port;
    port = atoi(argv[2]);
    if(port < 0 || port > 65535) {
        panic("Invalid port number");
    }

    // get the server ip address
    char *server_ip;
    server_ip = argv[1];

    // get the server address
    struct hostent *server;
    server = gethostbyname(server_ip);
    if(server == NULL) {
        printf("Error, no such host\n");
        panic("Failed to get server address");
    }

    // create a socket (endpoint) for client
    int client_fd;
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd < 0) {
        panic("Failed to create client socket");
    }

    // connect to the server
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));

    int server_addr_len;
    server_addr_len = sizeof(server_addr);

    server_addr.sin_family = AF_INET;
    // server_addr.sin_addr.s_addr = inet_addr(LOCALHOST);
    bcopy((char *)server->h_addr_list[0], (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(port);

    int connect_success;
    connect_success = connect(client_fd, (struct sockaddr *)&server_addr, server_addr_len);
    if(connect_success < 0) {
        panic("Failed to connect to server");
    }

    // connect successfully
    printf("Connected to server\n");

    // send a message to the server
    char message[MAX_MESSAGE_LENGTH];
    bzero(message, MAX_MESSAGE_LENGTH);
    sprintf(message, "Hello, server!");

    int bytes_written;
    bytes_written = write(client_fd, message, strlen(message));
    if(bytes_written < 0) {
        panic("Failed to send message to server");
    }

    close(client_fd);
    return 0;
}