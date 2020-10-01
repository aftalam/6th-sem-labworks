//program to implement cpu scheduling for fcfs

#include <stdio.h>
void main()
{
    int art[5], wt[5], bt[5], i, c, p, tat[5];
    float awt = 0, att = 0;
    printf(" Enter Number of Processes : ");
    scanf("%d", &p);
    for (i = 0; i < p; i++)
    {
        printf(" Enter Arrival Time : ");
        scanf("%d", &art[i]);
        printf(" Enter Burst Time : ");
        scanf("%d", &bt[i]);
    }
    c = 0;
    wt[0] = 0;
    for (i = 0; i < p; i++)
    {
        wt[i] = c - art[i];
        c += bt[i];
        tat[i] = bt[i] + wt[i];
        printf("\n Waiting Time for Process %d : %d ", i + 1, wt[i]);
        printf("\n Turn Around Time : %d \n", tat[i]);
    }
    for (i = 0; i < p; i++)
    {
        awt = awt + wt[i];
        att = att + wt[i];
    }
    printf("\n Average Waiting Time : %f ", awt / p);
    printf("\n Average Turn Around Time : %f ", att);
}
