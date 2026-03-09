#include <limits.h>

struct Process
{
    int pid;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
};



void sjf_non_preemptive(struct Process p[], int n)
{
    int completed = 0, time = 0, min, idx;
    int visited[20] = {0};

    printf("\nSJF Non Preemptive\n");

    while (completed < n)
    {
        min = INT_MAX;
        idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival <= time && !visited[i] && p[i].burst < min)
            {
                min = p[i].burst;
                idx = i;
            }
        }

        if (idx != -1)
        {
            time += p[idx].burst;
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            visited[idx] = 1;
            completed++;
        }
        else
            time++;
    }

    float avgWT = 0, avgTAT = 0;

    printf("PID\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n", p[i].pid, p[i].waiting, p[i].turnaround);
        avgWT += p[i].waiting;
        avgTAT += p[i].turnaround;
    }

    printf("Average Waiting Time = %.2f\n", avgWT/n);
    printf("Average Turnaround Time = %.2f\n", avgTAT/n);
}



void sjf_preemptive(struct Process p[], int n)
{
    int complete = 0, time = 0, minm = INT_MAX;
    int shortest = 0, finish;
    int check = 0;

    printf("\nSJF Preemptive (SRTF)\n");

    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((p[j].arrival <= time) &&
                (p[j].remaining < minm) && p[j].remaining > 0)
            {
                minm = p[j].remaining;
                shortest = j;
                check = 1;
            }
        }

        if (check == 0)
        {
            time++;
            continue;
        }

        p[shortest].remaining--;
        minm = p[shortest].remaining;

        if (minm == 0)
            minm = INT_MAX;

        if (p[shortest].remaining == 0)
        {
            complete++;
            check = 0;
            finish = time + 1;

            p[shortest].completion = finish;
            p[shortest].turnaround =
                finish - p[shortest].arrival;

            p[shortest].waiting =
                p[shortest].turnaround - p[shortest].burst;
        }

        time++;
    }

    float avgWT = 0, avgTAT = 0;

    printf("PID\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n",
        p[i].pid,
        p[i].waiting,
        p[i].turnaround);

        avgWT += p[i].waiting;
        avgTAT += p[i].turnaround;
    }

    printf("Average Waiting Time = %.2f\n", avgWT/n);
    printf("Average Turnaround Time = %.2f\n", avgTAT/n);
}



void priority_non_preemptive(struct Process p[], int n)
{
    int completed = 0, time = 0;
    int visited[20] = {0};

    printf("\nPriority Non Preemptive\n");

    while (completed < n)
    {
        int idx = -1;
        int highest = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival <= time &&
                !visited[i] &&
                p[i].priority < highest)
            {
                highest = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1)
        {
            time += p[idx].burst;

            p[idx].completion = time;
            p[idx].turnaround =
                p[idx].completion - p[idx].arrival;

            p[idx].waiting =
                p[idx].turnaround - p[idx].burst;

            visited[idx] = 1;
            completed++;
        }
        else
            time++;
    }

    float avgWT = 0, avgTAT = 0;

    printf("PID\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n",
        p[i].pid,
        p[i].waiting,
        p[i].turnaround);

        avgWT += p[i].waiting;
        avgTAT += p[i].turnaround;
    }

    printf("Average Waiting Time = %.2f\n", avgWT/n);
    printf("Average Turnaround Time = %.2f\n", avgTAT/n);
}

void priority_preemptive(struct Process p[], int n)
{
    int time = 0, completed = 0;
    int highest, idx;

    printf("\nPriority Preemptive\n");

    while (completed < n)
    {
        highest = INT_MAX;
        idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival <= time &&
                p[i].remaining > 0 &&
                p[i].priority < highest)
            {
                highest = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1)
        {
            p[idx].remaining--;
            time++;

            if (p[idx].remaining == 0)
            {
                completed++;

                p[idx].completion = time;
                p[idx].turnaround =
                    p[idx].completion - p[idx].arrival;

                p[idx].waiting =
                    p[idx].turnaround - p[idx].burst;
            }
        }
        else
        {
            time++;
        }
    }

    float avgWT = 0, avgTAT = 0;

    printf("PID\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n",
               p[i].pid,
               p[i].waiting,
               p[i].turnaround);

        avgWT += p[i].waiting;
        avgTAT += p[i].turnaround;
    }

    printf("Average Waiting Time = %.2f\n", avgWT/n);
    printf("Average Turnaround Time = %.2f\n", avgTAT/n);
}


/* ---------- MAIN ---------- */

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct Process p[20];

    for(int i=0;i<n;i++)
    {
        printf("\nProcess %d\n",i+1);

        p[i].pid=i+1;

        printf("Arrival Time: ");
        scanf("%d",&p[i].arrival);

        printf("Burst Time: ");
        scanf("%d",&p[i].burst);

        printf("Priority: ");
        scanf("%d",&p[i].priority);

        p[i].remaining = p[i].burst;
    }

    sjf_non_preemptive(p,n);
    sjf_preemptive(p,n);
    priority_non_preemptive(p,n);
    priority_preemptive(p,n);   // added function call

    return 0;
}
