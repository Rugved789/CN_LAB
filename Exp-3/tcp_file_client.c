// tcp_file_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PRN 123
#define PORT (10000 + PRN)
#define BUF_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    char filename[256];
    printf("Enter filename to send: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("File open failed");
        close(sock);
        return 1;
    }

    // Send filename length and filename
    int filename_len = strlen(filename);
    send(sock, &filename_len, sizeof(filename_len), 0);
    send(sock, filename, filename_len, 0);

    // Send file data
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
        send(sock, buffer, bytes_read, 0);
    }

    printf("File sent successfully.\n");

    fclose(fp);
    close(sock);
    return 0;
}
