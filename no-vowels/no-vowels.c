// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string input);

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Error\n");
        return 1;
    }
    else {
        string replaced = replace(argv[1]);
        printf("%s\n", replaced);
    }
}

string replace(string input) {
    for (int i = 0; i < strlen(input); i++) {
        // printf("Pass\n");
        switch(input[i]) {
            case 'a':
                input[i] = (char) 54;
                break;
            case 'e':
                input[i] = (char) 51;
                // strcat(replaced, (string) ('e' - 46));
                break;
            case 'i':
                input[i] = (char) 49;
                // strcat(replaced, (string) ('i' - 48));
                break;
            case 'o':
                input[i] = (char) 48;
                // strcat(replaced, (string) ('o' - 49));
                break;
            default:
                break;
        }
    }
    return input;
}