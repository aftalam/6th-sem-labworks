//program to implement round robin scheduling

#include <stdio.h>
int main()
{
      int i, x, n, total = 0, count = 0, tquantum;
      int wt = 0, tat = 0, at[10], bt[10], temp[10];
      float awt, atat;
      printf(" Enter Number of Processes : ");
      scanf("%d", &n);
      x = n;
      for (i = 0; i < n; i++)
      {
            printf(" Enter Details of PID [%d] \n", i + 1);
            printf(" ArrivalTime : ");
            scanf("%d", &at[i]);
            printf(" BurstTime : ");
            scanf("%d", &bt[i]);
            temp[i] = bt[i];
      }
      printf("\n Enter Time Quantum : ");
      scanf("%d", &tquantum);
      printf("\n PID\tBurstTime\tWaitingTime\tTurnAroundTime ");
      for (total = 0, i = 0; x != 0;)
      {
            if (temp[i] <= tquantum && temp[i] > 0)
            {
                  total += temp[i];
                  temp[i] = 0;
                  count = 1;
            }
            else if (temp[i] > 0)
            {
                  temp[i] -= tquantum;
                  total += tquantum;
            }
            if (temp[i] == 0 && count == 1)
            {
                  x--;
                  printf("\n  %d\t%d\t\t%d\t\t%d ", i + 1, bt[i], total - at[i] - bt[i], total - at[i]);
                  wt = wt + total - at[i] - bt[i];
                  tat = tat + total - at[i];
                  count = 0;
            }
            if (i == n - 1)
            {
                  i = 0;
            }
            else if (at[i + 1] <= total)
            {
                  i++;
            }
            else
            {
                  i = 0;
            }
      }
      awt = wt * 1.0 / n;
      atat = tat * 1.0 / n;
      printf("\n Average Waiting Time : %f ", awt);
      printf("\n Average Turn Around Time : %f ", atat);
      return 0;
}
