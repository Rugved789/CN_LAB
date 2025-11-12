#include <stdio.h>
#include <stdlib.h>

// Structure to store packet information
typedef struct {
    int time;
    int size; 
} Packet;

int main() {
    int cap, rate, n;
    printf("Enter bucket capacity (bytes): ");
    scanf("%d", &cap);
    printf("Enter leak rate (bytes/sec): ");
    scanf("%d", &rate);
    printf("Enter number of packets: ");
    scanf("%d", &n);

    Packet p[n];
    printf("Enter arrival time and size of each packet:\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &p[i].time, &p[i].size);

    // Step 3: Initialize variables
    int buffer = 0;   // current buffer level
    int prev = 0;     // previous packet time
    int dropped = 0;  // total dropped bytes

    // Step 4: Display table header
    printf("\nTime\tSize\tLeaked\tAction\tBuffer\n");

    // Step 5: Process each packet
    for (int i = 0; i < n; i++) {
        int dt = p[i].time - prev;
        int leak = dt * rate;

        if (leak > buffer)
            leak = buffer;

        buffer -= leak;
        prev = p[i].time;

        if (buffer + p[i].size <= cap) {
            buffer += p[i].size;
            printf("%d\t%d\t%d\tACCEPT\t%d\n", p[i].time, p[i].size, leak, buffer);
        } else {
            dropped += p[i].size;
            printf("%d\t%d\t%d\tDROP\t%d\n", p[i].time, p[i].size, leak, buffer);
        }
    }
    printf("\nTotal Dropped: %d bytes\n", dropped);

    return 0;
}
