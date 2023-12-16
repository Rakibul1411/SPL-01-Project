#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
using namespace std;

int CHAR_TO_INDEX(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return (int)c - (int)'a';
    }

    else
    {
        return (int)c - (int)'1' + 26;
    }
}


struct TrieNode
{
    struct TrieNode *children[36];


    bool isEndOfWord;
};


struct TrieNode *getNode()
{
    struct TrieNode *pNode = nullptr;

    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (pNode)
    {
        int i;

        pNode->isEndOfWord = false;

        for (i = 0; i < 36; i++)
        {
            pNode->children[i] = nullptr;
        }
    }

    return pNode;
}


void insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
        {
            pCrawl->children[index] = getNode();
        }

        pCrawl = pCrawl->children[index];
    }


    pCrawl->isEndOfWord = true;
}


bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
        {
            return false;
        }

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl->isEndOfWord);
}


// Function to load hashes from file into Trie
void loadHashes(const char* filename, TrieNode* root)
{

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening Hashset file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {

        if (!line.empty())
        {
            insert(root, line.c_str());
            //cout << "Inserted hash: " << line << endl;
        }

    }

    file.close();
}
