#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else {
        for (int i = 0; i < strlen(argv[1]); i++) {
            if (!(isdigit(argv[1][i]))) {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        int key = atoi(argv[1]);
        // printf("KEY: %d\n", key);
        string plaintext = get_string("Plaintext:  ");
        // printf("STRLEN: %lu\n", strlen(plaintext));
        char ciphertext[strlen(plaintext) + 1];

        for (int i = 0; i < strlen(plaintext); i++) {
            if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
                ciphertext[i] = (char) ((plaintext[i] - 'a' + key) % 26) + 'a';
            }
            else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
                ciphertext[i] = (char) ((plaintext[i] - 'A' + key) % 26) + 'A';
            }
            else {
                ciphertext[i] = plaintext[i];
            }
        }
        ciphertext[strlen(plaintext)] = '\0';

        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }

}