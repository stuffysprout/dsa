#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

Node *front=NULL, *rear = NULL;

void enque(int x)
{
    Node *t;
    t = (Node *)malloc(sizeof(Node));
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
    Node *p;
    int s;
    if(front)
    {
        p = front;
        front = front->next;
        s = p->data;
        free(p);
    }
    else
    {
        printf("\n Queue is empty");
    }
    return s;
}

void display(Node *p)
{
    if(p)
    {
        printf("%d ",p->data);
        display(p->next);
    }
    printf("\n");
}

int main()
{
    int n=0;
    do
    {
        printf("1. enque\n2. deque\n");
        scanf("%d",&n);
        if(n==1)
        {
            int x;
            scanf("%d",&x);
            enque(x);
            if(front)
            display(front);
            else
            printf("\nQueue empty\n");
        }
        else if(n==2)
        {
            int x=deque();
            printf("%d\n",x);
            if(front)
            display(front);
            else
            printf("\nQueue empty\ns");
        }
    } while (n!=3);
    return 0;
    
}