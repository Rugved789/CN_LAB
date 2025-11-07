#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 10055
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(server);

    FILE *fp;
    char filename[100];

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;  // localhost

    // Ask user for filename
    printf("Enter the filename to send: ");
    scanf("%s", filename);

    // Open the file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File open error");
        exit(1);
    }

    // Step 1: Send filename to server
    sendto(sockfd, filename, strlen(filename), 0,
           (struct sockaddr *)&server, len);

    // Step 2: Send file data
    while (!feof(fp)) {
        memset(buffer, 0, BUF_SIZE);
        int n = fread(buffer, sizeof(char), BUF_SIZE, fp);
        if (n > 0) {
            sendto(sockfd, buffer, n, 0, (struct sockaddr *)&server, len);
        }
    }

    // Step 3: Send end signal
    strcpy(buffer, "EOF");
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, len);

    printf("File transfer completed.\n");

    fclose(fp);
    close(sockfd);
    return 0;
}
