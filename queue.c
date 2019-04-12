#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
//@1811167

struct node
{
    int data;
    struct node *next;
};
typedef struct node node;

struct queue
{
    int count;
    node *front;
    node *rear;
};
typedef struct queue queue;

queue *createNewQueue(int *error)
{
    queue *q = malloc(sizeof(queue));
    if (q != NULL)
    {
        q->count = 0;
        q->front = NULL;
        q->rear = NULL;
        return q;
    }
    if (q == NULL)
        *error = 1;
    else *error = 0;

}

int isempty(queue *q)
{
    if (q->front == NULL && q->rear == NULL)
        return 1;
    else
        return 0;

}

int enqueue(queue *q, int value, int *error)
{

    node *tmp;
    tmp = malloc(sizeof(node));

    if (tmp != NULL)
    {
        tmp->data = value;
        tmp->next = NULL;
        if (q->front == NULL && q->rear == NULL)
        {
            q->front = q->rear = tmp;
            return 0;
        }
        q->rear->next = tmp;
        q->rear = tmp;
        q->count++;
        *error = 0;
    } else *error = 2;
}

int dequeue(queue *q, int *error)
{
    if (q->count == 0)
        *error = 3;
    node *tmp;
    int n = q->front->data;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
    return (n);
}

void displayFront(node *head, int *error)
{

    if (head != NULL)
    {
        printf("%d\n", head->data);

    } else *error = 5;
}

int getFront(node *head, int *error)
{
    int n;

    if (head != NULL)
    {
        printf("%d\n", head->data);
        n = head->data;
        return (n);
    } else *error = 5;
}

int isfull(int *error)
{
    if (error == 2)
        return 1;
    else
        return 0;
}

void delete(queue *q, int *error)
{
    if (q->count == 0)
        *error = 4;
    else *error = 0;
    free(q->front);
    free(q->rear);
    q->rear = NULL;
    q->front = NULL;
    q->count = 0;
}
