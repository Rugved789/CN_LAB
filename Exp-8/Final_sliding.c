#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int total_frames, window_size, ack = 0;
    srand(time(NULL)); // for random loss

    printf("Enter total number of frames: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);

    printf("\n--- Go-Back-N Sliding Window Protocol ---\n");

    while (ack < total_frames) {
        printf("\nSender: Sending frames ");
        for (int i = ack; i < ack + window_size && i < total_frames; i++)
            printf("%d ", i);
        printf("\n");

        for (int i = ack; i < ack + window_size && i < total_frames; i++) {
            int frame_lost = rand() % 5 == 0; // 20% chance frame lost
            if (frame_lost) {
                printf("Frame %d lost! Retransmitting from frame %d\n", i, i);
                break; // stop and retransmit
            } else {
                printf("Receiver: Frame %d received\n", i);

                int ack_lost = rand() % 5 == 0; // 20% chance ACK lost
                if (ack_lost) {
                    printf("ACK %d lost! Retransmitting from frame %d\n", i, i);
                    break; // retransmit from this frame
                } else {
                    printf("Sender: ACK %d received\n", i);
                    ack++;
                }
            }
        }
    }

    printf("\nAll %d frames transmitted successfully!\n", total_frames);
    return 0;
}
