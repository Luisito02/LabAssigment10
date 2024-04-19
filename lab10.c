#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 26

// Trie node structure
struct TrieNode {
    struct TrieNode* children[ALPHABET];
    int count;
};

// Trie structure
struct Trie
{
        struct TrieNode* root;	
};
// Helper function to create a new trie node
struct TrieNode* createNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (newNode) {
        newNode->count = 0;
        for (int i = 0; i < ALPHABET; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
     if (!pTrie || !word)
        return;
    struct TrieNode* currentNode = pTrie->root;
    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';
        if (!currentNode->children[index]) {
            currentNode->children[index] = createNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (!pTrie || !word)
        return 0;

    struct TrieNode* currentNode = pTrie->root;
    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';
        if (!currentNode->children[index]) {
            return 0;
        }
        currentNode = currentNode->children[index];
    }
    return currentNode->count;
}
// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (!pTrie)
        return NULL;
    if (pTrie->root) {
        for (int i = 0; i < ALPHABET; i++) {
            if (pTrie->root->children[i]) {
                deallocateTrie(pTrie->root->children[i]);
            }
        }
        free(pTrie->root);
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
     struct Trie* pTrie = (struct Trie*)malloc(sizeof(struct Trie));
    if (pTrie) {
        pTrie->root = createNode();
    }
    return pTrie;
}
// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *dictionary, char **pInWords)
{
    FILE* file = fopen("dictionary.txt", "r");
    if (!file) {
        printf("Error opening file: %s\n", dictionary);
        return 0;
    }

    int numWords;
    fscanf(file, "%d", &numWords);

    for (int i = 0; i < numWords; i++) {
        pInWords[i] = (char*)malloc(256 * sizeof(char));
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}