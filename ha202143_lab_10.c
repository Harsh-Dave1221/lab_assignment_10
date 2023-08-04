#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count;
    struct Trie *children[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    if (node)
    {
        node->count = 0;
        for (int i = 0; i < 26; ++i)
        {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *node = pTrie;
    for (int i = 0; word[i] != '\0'; ++i)
    {
        int index = word[i] - 'a';
        if (!node->children[index])
        {
            node->children[index] = createTrie();
        }
        node = node->children[index];
    }
    node->count++;
}

// computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word)
{
    struct Trie *node = pTrie;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';
        if (!node->children[index])
        {
            return 0;
        }
        node = node->children[index];
    }
    return node->count;
}

// deallocates the trie structure
void deallocateTrie(struct Trie *pTrie)
{
    if (pTrie)
    {
        for (int i = 0; i < 26; ++i)
        {
            if (pTrie->children[i])
            {
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
    }
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    int numWords;
    fscanf(file, "%d", &numWords);

    for (int i = 0; i < numWords; ++i)
    {
        pInWords[i] = (char *)malloc(100 * sizeof(char));
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);

    return numWords;
}

int main(void)
{
    char *inWords[256];

    // read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    deallocateTrie(pTrie);

    for (int i = 0; i < numWords; ++i)
    {
        free(inWords[i]);
    }

    return 0;
}