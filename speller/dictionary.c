// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Dictionary size
int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    if (table[index] == NULL) {
        return false;
    }
    node *trav = table[index];
    while (trav != NULL) {
        if (strcasecmp(trav->word, word) == 0) {
            return true;
        }
        trav = trav->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // sum up alphabetic characters and index it
    int sum = 0;
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] == 39) {
            continue;
        }
        sum += toupper(word[i]) - 'A';
    }
    // printf("sum: %d\n", sum);
    return sum % 26;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dictionary_words = fopen(dictionary, "r");
    if (dictionary_words == NULL) {
        printf("Cannot open dictionary file\n");
        return false;
    }

    char buffer[LENGTH + 1];
    // read until newline
    // while (fgets(buffer, LENGTH + 1, dictionary_words) != NULL) {
    while (fscanf(dictionary_words, "%s", buffer) != EOF) {
        node *current = malloc(sizeof(node));
        // buffer[strlen(buffer) - 1] = '\0';
        strcpy(current->word, buffer);
        // printf("strlen: %lu\n", strlen(buffer));
        // printf("%s\n", current->word);
        int index = hash(buffer);
        // printf("index: %d\n", index);

        current->next = table[index];
        table[index] = current;
        dictionary_size++;
        // sleep(1);
    }
    fclose(dictionary_words);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) {
        if (table[i] != NULL) {
            node *back = table[i];
            node *front;
            while(back->next != NULL) {
                front = back->next;
                free(back);
                back = front;
            }
            free(back);
        }
    }
    return true;
}
