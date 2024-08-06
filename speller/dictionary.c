// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char perm_word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N =
    3079; // I've chosen a prime number between 2k - 5k, as I expect inputs of few thousands words

unsigned int word_count = 0;

// Hash table
node *table[N];

// Checks if a word is in the dictionary
bool check(const char *word)
{
    // Normalize word for hashing if necessary
    char temp_word[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        temp_word[i] = tolower(word[i]);
    }
    temp_word[len] = '\0'; // Null-terminate the string

    // Get the hash index
    unsigned int index = hash(temp_word);

    // Search in the linked list at that index
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->perm_word, word) == 0)
        {
            return true; // Word found
        }
    }

    return false; // Word not found
}

// Hashes word to a number using the sdbm algorithm
// Credits: Hash function guidance provided by ChatGPT from OpenAI
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0; // Initialize hash value to zero
    int c;                       // Variable to store the ASCII value of each character

    // Process each character in the string
    while ((c = *word++))
    {
        // Mix in the character's ASCII value into the hash_value using bit manipulation
        hash_value = c + (hash_value << 6) + (hash_value << 16) - hash_value;
    }

    // Map the hash value to one of the buckets in the hash table
    return hash_value % N; // N is the number of buckets in the hash table
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        fprintf(stderr, "Could not open dictionary file: %s\n", dictionary);
        return false;
    }

    // word buffer
    char temp_word[LENGTH + 1];

    // Read each word in the file
    while (fscanf(source, "%s", temp_word) == 1)
    {
        // Normalize the word to lowercase for consistent hashing
        for (int i = 0; temp_word[i]; i++)
        {
            temp_word[i] = tolower(temp_word[i]);
        }

        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            // Handle the memory allocation error, possibly by freeing already allocated resources
            // and returning false
            fclose(source);
            return false;
        }

        // Copy the word from temporary to permanent storage in the node
        strcpy(new_node->perm_word, temp_word);

        // Calculate hash index and add to the hash table
        unsigned int index = hash(temp_word); // Calculate the hash index for the word, determining
                                              // which bucket to use in the hash table.
        new_node->next = table[index]; // Set the new node's "next" pointer to point to the current
                                       // head of the linked list at the calculated bucket index.
        table[index] =
            new_node; // Update the head of the linked list at the bucket index to be the new node,
                      // effectively inserting the node at the beginning of the list.

        word_count++; // Count each time a word is added
    }

    // Close the dictionary file
    fclose(source);

    // if nothing fails
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
