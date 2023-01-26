#include "queue.h"
QUEUE *MakeNullQueue(void)
{
    QUEUE *New;
    New = (QUEUE *)malloc(sizeof(QUEUE));
    LinkList *root;
    root = (LinkList *)malloc(sizeof(LinkList));
    root->next = NULL;
    // root->data = NotFound;
    New->Rear = root;
    New->Front = root;
    return New;
}
int sizeQ(QUEUE *Q)
{
    int i = 0;
    LinkList *root;
    root = Q->Front;
    while (root != Q->Rear)
    {
        root = root->next;
        i++;
    }
    return i;
}
int isEmptyQ(QUEUE *Q)
{
    return (Q->Front == Q->Rear);
}
int isFullQ(QUEUE *Q)
{
    return (sizeQ(Q) == FULL);
}
LinkList *front(QUEUE *Q)
{
    if (!isEmptyQ(Q))
    {
        return Q->Front;
    }
    else
    {
        return NULL;
    }
}
void EnQueue(QUEUE *Q, ElementType x)
{
    if (!isFullQ(Q))
    {
        Q->Rear->next = (LinkList *)malloc(sizeof(LinkList));
        Q->Rear = Q->Rear->next;
        Q->Rear->data = x;
        Q->Rear->next = NULL;
    }
    else
    {
        printf("Full Queue!\n");
    }
}
ElementType DeQueue(QUEUE *Q)
{
    if (!isEmptyQ(Q))
    {
        ElementType x;
        LinkList *Head;
        Head = Q->Front;
        Q->Front = Q->Front->next;
        x = Q->Front->data;
        free(Head);
        return x;
    }
    else
    {
        printf("Empty Queue!\n");
        free(Q->Front);
        free(Q);
        exit(0);
    }
}
void PrintQ(QUEUE *Q) /*Ham nay tuy thuoc vao cau truc du lieu cua data*/
{
    /* code */
}