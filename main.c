#include <stdlib.h>
#include <time.h>
#include "store_stack/store_stack.h"
#include "store_queue/store_queue.h"

int main()
{
    int seed = time(0);

    sandwichStoreStack(seed);
    sandwichStoreQueue(seed);

    return 0;
}