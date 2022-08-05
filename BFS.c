#include <stdio.h>
#include <stdlib.h>
#define maxnode 100000
#define ll long long int
 
typedef struct Node
{
    int  id;
    struct Node *next;
}Node;
 
typedef struct List
{
    Node *head;
}List;
 
List *adjlist[maxnode];
int visited[maxnode] = {0};
 
void addnode(int x, int y)
{
    Node *temp,*dest;
    dest = (Node *)malloc(sizeof(Node));
    dest->id = y;
    dest->next = NULL;
    temp = adjlist[x]->head;
    while(temp->next)
    {
        temp = temp->next;
    }
    temp->next = dest;
}

typedef struct QNode
{
    int data;
    struct QNode *next;
}QNode;

QNode *front=NULL, *rear = NULL;

void enque(int x)
{
    QNode *t;
    t = (QNode *)malloc(sizeof(QNode));
    if(front)
    {
        t->data = x;
        t->next = NULL;
        rear->next = t;
        rear = t;
    }
    else
    {
        t->data = x;
        t->next = NULL;
        front = rear = t;
    }
}

int deque()
{
    QNode *p;
    int s;
    if(front)
    {
        p = front;
        front = front->next;
        s = p->data;
        free(p);
    }
    return s;
}

int isEmpty()
{
    if(front)
        return 1;
    else 
        return 0;
}

void bfs(int id)
{
    enque(id);
    printf("%d ",id);
    visited[id] = 1;
    int x,y;
    Node *temp;
    while(isEmpty())
    {
        x = deque();
        temp = adjlist[x]->head;
        while(temp->next)
        {
            temp = temp->next;
            y = temp->id;
            if(visited[y]==0)
            {
                enque(y);
                visited[y] = 1;
                printf("%d ",y);
            }
        }
    }
}

int main()
{
    Node *src;
    int n;
    ll m;
    scanf("%d",&n);
    scanf("%lld",&m);
    for(int i=0;i<n;i++)
    {
        adjlist[i] = (List*)malloc(sizeof(List));
        adjlist[i]->head = NULL;
        src = (Node *)malloc(sizeof(Node));
        src->id = i;
        src->next = NULL;
        adjlist[i]->head = src;
    }
    int x,y;
    while(m--)
    {
        scanf("%d",&x);
        scanf("%d",&y);
        addnode(x,y);
    }
    bfs(0);
    printf("\n");
    return 0;
}