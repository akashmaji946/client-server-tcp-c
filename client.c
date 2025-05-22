/* client.c */
/*
@author: Akash
@email: akashmaji@iisc.ac.in
*/
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
    printf(GREEN);
    printf(">>> Connected to server at [%s:%d] <<< \n", server_ip, port);
    printf(RESET);

    // buffer to store the message
    char buffer[MAX_MESSAGE_LENGTH];
    bzero(buffer, MAX_MESSAGE_LENGTH);
    // buffer to store the message to receive from the client
    char message_to_receive[MAX_MESSAGE_LENGTH];
    bzero(message_to_receive, MAX_MESSAGE_LENGTH);
    // buffer to store the message to send to the client
    char message_to_send[MAX_MESSAGE_LENGTH];
    bzero(message_to_send, MAX_MESSAGE_LENGTH);


    int bytes_read;
    int bytes_written;

    // bytes_read = read(client_fd, message_to_receive, MAX_MESSAGE_LENGTH);
    strncpy(message_to_receive, "> Begin conversation by sending a message to the server. <\
    \n( Press Enter to send a message. Press Ctrl+C to exit )\n", MAX_MESSAGE_LENGTH);
    bytes_read = strlen(message_to_receive);

    while(bytes_read > 0) {
        // print the message received from the client
        printf(CYAN);
        printf("Server: %s\n", message_to_receive);
        printf(RESET);

        // get the input from stdin
        bzero(buffer, MAX_MESSAGE_LENGTH);
        fgets(buffer, MAX_MESSAGE_LENGTH, stdin);
        // send the message to the client
        bzero(message_to_send, MAX_MESSAGE_LENGTH);
        sprintf(message_to_send, "%s", buffer);
        bytes_written = write(client_fd, message_to_send, strlen(message_to_send));
        if(bytes_written < 0) {
            panic("Failed to send message to server");
        }

        // read the next message
        bzero(message_to_receive, MAX_MESSAGE_LENGTH);
        bytes_read = read(client_fd, message_to_receive, MAX_MESSAGE_LENGTH);
    }

    // check if the read was unsuccessful or the client disconnected
    if(bytes_read < 0) {
        panic("Failed to read message from server");
    }else if(bytes_read == 0) {
        relax("Server disconnected");
    }

    close(client_fd);
    return 0;
}