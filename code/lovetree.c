#include <stdio.h>
#include <windows.h>

#define MAXM 100
typedef int ElementType;
typedef struct TreeNode *Tree;
struct TreeNode
{
    ElementType Value;
    Tree Left;
    Tree Right;
    int Level;
};
int Z = 0;
int p;
int q = 0;
Tree BuildTree(int a[], int b[], int n, int level);
int Islovetreetest1(int c[], int k);
int Islovetreetest2(Tree T);
void contourtree(Tree T, int leafvalue[], int k);
void searchleaf(Tree T, int c[], int leafvalue[]);
int Compare(Tree H1, Tree H2);
void findelement(Tree Temp, int findlevel, int levelnumber[]);

int main()
{
    int N;
    int i;
    int a[MAXM];
    int b[MAXM];
    int c[MAXM];
    int leafvalue[MAXM];
    Tree H;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }
    for (i = 0; i < N; i++)
    {
        scanf("%d", &b[i]);
    }
    H = BuildTree(a, b, N, 0);
    searchleaf(H, c, leafvalue);
    if (Islovetreetest1(c, Z) && Islovetreetest2(H))
        printf("Yes\n");
    else
        printf("No\n");
    contourtree(H, leafvalue, Z);
}

Tree BuildTree(int a[], int b[], int n, int level)
{
    int i;

    if (n <= 0)
        return NULL;
    else
    {
        Tree T = (Tree)malloc(sizeof(struct TreeNode));
        for (i = 0; i < n; i++)
        {
            if (a[i] == b[n - 1])
            {
                break;
            }
        }
        T->Value = a[i];
        T->Level = level;
        T->Left = BuildTree(a, b, i, level + 1);
        T->Right = BuildTree(&a[i + 1], &b[i], n - i - 1, level + 1);
        return T;
    }
}

void searchleaf(Tree T, int c[], int leafvalue[])
{
    if (T == NULL)
        return;
    else if (T->Left == NULL && T->Right == NULL)
    {
        c[Z] = T->Level;
        leafvalue[Z] = T->Value;
        Z++;
        return;
    }
    else
    {
        searchleaf(T->Left, c, leafvalue);
        searchleaf(T->Right, c, leafvalue);
    }
    return;
}

int Islovetreetest1(int c[], int Z)
{
    int i, j;
    for (i = 0; i < Z / 2; i++)
    {
        if (c[i] != c[Z - 1 - i])
            return 0;
    }
    int max = 0;
    for (i = 1; i <= (Z - 1) / 2; i++)
    {
        if (c[i] >= c[max])
            max = i;
    }
    for (i = 0; i < max; i++)
    {
        if (c[i + 1] < c[i])
        {
            return 0;
        }
    }
    for (i = max; i <= (Z - 3) / 2; i++)
    {
        if (c[i + 1] > c[i])
        {
            return 0;
        }
    }
    return 1;
}

int Islovetreetest2(Tree T)
{
    if (T == NULL)
        return 1;
    else if (Compare(T->Left, T->Right))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Compare(Tree H1, Tree H2)
{
    if (H1 == NULL && H2 == NULL)
    {
        return 1;
    }
    else if (H1 != NULL && H2 != NULL)
    {
        if (Compare(H1->Left, H2->Right) && Compare(H1->Right, H2->Left))
            return 1;
        else
            return 0;
    }
    else
    {
        return 0;
    }
}

void contourtree(Tree T, int leafvalue[], int Z)
{
    int levelnumber[MAXM];
    int contour[MAXM];
    int numberofthisorder[MAXM];
    int i, j;
    int k = 0;
    int flag = 1;

    for (i = 0;; i++)
    {
        p = 0;
        findelement(T, i, levelnumber);
        if (p == 0)
            break;
        else
        {
            if (p == 1)
                contour[k++] = levelnumber[0];
            else
            {
                contour[k++] = levelnumber[0];
                contour[k++] = levelnumber[p - 1];
            }
        }
    }
    int w = k;
    for (i = 0; i < Z; i++)
    {
        flag = 1;
        for (j = 0; j < w; j++)
        {
            if (leafvalue[i] == contour[j])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            contour[k++] = leafvalue[i];
        }
    }
    printf("%d", contour[0]);
    if (k > 1)
    {
        for (i = 1; i < w; i = i + 2)
        {
            printf(" %d", contour[i]);
        }
        for (i = w; i < k; i++)
        {
            printf(" %d", contour[i]);
        }
        for (i = w - 1; i > 0; i = i - 2)
        {
            printf(" %d", contour[i]);
        }
    }
}

void findelement(Tree Temp, int findlevel, int levelnumber[])
{
    if (Temp == NULL)
        return;
    if (Temp->Level == findlevel)
    {
        levelnumber[p] = Temp->Value;
        p++;
        return;
    }
    else
    {
        findelement(Temp->Left, findlevel, levelnumber);
        findelement(Temp->Right, findlevel, levelnumber);
    }
}