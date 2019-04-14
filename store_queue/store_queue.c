#include "../data_structures/queue/queue.h"
#include <stdlib.h>
#include "../random.h"
#include <stdio.h>
#include <time.h>

int sandwichStoreQueue()
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

    int WORKDAY_LENGTH = 0;
    int CLIENT_PROBABILITY = 0;
    int NEW_SANDWICH_AMOUNT = 0;
    int NEW_SANDWICH_TIME = 0;
    int SANDWICH_EXPIRATION_TIME = 0;
    float SANDWICH_SELL_PRICE = 0;
    float SANDWICH_MANUFACTURE_PRICE = 0;
    FILE *fp = NULL;

    fp = fopen("params.txt", "r");

    fscanf(fp, "%d darbo dienos ilgis\n", &WORKDAY_LENGTH);
    fscanf(fp, "%d kliento tikimybe\n", &CLIENT_PROBABILITY);
    fscanf(fp, "%d nauju sumustiniu daznis\n", &NEW_SANDWICH_TIME);
    fscanf(fp, "%d nauju sumustiniu kiekis\n", &NEW_SANDWICH_AMOUNT);
    fscanf(fp, "%d sumustiniu galiojimo laikas\n", &SANDWICH_EXPIRATION_TIME);
    fscanf(fp, "%f sumustinio pardavimo kaina\n", &SANDWICH_SELL_PRICE);
    fscanf(fp, "%f sumustinio gamybos kaina\n", &SANDWICH_MANUFACTURE_PRICE);

    fclose(fp);

    srand(time(0));

    while (counter <= WORKDAY_LENGTH)
    {
        counter++;
        random = getRandom(1, 100);

        //HANDLE NEW SANDWICHES
        if (counter % NEW_SANDWICH_TIME == 0)
        {
            if (s1Count <= s2Count)
            {
                for (int i = 0; i < NEW_SANDWICH_AMOUNT; i++)
                {
                    printf("New sandwich added to Holder1!\n");
                    enqueue(holder1, 1, error);
                    s1Count++;
                }
            } else
            {
                for (int i = 0; i < NEW_SANDWICH_AMOUNT; i++)
                {
                    printf("New sandwich added to Holder2!\n");
                    enqueue(holder2, 1, error);
                    s2Count++;
                }
            }

            production += SANDWICH_MANUFACTURE_PRICE * NEW_SANDWICH_AMOUNT;
            expirationCounter++;
        } else
        {
            expirationCounter++;
        }

        //HANDLE BUYER
        if (random >= CLIENT_PROBABILITY && (s1Count > 0 || s2Count > 0))
        {
            printf("A client comes in...\n");
            if (random >= 50)
            {
                printf("Client buys sandwich from Holder1\n");
                dequeue(holder1, error);
                s1Count--;
                profit += SANDWICH_SELL_PRICE;
                printf("Total profit: %.2f\n", profit);
            } else
            {
                printf("Client buys sandwich from Holder2\n");
                dequeue(holder2, error);
                s2Count--;
                profit += SANDWICH_SELL_PRICE;
                printf("Total profit: %.2f\n", profit);
            }
        } else
        {
            printf("Waiting for clients...\n");
        }

        //HANDLE HOLDER 1 EXPIRED SANDWICHES
        if (s1Count > (SANDWICH_EXPIRATION_TIME / NEW_SANDWICH_TIME) * NEW_SANDWICH_AMOUNT)
        {
            int expCount1 = s1Count - ((SANDWICH_EXPIRATION_TIME / NEW_SANDWICH_TIME) * NEW_SANDWICH_AMOUNT);
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
        if (s2Count > (SANDWICH_EXPIRATION_TIME / NEW_SANDWICH_TIME) * NEW_SANDWICH_AMOUNT)
        {
            int expCount2 = s2Count - ((SANDWICH_EXPIRATION_TIME / NEW_SANDWICH_TIME) * NEW_SANDWICH_AMOUNT);

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
        if (counter == WORKDAY_LENGTH)
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

    return 0;
}
