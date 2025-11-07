#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int cap, rate, n;
    printf("Enter bucket size (tokens): "); scanf("%d", &cap);
    printf("Enter token generation rate (tokens/sec): "); scanf("%d", &rate);
    printf("Enter number of packets: "); scanf("%d", &n);

    int size[n], tokens = 0, sent = 0, drop = 0;
    printf("Enter packet sizes:\n");
    for (int i = 0; i < n; i++) scanf("%d", &size[i]);

    for (int i = 0; i < n; i++) {
        sleep(1);
        tokens += rate;
        if (tokens > cap) tokens = cap;
        printf("\nPacket %d of size %d arrived. Tokens=%d\n", i + 1, size[i], tokens);
        if (size[i] <= tokens) { tokens -= size[i]; sent++; printf("✅ Sent | Remaining tokens=%d\n", tokens); }
        else { drop++; printf("❌ Dropped | Not enough tokens\n"); }
    }

    printf("\nSummary:\nSent=%d\tDropped=%d\tFinal tokens=%d\n", sent, drop, tokens);
    return 0;
}
