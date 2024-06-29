#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"

using namespace std;

class TrieNode2 // trienode for unncessary words.
{
public:
    vector<TrieNode2 *> child;
    bool isEndofWord;
    int weight;

    TrieNode2()
    {
        child = vector<TrieNode2 *>(26, nullptr);
        isEndofWord = false;
        weight = 0;
    }
};

class Unnecessary // unnecessary trie.
{
private:
    TrieNode2 *root;

public:
    Unnecessary()
    {
        root = new TrieNode2;
    }

    void insert(string word);

    bool search(string word);
};

class Trie_count // for para and document or corpus trie.
{
public:
    vector<Trie_count *> child;
    bool isEndofWord;
    float wordcount;

    Trie_count()
    {
        child = vector<Trie_count *>(128, nullptr);
        isEndofWord = false;
        wordcount = 0.0;
    }
};

class Count // for para and document trie.
{
private:
    Trie_count *root;

public:
    double score;
    Count()
    {
        root = new Trie_count;
        score = 0;
    }

    void insert(string word);

    Trie_count *search(string word);
};

class QNA_tool
{

private:
    // You are free to change the implementation of this function
    void query_llm(string filename, Node *root, int k, string API_KEY, string question);
    // filename is the python file which will call ChatGPT API
    // root is the head of the linked list of paragraphs
    // k is the number of paragraphs (or the number of nodes in linked list)
    // API_KEY is the API key for ChatGPT
    // question is the question asked by the user

    // You can add attributes/helper functions here

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */

    QNA_tool();  // Constructor
    ~QNA_tool(); // Destructor

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node *get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    std::string get_paragraph(int book_code, int page, int paragraph);
    // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // Searches through the corpus.

    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */

    // You can add attributes/helper functions here
    Dict mainStorage;
    Chaining csvStorer;
    maxHeap topKPara;
    Node *arr;
};