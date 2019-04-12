#include <stdio.h>
#include "queue.h"
#include "stack.h"
#include <stdlib.h>
#include <time.h>

#define WORKDAY 200
#define CLIENT_CHANCE 80
#define NEW_SANDWICH_PERIOD 10
#define NEW_SANDWICH_COUNT 2
#define EXPIRATION 40
#define PRICE 1.5
#define HOLDER_SELECTION_PROBABILITY 50
#define MANUFACTURE_PRICE 0.3

int getRandom(int lower, int upper);

void sandwichStoreStack();

void sandwichStoreQueue();

int main()
{
    sandwichStoreStack();
//    sandwichStoreQueue();

    return 0;
}

void sandwichStoreQueue()
{
    int *error = NULL;
    queue *holder1 = createNewQueue(error);
    queue *holder2 = createNewQueue(error);
    int counter = 0;
    int expirationCounter = 0;
    int s1Count = 0;
    int s2Count = 0;
    double profit = 0;
    int random = 0;
    double production = 0;

    srand(time(0));

    while (counter <= WORKDAY)
    {
        counter++;
        random = getRandom(1, 100);

        //HANDLE NEW SANDWICHES
        if (counter % NEW_SANDWICH_PERIOD == 0)
        {
            if (s1Count <= s2Count)
            {
                for (int i = 0; i < NEW_SANDWICH_COUNT; i++)
                {
                    printf("New sandwich added to Holder1!\n");
                    enqueue(holder1, 1, error);
                    s1Count++;
                }
            } else
            {
                for (int i = 0; i < NEW_SANDWICH_COUNT; i++)
                {
                    printf("New sandwich added to Holder2!\n");
                    enqueue(holder2, 1, error);
                    s2Count++;
                }
            }

            production += MANUFACTURE_PRICE * NEW_SANDWICH_COUNT;
            expirationCounter++;
        } else
        {
            expirationCounter++;
        }

        //HANDLE BUYER
        if (random >= CLIENT_CHANCE && (s1Count > 0 || s2Count > 0))
        {
            printf("A client comes in...\n");
            if (random >= HOLDER_SELECTION_PROBABILITY)
            {
                printf("Client buys sandwich from Holder1\n");
                dequeue(holder1, error);
                s1Count--;
                profit += PRICE;
                printf("Total profit: %.2f\n", profit);
            } else
            {
                printf("Client buys sandwich from Holder2\n");
                dequeue(holder2, error);
                s2Count--;
                profit += PRICE;
                printf("Total profit: %.2f\n", profit);
            }
        } else
        {
            printf("Waiting for clients...\n");
        }

        //HANDLE HOLDER 1 EXPIRED SANDWICHES
        if (s1Count > (EXPIRATION / NEW_SANDWICH_PERIOD) * NEW_SANDWICH_COUNT)
        {
            int expCount1 = s1Count - ((EXPIRATION / NEW_SANDWICH_PERIOD) * NEW_SANDWICH_COUNT);
            printf("Holder1 has %d expired sandwiches.\n", expCount1);
            for (int i = 0; i < expCount1; i++)
            {
                printf("Removing expired sandwich from holder1...\n");
                dequeue(holder1, error);
                s1Count--;
                printf("Done!\n");
                printf("after removing has: %d\n", s1Count);
            }
        }

        //HANDLE HOLDER 2 EXPIRED SANDWICHES
        if (s2Count > (EXPIRATION / NEW_SANDWICH_PERIOD) * NEW_SANDWICH_COUNT)
        {
            int expCount2 = s2Count - ((EXPIRATION / NEW_SANDWICH_PERIOD) * NEW_SANDWICH_COUNT);

            printf("Holder2 has %d expired sandwiches.\n", expCount2);
            for (int i = 0; i < expCount2; i++)
            {
                printf("Removing expired sandwich from holder2...\n");
                dequeue(holder2, error);
                s2Count--;
                printf("Done!\n");
                printf("after removing has: %d\n", s1Count);
            }
        }

        //DISPLAY DAY'S TOTALS
        if (counter == WORKDAY)
        {
            printf("Store is closing.\nToday's costs: %.2f\n", production);
            printf("Today's revenue: %.2f\n", profit);
            printf("Today's profit: %.2f\n", profit - production);
            break;
        }
    }

    //WRITE RESULTS TO FILE
    FILE *file = NULL;
    file = fopen("store_queue.txt", "w+");
    fputs("Results using queue: ", file);
    fprintf(file, "Today's revenue: %.2f\n", profit);
    fprintf(file, "Today's costs: %.2f\n", production);
    fprintf(file, "Today's profit: %.2f\n", profit - production);
    fclose(file);
}

void sandwichStoreStack()
{
    Stekas *holder1 = createStack();
    Stekas *holder2 = createStack();
    int counter = 0;
    int expirationCounter = 0;
    int s1Count = 0;
    int s2Count = 0;
    int *bin = NULL;
    double revenue = 0;
    int random = 0;
    double production = 0;

    int day = 0;
    int probability = 0;
    char buffer[255];
    FILE *fp = NULL;
    fp = fopen("params.txt", "r");
    fscanf(fp, "%d \n%d", &day, &probability);
    printf("Read: %d %d\n", day, probability);
    fclose(fp);

    srand(time(0));

    while (counter <= WORKDAY)
    {
        counter++;
        random = getRandom(1, 100);

        //HANDLE NEW SANDWICHES
        if (counter % NEW_SANDWICH_PERIOD == 0)
        {
            if (s1Count <= s2Count)
            {
                for (int i = 0; i < NEW_SANDWICH_COUNT; i++)
                {
                    printf("New sandwich added to Holder1!\n");
                    push(holder1, 1);
                    s1Count++;
                }
            } else
            {
                for (int i = 0; i < NEW_SANDWICH_COUNT; i++)
                {
                    printf("New sandwich added to Holder2!\n");
                    push(holder2, 1);
                    s2Count++;
                }
            }

            production += MANUFACTURE_PRICE * NEW_SANDWICH_COUNT;
            expirationCounter++;
        } else
        {
            expirationCounter++;
        }

        //HANDLE BUYER
        if (random >= CLIENT_CHANCE && (s1Count > 0 || s2Count > 0))
        {
            printf("A client comes in...\n");
            if (random >= HOLDER_SELECTION_PROBABILITY)
            {
                printf("Client buys sandwich from Holder1\n");
                pop(holder1, bin);
                s1Count--;
                revenue += PRICE;
                printf("Total profit: %.2f\n", revenue);
            } else
            {
                printf("Client buys sandwich from Holder2\n");
                pop(holder2, bin);
                s2Count--;
                revenue += PRICE;
                printf("Total profit: %.2f\n", revenue);
            }
        } else
        {
            printf("Waiting for clients...\n");
        }

        //HANDLE HOLDER 1 EXPIRED SANDWICHES
        if (s1Count > (EXPIRATION / NEW_SANDWICH_PERIOD) * NEW_SANDWICH_COUNT)
        {
            int expCount1 = s1Count - ((EXPIRATION / NEW_SANDWICH_PERIOD) * NEW_SANDWICH_COUNT);
            printf("Holder1 has %d expired sandwiches.\n", expCount1);
            for (int i = 0; i < expCount1; i++)
            {
                printf("Removing expired sandwich from holder1...\n");
                pop(holder1, bin);
                s1Count--;
                printf("Done!\n");
                printf("after removing has: %d\n", s1Count);
            }
        }

        //HANDLE HOLDER 2 EXPIRED SANDWICHES
        if (s2Count > (EXPIRATION / NEW_SANDWICH_PERIOD) * NEW_SANDWICH_COUNT)
        {
            int expCount2 = s2Count - ((EXPIRATION / NEW_SANDWICH_PERIOD) * NEW_SANDWICH_COUNT);

            printf("Holder2 has %d expired sandwiches.\n", expCount2);
            for (int i = 0; i < expCount2; i++)
            {
                printf("Removing expired sandwich from holder2...\n");
                pop(holder2, bin);
                s2Count--;
                printf("Done!\n");
                printf("after removing has: %d\n", s1Count);
            }
        }

        //DISPLAY DAY'S TOTALS
        if (counter == WORKDAY)
        {
            printf("Store is closing.\nToday's costs: %.2f\n", production);
            printf("Today's revenue: %.2f\n", revenue);
            printf("Today's profit: %.2f\n", revenue - production);
            break;
        }
    }

    //WRITE RESULTS TO FILE
    FILE *file = NULL;
    fputs("Results using stack: ", file);
    file = fopen("results_stack.txt", "w+");
    fprintf(file, "Today's revenue: %.2f\n", revenue);
    fprintf(file, "Today's costs: %.2f\n", production);
    fprintf(file, "Today's profit: %.2f\n", revenue - production);
    fclose(file);
}

int getRandom(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}