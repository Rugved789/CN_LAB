#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 9090
#define BUF_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server, client;
    char buffer[BUF_SIZE];
    socklen_t client_len = sizeof(client);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Echo Server listening on port %d...\n", PORT);

    while (1) {
        memset(buffer, 0, BUF_SIZE);
        recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr *)&client, &client_len);
        printf("Received: %s", buffer);
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&client, client_len);
    }

    close(sock);
    return 0;
}

