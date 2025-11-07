#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int total_frames, window_size, sent = 0, ack = 0;
    int loss_chance = 20;
    srand(time(NULL));

    printf("Enter total number of frames: ");
    scanf("%d", &total_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);
    printf("\n--- Sliding Window Protocol Simulation (Go-Back-N) ---\n");

    while(ack < total_frames){
        for(int i=0; i<window_size && sent<total_frames; i++){
            printf("Sender: Sending Frames %d\n",sent);
            if(rand()%100 < loss_chance){
                printf("Channel: Frame %d lost!\n",sent);
            } else {
                printf("Receiver: Frame %d received successfully\n",sent);
                sent++;
            }
        }

        // Simulate Acks
        for(int i=ack; i<sent;i++){
            if(rand()%100 < loss_chance){
                printf("ACK %d lost! -> Timeout, retransmitting from frame %d\n",i,i);
                break;
            } else {
                printf("ACK %d received by sender\n",i);
                ack = i + 1;
            }
        }
        // Retransmit if timeout
        if(ack < sent){
            printf("Timeout! Retransmitting window from frame %d\n",ack);
            sent = ack;
        }
        printf("\n");
    }
    printf("All %d frames transmitted successfully!\n", total_frames);
    return 0;
}

