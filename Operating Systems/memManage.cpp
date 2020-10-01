//program to implement first fit, best fit, worst fit algorithm for memory management

#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    int bloSize[5], proSize[5], temp[5], i = 0, j = 0, k = 0, n, m, count = 0, ch;
    cout << " Enter Number of Processes : ";
    cin >> n;
    cout << " Enter Number of Blocks : ";
    cin >> m;
    cout << " Enter the SIZE of Processes : ";
    for (i = 0; i < n; i++)
        cin >> proSize[i];
    cout << " Enter the SIZE of Blocks : ";
    for (j = 0; j < m; j++)
        cin >> bloSize[j];
    for (k = 0; k < n; k++)
        temp[k] = -1;
    cout << " Options --- 1.First Fit\t2.Best Fit\t3.Worst Fit " << endl;
    cout << " Enter Your Choice : ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                if (proSize[i] <= bloSize[j] && bloSize[j] != 0)
                {
                    temp[i] = j;
                    bloSize[j] -= proSize[i];
                    break;
                }
            }
        }
        break;
    case 2:
        for (i = 0; i < n; i++)
        {
            int diff = 9999;
            for (j = 0; j < m; j++)
            {
                if (proSize[i] <= bloSize[j] & bloSize[j] != 0 && (bloSize[j] - proSize[i]) < diff)
                {
                    diff = bloSize[j] - proSize[i];
                    count = j;
                }
            }
            if (diff != 0)
            {
                bloSize[count] -= proSize[i];
                temp[i] = count;
            }
        }
        break;
    case 3:
        for (i = 0; i < n; i++)
        {
            int diff = 0;
            for (j = 0; j < m; j++)
            {
                if (proSize[i] <= bloSize[j] & bloSize[j] != 0 && (bloSize[j] - proSize[i]) > diff)
                {
                    diff = bloSize[j] - proSize[i];
                    count = j;
                }
            }
            if (diff != 0)
            {
                bloSize[count] -= proSize[i];
                temp[i] = count;
            }
        }
        break;
    default:
        cout << " Wrong Choice ! ";
        break;
    }
    cout << "\n Process No.\tProcess Size\tBlock No.\n";
    for (i = 0; i < n; i++)
    {
        cout << "   " << i + 1 << "\t\t" << proSize[i] << "\t\t";
        if (temp[i] != -1)
            cout << temp[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
    return 0;
}
