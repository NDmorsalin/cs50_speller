// Implements a dictionary's functionality
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
int count = 0;


//convert char to index, a=0, b=1 etc...
int char_index(char C)
{
    return (int)(tolower(C)) - 97;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int I = char_index(word[0]);

    struct node* _this = table[I];  // Initialize _this
    while ( _this != NULL)
    {
        if (strcasecmp(_this->word, word) == 0)
        {
            return true;
        }
        _this = _this->next;
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    /* allocate node */
    struct node* tmp = (struct node*) malloc(sizeof(struct node));
    if (tmp == NULL) {
        printf("Out of memory\n");
        return 0;
    }

    strcpy(tmp->word, word);


    int I = char_index(word[0]);
    if(table[I] == NULL)
    {
        table[I] = (struct node*)malloc(sizeof(struct node));
        if (table[I] == NULL) {
            printf("Out of memory\n");
            return 0;
        }
    }
    else
    {
        /* link the old list off the new node */
        tmp->next = table[I]->next;
    }
    table[I]->next = tmp;

    return 1;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char *word[LENGTH + 1];


    while(fscanf(dict, "%s", *word) != EOF)
    {
        int hash_succeed = hash(*word);

        if(hash_succeed == 0)
        {
            return false;
        }
        else
        {
            count += hash_succeed;
        }
    }
    fclose(dict);
    return !(count == 0);
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int I = 0; I < N; I++)
    {
        struct node* _this = table[I];  // Initialize _this
        while ( _this != NULL)
        {
            struct node* tmp = _this;
            _this = _this->next;

            free(tmp);
        }
    }
    return true;
}
