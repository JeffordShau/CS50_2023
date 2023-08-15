#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int index = 1;
int primeNums[1000];

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    primeNums[0] = 2;
    primeNums[1] = 3;
    if (number == 1) {
        return false;
    }
    else if (number == 2) {
        return true;
    }
    else if (number == 3) {
        return true;
    }
    else if (number != primeNums[index] + 2) { // build prime array if min > 3

        // printf("HI%d\n", number);
        // printf("INDEX: %d\n", index);
        for (int i = primeNums[index] + 2; i < number; i += 2) {
            for (int j = 1; i < index; j++) {
                if (number % primeNums[i] == 0) {
                    // printf("Break\n");
                    break;
                }
            }
            index++;
            primeNums[index] = i;
            // printf("%d: %d\n", index, primeNums[index]);
        }
    }
   else if (number % 2 == 1) {
        // printf("Pass\n");
        for (int i = 1; i < index; i++) {
            if (number % primeNums[i] == 0) {
                return false;
            }
        }
        index++;
        primeNums[index] = number;
        return true;
    }
    return false;
}
