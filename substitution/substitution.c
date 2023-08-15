#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else {
        for (int i = 0; i < strlen(argv[1]); i++) {
            if (!(isalpha(argv[1][i]))) {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            for (int j = i + 1; j < strlen(argv[1]) - 1; j++) {
                if (argv[1][j] == argv[1][i]) {
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }
            }
        }

        char* plaintext = get_string("plaintext: ");
        char ciphertext[strlen(plaintext) + 1];

        for (int i = 0; i < strlen(plaintext); i++) {
            if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
                ciphertext[i] = toupper(argv[1][plaintext[i] - 'A']);
            }
            else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
                ciphertext[i] = tolower(argv[1][plaintext[i] - 'a']);
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