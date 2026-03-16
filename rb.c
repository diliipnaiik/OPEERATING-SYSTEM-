#include <stdio.h>

void roundRobin(int n, int bt[], int quantum) {
    int wt[n], tat[n], rem_bt[n];
    int t = 0;
    int i;



    for(i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    while(1) {
        int done = 1;

        for(i = 0; i < n; i++) {

            if(rem_bt[i] > 0) {
                done = 0;

                if(rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }

        if(done == 1)
            break;
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    float total_wt = 0, total_tat = 0;

    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];

        printf("P%d\t%d\t\t%d\t\t%d\n", i+1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat/n);
}

int main() {

    int n = 4;
    int bt[] = {5, 4, 2, 1};

    printf("Round Robin Scheduling (Time Quantum = 2)\n");
    roundRobin(n, bt, 2);

    printf("\n----------------------------------------\n");

    printf("\nRound Robin Scheduling (Time Quantum = 4)\n");
    roundRobin(n, bt, 4);

    return 0;
}
