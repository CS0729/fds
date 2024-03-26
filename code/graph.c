#include <stdio.h>
#include <windows.h>
#define MAXM 201

int main()
{
    int numberofvertex, numberofedge;
    scanf("%d%d", &numberofvertex, &numberofedge);
    int a[MAXM][MAXM];
    for (int i = 0; i < MAXM; i++)
    {
        for (int j = 0; j < MAXM; j++)
        {
            a[i][j] = 0;
        }
    }

    int i, j, start, end, testtime, n;
    for (i = 0; i < numberofedge; i++)
    {
        scanf("%d%d", &start, &end);
        a[start - 1][end - 1] = 1;
        a[end - 1][start - 1] = 1;
    }
    scanf("%d", &testtime);
    for (i = 1; i <= testtime; i++)
    {
        scanf("%d", &n);
        int flag = 1;
        int b[MAXM];
        int mark[MAXM] = {0};
        for (j = 0; j < n; j++)
        {
            scanf("%d", &b[j]);
            mark[b[j] - 1] = 1;
        }

        if (b[n - 1] != b[0])
        {
            flag = 0;
        }
        else
        {
            int k;
            flag = 1;
            for (k = 0; k < n - 1; k++)
            {
                if (a[b[k] - 1][b[k + 1] - 1] != 1)
                {
                    flag = 0;
                }
            }
        }
        for (int k = 0; k < numberofvertex; k++)
        {
            if (mark[k] == 0)
            {
                flag = 0;
                break;
            }
        }
        if (n != numberofvertex + 1)
            flag = 0;
        if (flag == 0)
            printf("NO\n");
        else
            printf("YES\n");
    }
}
