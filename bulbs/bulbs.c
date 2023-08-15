#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string text = get_string("Message: ");
    for (int i = 0; i < strlen(text); i++) {
        int oneChar = (int) text[i];
        int bitVal[BITS_IN_BYTE];
        int index = BITS_IN_BYTE - 1;
        while (index >= 0) {
            bitVal[index] = oneChar % 2;
            oneChar /= 2;
            index--;
        }
        for (int j = 0; j < BITS_IN_BYTE; j++) {
            print_bulb(bitVal[j]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
