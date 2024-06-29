// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct Account {
    std::string id;
    double balance;
};

class BaseClass {
public:
    virtual void createAccount(std::string id, double count) = 0;
    virtual double getBalance(std::string id) = 0;
    virtual void addTransaction(std::string id, double count) = 0;
    virtual bool doesExist(std::string id) = 0;
    virtual bool deleteAccount(std::string id) = 0;
    virtual int databaseSize() = 0;
    virtual int hash(std::string id) = 0;

    std::vector<Account> bankStorage1d;
    std::vector<std::vector<Account> > bankStorage2d;
    
};

class Chaining : public BaseClass {
public:
    Chaining(); //override;
    void createAccount(std::string id, double count) override;
    double getBalance(std::string id) override;
    void addTransaction(std::string id, double count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
private:
    static const int hashPrime = 65537;
    int counter=0;
    // Other data members and functions specific to Chaining
};

class Datastorer
{
public:
    int book_code = 0;
    int page = 0;
    int para = 0;
    int offset = 0;
    int sentence_no = 0;
};

/// TrieNode implementation starts
class TrieNode
{
public:
    string id;                // stores the value eg. a,b,c
    vector<TrieNode *> child; // to store children
    bool isendword;           // true if node is endofword
    double wordcount;
    vector<Datastorer> data;
    TrieNode *par;   // parent of trienode
    TrieNode *gr_an; // green ancestor : dictionary suffix links
    TrieNode *bl_an; // blue ancestor : suffix links
    TrieNode()
    {
        id = "";
        child = vector<TrieNode *>(1, nullptr);
        this->isendword = false;
        this->wordcount = 0;
        data.clear();
        par = nullptr;
        gr_an = nullptr;
        bl_an = nullptr;
    }

    TrieNode(bool a, bool b)
    {
        id = "";
        child = vector<TrieNode *>(128, nullptr);
        this->isendword = false;
        this->wordcount = 0;
        data.clear();
        par = nullptr;
        gr_an = nullptr;
        bl_an = nullptr;
    }

    TrieNode(string s, int bk_code, int para, int page, int sentence_no, int offset)
    {
        id = s;
        child = vector<TrieNode *>(1, nullptr);
        this->isendword = false;
        data.clear();
        Datastorer d; // datastorer class for every letter inserted in the trie.
        d.book_code = bk_code;
        d.page = page;
        d.para = para;
        d.sentence_no = sentence_no;
        d.offset = offset;
        data.push_back(d);   // stored into vector.
        this->wordcount = 0; // wordcount updated at end of word as was before.
        par = nullptr;
        gr_an = nullptr;
        bl_an = nullptr;
    }

    TrieNode(bool a)
    {
        id = "";
        child = vector<TrieNode *>();
        this->isendword = false;
        data.clear();
        Datastorer d; // datastorer class for every letter inserted in the trie.
        d.book_code = 0;
        d.page = 0;
        d.para = 0;
        d.sentence_no = 0;
        d.offset = 0;
        data.push_back(d);   // stored into vector.
        this->wordcount = 0; // wordcount updated at end of word as was before.
        par = nullptr;
        gr_an = nullptr;
        bl_an = nullptr;
    }
};

class Dict
{
private:
    // You can add attributes/helper functions here
    TrieNode *root;
    ///TrieNode *snt;

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    double get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
    TrieNode* getRoot(){return root;}
};

