//program to implement priority scheduling

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int main()
{
    int at[5], bt[5], n, i, j, temp, p[5], st[5], ft[5], wt[5], tat[5];
    int WT = 0, TAT = 0;
    float AWT, ATAT;
    char pn[5][5], t[5];
    cout << " Enter Number of Processes : ";
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cout << " Enter PID : ";
        scanf("%s", pn[i]);
        cout << " Enter ArrivalTime : ";
        cin >> at[i];
        cout << " Enter BurstTime : ";
        cin >> bt[i];
        cout << " Enter Priority : ";
        cin >> p[i];
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (p[i] < p[j])
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                strcpy(t, pn[i]);
                strcpy(pn[i], pn[j]);
                strcpy(pn[j], t);
            }
        }
    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            st[i] = at[i];
            wt[i] = st[i] - at[i];
            ft[i] = st[i] + bt[i];
            tat[i] = ft[i] - at[i];
        }
        else
        {
            st[i] = ft[i - 1];
            wt[i] = st[i] - at[i];
            ft[i] = st[i] + bt[i];
            tat[i] = ft[i] - at[i];
        }
        WT += wt[i];
        TAT += tat[i];
    }
    AWT = (float)WT / n;
    ATAT = (float)TAT / n;
    cout << "\n PID\tArrivalTime\tBurstTime\tPriority\tWaitingTime\tTurnAroundTime ";
    for (i = 0; i < n; i++)
        cout << "\n " << pn[i] << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << p[i] << "\t\t" << wt[i] << "\t\t" << tat[i];
    cout << "\n Average Waiting Time : " << AWT;
    cout << "\n Average Turn Around Time : " << ATAT;
}
