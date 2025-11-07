#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 9090
#define BUF_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[BUF_SIZE];
    socklen_t server_len = sizeof(server);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUF_SIZE, stdin);

        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server, server_len);

        memset(buffer, 0, BUF_SIZE);
        recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr *)&server, &server_len);
        printf("Echo from server: %s", buffer);
    }

    close(sock);
    return 0;
}

