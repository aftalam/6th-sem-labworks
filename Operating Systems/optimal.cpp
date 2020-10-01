//program to implement optimal page replacement algorithm

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
int findpos(int tframe[], int nf, int pages[], int curr, int np)
{
    int i, j;
    for (i = 0; i < nf; i++)
    {
        if (tframe[i] == -1)
            return i;
    }
    int pos[nf] = {0};
    for (i = 0; i < nf; i++)
    {
        pos[i] = 1e9;
        for (j = curr + 1; j < np; j++)
        {
            if (pages[j] == tframe[i])
            {
                pos[i] = j;
                break;
            }
        }
    }
    int max1 = -1;
    int returnpos = -1;
    for (i = 0; i < nf; i++)
    {
        if (pos[i] > max1)
        {
            max1 = pos[i];
            returnpos = i;
        }
    }
    return returnpos;
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
            int pos = findpos(tframe, nf, pages, i, n);
            tframe[pos] = pages[i];
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
