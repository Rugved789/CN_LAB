#include <stdio.h>
#define INF 9999
#define N 10

int main() {
    int n, i, j, k, updated;
    int cost[N][N], DV[N][N], nextHop[N][N];

    // Step 1: Initialization
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter cost matrix (9999 for no link):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            DV[i][j] = cost[i][j];
            nextHop[i][j] = (cost[i][j] != INF && i != j) ? j : -1;
        }
        DV[i][i] = 0;
        nextHop[i][i] = i;
    }

    // Step 2: Repeat until no distance vector changes
    do {
        updated = 0;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                for (k = 0; k < n; k++)
                    if (DV[i][j] > cost[i][k] + DV[k][j]) {
                        DV[i][j] = cost[i][k] + DV[k][j];
                        nextHop[i][j] = k;
                        updated = 1;
                    }
    } while (updated);

    // Step 3: Print Final Distance Vectors (Routing Tables)
    printf("\nFinal Routing Tables:\n");
    for (i = 0; i < n; i++) {
        printf("\nNode %d:\nDest\tDist\tNextHop\n", i + 1);
        for (j = 0; j < n; j++) {
            if (DV[i][j] >= INF)
                printf("%d\tINF\t-\n", j + 1);
            else
                printf("%d\t%d\t%d\n", j + 1, DV[i][j], nextHop[i][j] + 1);
        }
    }
    return 0;
}

