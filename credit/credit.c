#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long creditNum;
    int sum = 0;
    int numOfDigits;

    creditNum = get_long("Insert Credit Card Number: ");
    numOfDigits = log10(creditNum) + 1;
    if (numOfDigits < 13 || numOfDigits > 16) {
        printf("INVALID\n");
    }

    // do {
    //     creditNum = get_long("Insert Credit Card Number: ");
    //     numOfDigits = log10(creditNum) + 1;
    // }
    // while (numOfDigits < 13 || numOfDigits > 16);

    else {
        long creditNumCopy = creditNum;

        while (creditNum > 10) {
            sum += creditNum % 10;
            // printf("%d\n", sum);
            creditNum /= 10;
            int partialSum = (creditNum % 10) * 2;
            if (partialSum > 9) {
                sum += (partialSum % 10) + (partialSum / 10 % 10);
            }
            else {
                sum += partialSum;
            }
            // printf("%d\n", sum);
            creditNum /= 10;
        }
        sum += creditNum % 10;
        // printf("SUM: %d", sum);

        if (sum % 10 == 0) {
            while (creditNumCopy > 99) {
                creditNumCopy /= 10;
            }
            if (numOfDigits == 16 && creditNumCopy >=51 && creditNumCopy <=55) {
                printf("MASTERCARD\n");
            }
            else if (numOfDigits == 15 && (creditNumCopy == 34 || creditNumCopy == 37)) {
                printf("AMEX\n");
            }
            else if ((numOfDigits == 13 || numOfDigits == 16) && creditNumCopy / 10 == 4) {
                printf("VISA\n");
            }
            else {
            printf("INVALID\n");
            }
        }
        else {
            printf("INVALID\n");
        }
    }
}