#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for sleep()

int main() {
    int cap, rate, n;

    // Step 1: Input parameters
    printf("Enter bucket size (tokens): ");
    scanf("%d", &cap);

    printf("Enter token generation rate (tokens/sec): ");
    scanf("%d", &rate);

    printf("Enter number of packets: ");
    scanf("%d", &n);

    int size[n];
    printf("Enter packet sizes (in tokens required per packet):\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &size[i]);

    // Step 2: Initialize token bucket parameters
    int tokens = 0;  // current token count
    int sent = 0;    // packets successfully transmitted
    int drop = 0;    // packets dropped

    printf("\n--- TOKEN BUCKET SIMULATION START ---\n");

    // Step 3: Process each packet
    for (int i = 0; i < n; i++) {
        sleep(1);  // simulate 1-second time delay for token generation
        tokens += rate;               // generate tokens
        if (tokens > cap) tokens = cap;  // cap tokens at bucket size

        printf("\nPacket %d of size %d arrived. Tokens available: %d\n",
               i + 1, size[i], tokens);

        // Check if enough tokens are available to send packet
        if (size[i] <= tokens) {
            tokens -= size[i];
            sent++;
            printf("✅ Packet Sent | Remaining Tokens: %d\n", tokens);
        } else {
            drop++;
            printf("❌ Packet Dropped | Not enough tokens!\n");
        }
    }

    // Step 4: Print summary
    printf("\n--- SIMULATION SUMMARY ---\n");
    printf("Packets Sent: %d\n", sent);
    printf("Packets Dropped: %d\n", drop);
    printf("Final Tokens Remaining: %d\n", tokens);
    printf("--------------------------------------\n");

    return 0;
}
