#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 10055
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server, client;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(client);

    FILE *fp;
    char filename[100];

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("UDP File Server listening on port %d...\n", PORT);

    // Step 1: Receive filename from client
    memset(filename, 0, sizeof(filename));
    recvfrom(sockfd, filename, sizeof(filename), 0,
             (struct sockaddr *)&client, &len);

    printf("Receiving file: %s\n", filename);

    // Open file to save received data
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("File open error");
        exit(1);
    }

    // Step 2: Receive file data
    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int n = recvfrom(sockfd, buffer, BUF_SIZE, 0,
                         (struct sockaddr *)&client, &len);

        // Check for end signal
        if (strncmp(buffer, "EOF", 3) == 0) {
            printf("File transfer completed.\n");
            break;
        }

        fwrite(buffer, sizeof(char), n, fp);
    }

    fclose(fp);
    close(sockfd);
    return 0;
}
