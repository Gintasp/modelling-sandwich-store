#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

struct Node_t
{
    struct Node_t *next;
    Type duom;
};
typedef struct Node_t Node;


struct Stekas_t
{
    Node pradzia;
    int full;
};


Stekas *createStack()
{
    Stekas *stekas = malloc(sizeof(Stekas));
    if (stekas)
    {
        stekas->full = 0;
        stekas->pradzia.next = NULL;
        return stekas;
    } else
    {
        stekas->full = 1;
        return NULL;
    }
}


int isStackEmpty(Stekas *stekas)
{
    if (stekas->pradzia.next == NULL)
    {
        return 1;
    } else return 0;
}

int push(Stekas *stekas, Type data)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode)
    {
        newNode->duom = data;
        newNode->next = stekas->pradzia.next;
        stekas->pradzia.next = newNode;
        return 1;
    } else
    {
        stekas->full = 1;
        return 0;
    }
}

int pop(Stekas *stekas, Type *data)
{
    if (isStackEmpty(stekas))
        return 0;
    if (data)
    {
        stekas->full = 0;
        *data = stekas->pradzia.next->duom;
    }
    ///istrina node (atlaisvinam atminti)
    Node *temp = stekas->pradzia.next;
    stekas->pradzia.next = stekas->pradzia.next->next;
    free(temp);
    return 1;
}

int isStackFull(Stekas *stekas)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode)
    {
        stekas->full = 0;
        free(newNode);
        return 0;
    } else
    {
        stekas->full = 1;
        return 1;
    }
}

void destroyStack(Stekas *stekas)
{
    Node *dabartinis = stekas->pradzia.next;
    while (dabartinis->next != NULL)
    {
        Node *temp = dabartinis->next;
        free(dabartinis);
        dabartinis = temp;
    }
    free(stekas);
}
