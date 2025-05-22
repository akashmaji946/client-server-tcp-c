/* server.c */

#include "common.h"

int main(int argc, char *argv[]) {
    
    // we assume we use localhost(127.0.0.1)
    if(argc != 2) {
        panic("Usage: ./server <port>");
    }
    // get the port number
    int port;
    port = atoi(argv[1]);
    if(port < 0 || port > 65535) {
        panic("Invalid port number");
    }

    // create a socket (endpoint) for server
    // use AF_INET for IPv4
    // use SOCK_STREAM for TCP
    // use 0 for default protocol
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) {
        panic("Failed to create server socket");
    }

    // bind the socket to the port

    // use `sockaddr_in` to store the server address
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    int server_addr_len;
    server_addr_len = sizeof(server_addr);
    // use AF_INET for IPv4
    server_addr.sin_family = AF_INET;
    // inet_addr: convert string IP address to network byte order
    server_addr.sin_addr.s_addr = inet_addr(LOCALHOST);
    // htons: convert integer port number to network byte order
    server_addr.sin_port = htons(port); 

    // bind the socket to the port
    int bind_success;
    bind_success = bind(server_fd, (struct sockaddr *)&server_addr, server_addr_len);
    if(bind_success < 0) {
        panic("Failed to bind server socket to port");
    }

    // listen for incoming connections
    int listen_success;
    listen_success = listen(server_fd, MAX_CLIENTS);
    if(listen_success < 0) {
        panic("Failed to listen for incoming connections");
    }
    relax("Server is listening for incoming connections");

    // accept incoming connections
    int client_fd;
    // use `sockaddr_in` to fill the client address
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    int client_addr_len;
    client_addr_len = sizeof(client_addr);
    // accept: will block until a client connects, and populates the client address
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if(client_fd < 0) {
        panic("Failed to accept incoming connection");
    }

    // buffer to store the message
    char buffer[MAX_MESSAGE_LENGTH];
    bzero(buffer, MAX_MESSAGE_LENGTH);
    // read the message from the client
    int bytes_read;
    bytes_read = read(client_fd, buffer, MAX_MESSAGE_LENGTH);

    while(bytes_read > 0) {
        // print the message
        printf("Client: %s\n", buffer);
        // read the next message
        bzero(buffer, MAX_MESSAGE_LENGTH);
        bytes_read = read(client_fd, buffer, MAX_MESSAGE_LENGTH);
    }

    // check if the read was unsuccessful or the client disconnected
    if(bytes_read < 0) {
        panic("Failed to read message from client");
    }else if(bytes_read == 0) {
        relax("Client disconnected");
    }

    // close the connection
    close(client_fd);
    close(server_fd);
    
}