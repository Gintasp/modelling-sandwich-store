#ifndef QUEUE_H_INCLUDED

#include "p_queue.h"

struct node;
struct queue;

queue *createNewQueue(int *error);  //sukuriama tuscia eile

int enqueue(queue *q, int value, int *error);  //idedamas naujas elementas

int dequeue(queue *q, int *error); //isimamas elementas

void displayFront(node *head, int *error); //parodomi pirno elemento duomenys

int getFront(node *head, int *error);   //gaunami pirmo elemento duomenys (neisimant elemento is eiles)

void delete(queue *q, int *error); //eile sunaikinama

int isFull(int *error);  //1 - tiesa, 0 - netiesa

int isEmpty(queue *q);   //1 - tiesa, 0 - netiesa

/*
Klaidu kodai:
0 - klaidos nera
1 - nepayko sukurti eiles
2 - eile pilna
3 - bandoma pasalinti skaiciu is tuscios eiles
4 - bandoma istrinti tuscia eile
5 - eile tuscia
*/
#define QUEUE_H_INCLUDED

#endif // QUEUE_H_INCLUDED
