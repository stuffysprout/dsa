#include <stdio.h>
#include<stdlib.h>
#define ll long long int

typedef struct edge
{
    ll src;
    ll dest;
    ll weight;
}edge;

edge edgelist[1000000];

void Merge(edge A[1000000], ll low, ll mid, ll high){
    ll i = low;
    ll j = mid+1;
    ll k = low;
    ll B[high+1],C[high+1],D[high+1];
    while (i <= mid && j <= high){
        if (A[i].weight <= A[j].weight){
            C[k] = A[i].src;
            D[k] = A[i].dest;
            B[k++] = A[i++].weight;
        } else {
            C[k] = A[j].src;
            D[k] = A[j].dest;
            B[k++] = A[j++].weight;
        }
    }
    while (i <= mid){
        C[k] = A[i].src;
        D[k] = A[i].dest;
        B[k++] = A[i++].weight;
    }
    while (j <= high){
        C[k] = A[j].src;
        D[k] = A[j].dest;
        B[k++] = A[j++].weight;
    }
    for (ll i=low; i<=high; i++){
        A[i].weight = B[i];
        A[i].src = C[i];
        A[i].dest = D[i];
    }
}
 
void RecursiveMergeSort(edge A[1000000], ll low, ll high){
    if (low < high){
        ll mid = low + (high-low)/2;
        RecursiveMergeSort(A, low, mid);
        RecursiveMergeSort(A, mid+1, high);
        Merge(A, low, mid, high);
    }
}

ll size=0,numcomponents=0;
ll iden[1000000],sz[1000000];

void CreateUnionFind(ll n)
{
    if(n==0)
        return;
    size = numcomponents = n;
    for(ll i=0;i<size;i++)
    {
        iden[i] = i;
        sz[i] = 1;
    }
}

ll Find(ll p)
{
    ll root=p;
    while(iden[root]!=root)
    {
        root = iden[root];
    }
    ll temp;
    while(p!=root)
    {
        temp = iden[p];
        iden[p] = root;
        p = temp;
    }
    return root;
}

void Union(ll p, ll q)
{
    ll root1 = Find(p);
    ll root2 = Find(q);
    if(root1==root2)
        return;
    if(sz[root1]>sz[root2])
    {
        sz[root1]+=sz[root2];
        iden[root2] = root1;
        sz[root2] = 0;
    }
    else
    {
        sz[root2]+=sz[root1];
        iden[root1] = root2;
        sz[root1] = 0;
    }
    numcomponents--;
}

ll distance(ll x1,ll x2,ll y1, ll y2)
{
    return abs(x1-x2) + abs(y1-y2);
}

ll main()
{
    ll n;
    scanf("%d",&n);
    ll counter = 0;
    ll points[n][2];
    for(ll i=0;i<n;i++)
    {
        scanf("%d",&points[i][0]);
        scanf("%d",&points[i][1]);
    }
    ll dum;
    for(ll i=0;i<n-1;i++)
    {
        for(ll j=i+1;j<n;j++)
        {
            dum = distance(points[i][0],points[j][0],points[i][1],points[j][1]);
            edgelist[counter].src = i;
            edgelist[counter].dest = j;
            edgelist[counter++].weight = dum;
        }
    }
    RecursiveMergeSort(edgelist,0,counter-1);
    CreateUnionFind(n);
    ll i=0,j=0;
    edge MST[n-1];
    while(numcomponents>1 && j<counter && i<n-1)
    {
        if(Find(edgelist[j].src)!=Find(edgelist[j].dest))
        {
            Union(edgelist[j].src, edgelist[j].dest);
            MST[i].src = edgelist[j].src;
            MST[i].dest = edgelist[j].dest;
            MST[i++].weight = edgelist[j].weight;
        }
        j++;
    }
    if(i==n-1)
    {
        ll sum = 0;
        for(ll i=0;i<n-1;i++)
            sum += MST[i].weight;
        printf("%d\n",sum);
    }
    else
    {
        printf("-1\n");
    }
    return 0;
}