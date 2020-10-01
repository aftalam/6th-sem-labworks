//program to implement fifo page replacement algorithm

#include <iostream>
using namespace std;
int present(int tframe[], int nf, int page)
{
    for (int i = 0; i < nf; i++)
        if (page == tframe[i])
            return 1;
    return 0;
}
void printtable(int tframe[], int nf)
{
    for (int i = 0; i < nf; i++)
    {
        if (tframe[i] == -1)
            cout << "_ ";
        else
            cout << tframe[i] << " ";
    }
    cout << "||";
}
int main()
{
    int n, nf, i, pos = 0;
    cout << " Enter Number of Frames : ";
    cin >> nf;
    int tframe[nf];
    for (i = 0; i < nf; i++)
    {
        tframe[i] = -1;
    }
    cout << " Enter Number of Page Requests : ";
    cin >> n;
    int pages[n];
    cout << " Enter Page Reference String : ";
    for (i = 0; i < n; i++)
    {
        cin >> pages[i];
    }
    int count1 = 0;
    cout << " Position of Frame Table After Each Request : \n";
    for (i = 0; i < n; i++)
    {
        cout << " After Request " << pages[i] << " || ";
        if (!present(tframe, nf, pages[i]))
        {
            tframe[pos] = pages[i];
            pos = (pos + 1) % nf;
            printtable(tframe, nf);
            cout << " Page Fault ! \n";
            count1++;
            continue;
        }
        printtable(tframe, nf);
        cout << "\n";
    }
    cout << "\n Number of Page Faults : " << count1;
}
