//Aidan Huggins
//Dr. Torosdagli
//COP3502
//Lab Assignment 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
};

// Function to initialize a new TrieNode
struct TrieNode* createNode() 
{
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if(newNode) 
    {
        newNode->count = 0;
        for(int i = 0; i < ALPHABET_SIZE; i++) 
        {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

void insert(struct TrieNode* root, char *word) 
{
    struct TrieNode* node = root;
    int len = strlen(word);

    for(int i = 0; i < len; i++) 
    {
        int index = word[i] - 'a';
        if(index < 0 || index >= ALPHABET_SIZE) 
        {
            return;
        }
        if(!node->children[index]) 
        {
            node->children[index] = createNode();
            if(!node->children[index]) 
            {
                printf("Memory allocation failed\n");
                return;
            }
        }
        node = node->children[index];
    }
    // Marking the end of word
    node->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct TrieNode* root, char *word) 
{
    struct TrieNode* node = root;
    int len = strlen(word);

    for(int i = 0; i < len; i++) 
    {
        int index = word[i] - 'a';
        if(!node->children[index]) 
        {
            return 0; // Word not found
        }
        node = node->children[index];
    }
    return node->count;
}

// Deallocates the trie structure
void deallocateTrie(struct TrieNode* root) 
{
    if(root) 
    {
        for(int i = 0; i < ALPHABET_SIZE; i++) 
        {
            deallocateTrie(root->children[i]);
        }
        free(root);
    }
}

// Reads the dictionary file and stores words in pInWords
int readDictionary(char *filename, char **pInWords) 
{
    FILE *file = fopen(filename, "r");
    if(file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int numWords = 0;
    char word[100]; // Assuming maximum word length is 100
    while(fscanf(file, "%s", word) != EOF) 
    {
        pInWords[numWords] = strdup(word);
        numWords++;
    }
    fclose(file);
    return numWords;
}

int main(void) 
{
    char *inWords[256];
    int numWords = readDictionary("dictionary.txt", inWords);
    for(int i = 0; i < numWords; ++i) 
    {
        printf("%s\n", inWords[i]);
    }

    struct TrieNode *root = createNode();
    for(int i = 0; i < numWords; i++) 
    {
        insert(root, inWords[i]);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for(int i = 0; i < 5; i++) 
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }

    deallocateTrie(root);

    return 0;
}