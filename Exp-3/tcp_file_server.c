// tcp_file_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PRN 123
#define PORT (10000 + PRN)
#define BUF_SIZE 1024

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUF_SIZE];

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    listen(server_sock, 1);
    printf("TCP file server listening on port %d...\n", PORT);

    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
    if (client_sock < 0) {
        perror("Accept failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Receive filename size
    int filename_len;
    recv(client_sock, &filename_len, sizeof(filename_len), 0);

    // Receive filename
    recv(client_sock, buffer, filename_len, 0);
    buffer[filename_len] = '\0';
    printf("Receiving file: %s\n", buffer);

    FILE *fp = fopen(buffer, "wb");
    if (!fp) {
        perror("File creation failed");
        close(client_sock);
        close(server_sock);
        return 1;
    }

    // Receive file data
    int bytes;
    while ((bytes = recv(client_sock, buffer, BUF_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes, fp);
    }

    printf("File received successfully.\n");
    fclose(fp);
    close(client_sock);
    close(server_sock);
    return 0;
}
