#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startPop;
    do {
        startPop = get_int("Start size: ");
    }
    while (startPop < 9);

    // TODO: Prompt for end size
    int endPop;
    do {
        endPop = get_int("End size: ");
    }
    while (endPop < startPop);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (startPop < endPop){
        startPop = startPop + startPop / 3 - startPop / 4;
        years++;
    }

    // TODO: Print number of years
    printf("Years: %d\n", years);
}
