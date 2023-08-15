#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    printf("%s\n", text);

    int letters = count_letters(text);
    // printf("%d letters\n", letters);
    int words = count_words(text);
    // printf("%d words\n", words);
    int sentences = count_sentences(text);
    // printf("%d sentences\n", sentences);

    float grade = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8;
    if (grade > 16) {
        printf("Grade 16+\n");
    }
    else if (grade < 1) {
        printf("Before Grade 1\n");
    }
    else {
        printf("Grade %d\n", (int) round(grade));
    }
}

int count_letters(string text) {
    int counter = 0;
    for (int i = 0; i < strlen(text); i++) {
        if ((int) toupper(text[i]) >= 65 && (int) toupper(text[i]) <= 90) {
            counter++;
        }
    }
    return counter;
}

int count_words(string text) {
    int counter = 1;
    for (int i = 0; i < strlen(text) - 1; i++) {
        if ((int) text[i] == 32 && (int) text[i + 1] != 32) {
            counter++;
        }
    }
    if ((int) text[strlen(text)] == 32) {
            counter++;
    }
    return counter;
}

int count_sentences(string text) {
    int counter = 0;
    for (int i = 0; i < strlen(text); i++) {
        if ((int) text[i] == 33 || (int) text[i] == 46 || (int) text[i] == 63) {
            counter++;
        }
    }
    return counter;
}