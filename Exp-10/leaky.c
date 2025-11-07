#include <stdio.h>
#include <stdlib.h>

typedef struct { int time, size; } Packet;

int main() {
    int cap, rate, n;
    printf("Enter bucket capacity (bytes): "); scanf("%d", &cap);
    printf("Enter leak rate (bytes/sec): ");   scanf("%d", &rate);
    printf("Enter number of packets: ");       scanf("%d", &n);

    Packet p[n];
    printf("Enter arrival time and size of each packet:\n");
    for (int i = 0; i < n; i++) scanf("%d %d", &p[i].time, &p[i].size);

    int buf = 0, prev = 0, drop = 0;
    printf("\nTime\tSize\tLeaked\tAction\tBuffer\n");
    for (int i = 0; i < n; i++) {
        int dt = p[i].time - prev, leak = dt * rate;
        if (leak > buf) leak = buf;
        buf -= leak; prev = p[i].time;
        if (buf + p[i].size <= cap) { buf += p[i].size; printf("%d\t%d\t%d\tACCEPT\t%d\n", p[i].time, p[i].size, leak, buf); }
        else { drop += p[i].size; printf("%d\t%d\t%d\tDROP\t%d\n", p[i].time, p[i].size, leak, buf); }
    }
    printf("\nTotal Dropped: %d bytes\n", drop);
    return 0;
}
