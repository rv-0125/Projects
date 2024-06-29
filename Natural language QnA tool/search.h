// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
// #include "NodeNew.h"
using namespace std;

class NodeNew {
public: 
    NodeNew* left;
    NodeNew* right;

    int book_code;
    int page;
    int paragraph;
    double sentence_no;
    int offset;

    NodeNew(){};
    NodeNew(int b_code, int pg, int para, double s_no, int off)
    {
        book_code = b_code;
        page = pg;
        paragraph = para;
        sentence_no = s_no;
        offset = off;
    }
};

class maxHeap{
private:
    int capacity = 0;
    int count = 0;

public:
    int size = 0;
    NodeNew* maxHeapArr;
    maxHeap();
    maxHeap(int k){maxHeapArr = new NodeNew[k];capacity = k;return;};
    int parIdx(int i){return (i-1)/2;};
    int leftIdx(int i){return 2*i+1;};
    int rightIdx(int i){return 2*i+2;};
    void insert(NodeNew n);
    void removeMin();
    void HeapifyDown(int i);
    void merge(NodeNew a[], NodeNew b[], int a_len, int b_len, NodeNew c[], int start);
    void mergesort(NodeNew main[], int start, int main_len);
    ~maxHeap();
};

class Datastorer1
{
public:
    int book_code = 0;
    int page = 0;
    int para = 0;
    int offset = 0;
    int sentence_no = 0;
    Datastorer1();
    Datastorer1(int book_code, int page, int paragraph, int sentence_no,int offset){
        this->book_code=book_code;
        this->page=page;
        this->para=paragraph;
        this->offset=offset;
        this->sentence_no=sentence_no;
    }
};

class SearchEngine {
private:
    // You can add attributes/helper functions here

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
    vector<Datastorer1*>v[128][128];


    

};