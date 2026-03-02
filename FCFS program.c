#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes (max 20): ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Invalid number of processes! Must be between 1 and 20.\n");
        return 0;
    }

    int pid[20], at[20], bt[20], ct[20], wt[20], tat[20];
    float total_wt = 0, total_tat = 0;

    // Input
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;

        printf("\nProcess P%d\n", pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }


    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                int temp;


                temp = at[i];
                at[i] = at[j];
                at[j] = temp;


                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;


                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }


    ct[0] = at[0] + bt[0];
    wt[0] = 0;
    tat[0] = ct[0] - at[0];

    for (int i = 1; i < n; i++) {


        if (ct[i - 1] < at[i]) {
            ct[i] = at[i] + bt[i];
        } else {
            ct[i] = ct[i - 1] + bt[i];
        }

        wt[i] = ct[i] - at[i] - bt[i];
        tat[i] = ct[i] - at[i];

        total_wt += wt[i];
        total_tat += tat[i];
    }

    total_wt += wt[0];
    total_tat += tat[0];

    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;


    printf("\n-------------------------------------------------------------");
    printf("\nPID\tAT\tBT\tCT\tWT\tTAT");
    printf("\n-------------------------------------------------------------");

    for (int i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               pid[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n-------------------------------------------------------------");
    printf("\nAverage Waiting Time     = %.2f", avg_wt);
    printf("\nAverage Turnaround Time  = %.2f\n", avg_tat);

    return 0;
}
