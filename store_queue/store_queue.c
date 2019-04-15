#include "../data_structures/queue/queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "store_queue.h"
#include "../random.h"

int sandwichStoreQueue()
{
    int *error = NULL;
    queue *holder1 = createNewQueue(error);
    queue *holder2 = createNewQueue(error);
    int counter = 0;
    int q1Count = 0;
    int q2Count = 0;
    int *bin = NULL;
    double revenue = 0;
    int random = 0;
    double production = 0;
    FILE *fp = NULL;
    int totalSandwichCount = 0;
    double loses = 0;

    int WORKDAY_LENGTH = 0;
    int CLIENT_PROBABILITY = 0;
    int NEW_SANDWICH_AMOUNT = 0;
    int NEW_SANDWICH_TIME = 0;
    int SANDWICH_EXPIRATION_TIME = 0;
    float SANDWICH_SELL_PRICE = 0;
    float SANDWICH_MANUFACTURE_PRICE = 0;

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
            if (q1Count <= q2Count)
            {
                for (int i = 0; i < NEW_SANDWICH_AMOUNT; i++)
                {
                    printf("New sandwich added to Holder1!\n");
                    enqueue(holder1, 1, error);
                    q1Count++;
                    totalSandwichCount++;
                }
            } else
            {
                for (int i = 0; i < NEW_SANDWICH_AMOUNT; i++)
                {
                    printf("New sandwich added to Holder2!\n");
                    enqueue(holder1, 1, error);
                    q2Count++;
                    totalSandwichCount++;
                }
            }

            production += SANDWICH_MANUFACTURE_PRICE * NEW_SANDWICH_AMOUNT;
        }

        //HANDLE BUYER
        if (random >= CLIENT_PROBABILITY && (q1Count > 0 || q2Count > 0))
        {
            printf("A client comes in...\n");
            if (random >= 50 && q1Count > 0)
            {
                printf("Client buys sandwich from Holder1\n");
                dequeue(holder1, error);
                q1Count--;
                totalSandwichCount--;
                revenue += SANDWICH_SELL_PRICE;
                printf("Total profit: %.2f\n", revenue);
            } else
            {
                printf("Client buys sandwich from Holder2\n");
                dequeue(holder2, error);
                q2Count--;
                totalSandwichCount--;
                revenue += SANDWICH_SELL_PRICE;
                printf("Total profit: %.2f\n", revenue);
            }
        } else
        {
            printf("Waiting for clients...\n");
        }

        //HANDLE EXPIRED SANDWICHES
        if (totalSandwichCount > (SANDWICH_EXPIRATION_TIME / NEW_SANDWICH_TIME) * NEW_SANDWICH_AMOUNT)
        {
            int expired = totalSandwichCount - ((SANDWICH_EXPIRATION_TIME / NEW_SANDWICH_TIME) * NEW_SANDWICH_AMOUNT);

            if (q1Count >= q2Count)
            {
                for (int i = 0; i < expired; i++)
                {
                    printf("Removing expired sandwich from holder1\n");
                    dequeue(holder1, error);
                    loses += SANDWICH_MANUFACTURE_PRICE;
                    q1Count--;
                    totalSandwichCount--;
                }
            } else
            {
                for (int i = 0; i < expired; i++)
                {
                    printf("Removing expired sandwich from holder2\n");
                    dequeue(holder2, error);
                    loses += SANDWICH_MANUFACTURE_PRICE;
                    q2Count--;
                    totalSandwichCount--;
                }
            }
        }

        //AT THE END OF THE DAY
        if (counter == WORKDAY_LENGTH)
        {
            //REMOVE LEFTOVERS
            if (q1Count > 0)
            {
                for (int i = 0; i < q1Count; i++)
                {
                    printf("Removing expired sandwich at the end of the day from holder1\n");
                    dequeue(holder1, error);
                    q1Count--;
                    totalSandwichCount--;
                    loses += SANDWICH_MANUFACTURE_PRICE;
                }
            }

            if (q2Count > 0)
            {
                for (int i = 0; i < q2Count; i++)
                {
                    printf("Removing expired sandwich at the end of the day from holder2\n");
                    dequeue(holder2, error);
                    q2Count--;
                    totalSandwichCount--;
                    loses += SANDWICH_MANUFACTURE_PRICE;
                }
            }

            //DISPLAY DAY'S RESULTS
            printf("Store is closing.\nToday's costs: %.2f\n", production);
            printf("Today's revenue: %.2f\n", revenue);
            printf("Today's loses: %.2f\n", loses);
            printf("---------------\n");
            printf("Today's profit: %.2f\n", revenue - production - loses);
            break;
        }
    }

    //WRITE RESULTS TO FILE
    FILE *file = NULL;
    fputs("Results using queue: ", file);
    file = fopen("results_queue.txt", "w+");
    fprintf(file, "Today's revenue: %.2f\n", revenue);
    fprintf(file, "Today's costs: %.2f\n", production);
    fprintf(file, "Today's loses: %.2f\n", loses);
    fprintf(file, "---------------------\n");
    fprintf(file, "Today's profit: %.2f\n", revenue - production - loses);
    fclose(file);

    return 0;
}