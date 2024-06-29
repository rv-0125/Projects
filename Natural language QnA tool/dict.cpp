// Do NOT add any other includes
#include "dict.h"
#include "Node.h"
#include <iostream>

Chaining ::Chaining()
{
    for (int i = 0; i < hashPrime; i++)
    {
        std::vector<Account> newV;
        bankStorage2d.push_back(newV);
    }
}

void Chaining::createAccount(std::string id, double count)
{
    // IMPLEMENT YOUR CODE HERE
    int key = hash(id);
    Account toInsert;
    toInsert.id = id;
    toInsert.balance = count;
    bankStorage2d[key].push_back(toInsert);
    counter++;
}

double Chaining::getBalance(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    for (auto x : bankStorage2d[hash(id)])
    {
        if (x.id == id && x.balance >= 0)
        {
            return x.balance;
            // x.balance+=count;
            break;
        }
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, double count)
{
    // IMPLEMENT YOUR CODE HERE
    for (auto &x : bankStorage2d[hash(id)])
    {
        if (x.id == id && x.balance >= 0)
        {
            x.balance += count;
            return;
        }
    };
    createAccount(id, count);
}

bool Chaining::doesExist(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    for (auto x : bankStorage2d[hash(id)])
    {
        if (x.id == id && x.balance >= 0)
        {
            return true;
            break;
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    for (auto &x : bankStorage2d[hash(id)])
    {
        if (x.id == id && x.balance >= 0)
        {
            x.balance = -1;
            counter--;
            return true;
            break;
        }
    }
    return false; // Placeholder return value
}
int Chaining::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return counter; // Placeholder return value
}

int Chaining::hash(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    // FNV-1
    uint16_t hash_value = 0x811c;
    const uint16_t fnv_prime = 0x0101;

    for (char byte : id)
    {
        hash_value ^= static_cast<uint8_t>(byte);
        hash_value *= fnv_prime;
    }
    hash_value = static_cast<int>(hash_value);
    return hash_value;
    // return 0; // Placeholder return value
}

void inst_snt(int book_code, int page, int paragraph, int sentence_no, string sentence, TrieNode *root);

Dict::Dict()
{
    // Implement your function here
    root = new TrieNode(true, true);
    /// snt = new TrieNode(true);
}

Dict::~Dict()
{
    // Implement your function here
    /// delete snt;
    delete root;
}

void make_links(TrieNode *root)
{
    vector<TrieNode *> v;               // queue implementation.
    root->bl_an = root;                 // setting root ka blue ancestor to root;
    for (TrieNode *child : root->child) // bfs start. this is level 1.
    {
        if (child)
        {
            child->bl_an = root; // children one away from root, set blue anc as root.
            v.push_back(child);  // add to queue.
        }
    }

    while (!v.empty()) // bfs continue.
    {
        TrieNode *w = v[0]; // queue.front
        v.erase(v.begin()); // queue.pop
        for (int i = 0; i < 128; i++)
        {
            TrieNode *child = w->child[i]; // wa basically from pseudocode.
            if (child)
            {
                TrieNode *x = w->bl_an;           // x is w ka blue ancestor.
                while (x != root && !x->child[i]) // if x is not suffix link and xa does not exist.
                {
                    x = x->bl_an; // go to x ka blue ancestor.
                }
                if (x->child[i]) // xa exists
                {
                    x = x->child[i]; // wa ka blue ancestor will be xa.
                }
                child->bl_an = x; // also includes case where x ka blue ancestor is root itself.
                if (x->isendword)
                {
                    child->gr_an = x; // if x is a proper pattern in dictionary then green ancestor to child.
                }
                else
                {
                    child->gr_an = x->gr_an; // else x ka green ancestor is child ka green ancestor.
                }
                v.push_back(child);
            }
        }
    }
}

void insert_word(TrieNode *root, int book_code, int page, int para, int sentence_no, int offset, string word)
{
    // insert the word into trie.
    TrieNode *curr = root;
    int flag = 0; // check if word already in trie.
    for (char c : word)
    {
        char c1 = tolower(c);
        int index = 0;
        offset++;
        if (!curr->child[index])
        {
            flag = 1; // flag is one if word not in trie.
            curr->child[index] = new TrieNode(string(1, c1), book_code, para, page, sentence_no, offset);
        }
        curr = curr->child[index];
        // if (flag == 0) // word in trie already so we do this shit for updating data vector. memory mngmt ka pata nahi tho.
        // {
        //     Datastorer d;
        //     d.book_code = book_code;
        //     d.page = page;
        //     d.para = para;
        //     d.sentence_no = sentence_no;
        //     d.offset = offset;
        //     curr->data.push_back(d);
        // }
    }
    curr->isendword = true;
    curr->wordcount++;
    if (flag == 0) // word in trie already so we do this shit for updating data vectoronly at end of word.
    {
        Datastorer d;
        d.book_code = book_code;
        d.page = page;
        d.para = para;
        d.sentence_no = sentence_no;
        d.offset = offset;
        curr->data.push_back(d);
    }
}

void insert_word1(TrieNode *root, int book_code, int page, int para, int sentence_no, int offset, string word)
{
    // insert the word into trie.
    TrieNode *curr = root;
    // int flag = 0; // check if word already in trie.
    for (char c : word)
    {
        char c1 = tolower(c);
        int index = c1;
        offset++;
        if (!curr->child[index])
        {
            // flag = 1; // flag is one if word not in trie.
            curr->child[index] = new TrieNode(true, true);
            curr->child[index]->id = string(1, c1);
            // Datastorer d;
            // d.book_code = book_code;
            // d.para = para;
            // d.page = page;
            // d.sentence_no = sentence_no;
            // d.offset = offset;
            // curr->child[index]->data.push_back(d);
            /// curr->child[index] = new TrieNode(string(1,c1), book_code, para, page, sentence_no, offset);
        }
        curr = curr->child[index];
    }
    curr->isendword = true;
    curr->wordcount++;
    // if (flag == 0) // word in trie already so we do this shit for updating data vector. memory mngmt ka pata nahi tho.
    // {
    Datastorer d;
    d.book_code = book_code;
    d.page = page;
    d.para = para;
    d.sentence_no = sentence_no;
    d.offset = offset;
    curr->data.push_back(d);
    // }
}

string separators = ". , - : ! \" \' ( ) ? [ ] ; @ — ˙";

bool check(char c, string separators) // checking character in separators.
{
    return separators.find(c) != string::npos;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    inst_snt(book_code, page, paragraph, sentence_no, sentence, root);
}

void inst_snt(int book_code, int page, int paragraph, int sentence_no, string sentence, TrieNode *root)
{
    // Implement your function here
    string word = "";
    for (int i = 0; i < sentence.size(); i++)
    {
        if (!check(sentence[i], separators))
        {
            word += sentence[i];
            if (i == sentence.size() - 1)
            {
                insert_word1(root, book_code, page, paragraph, sentence_no, 0, word);
                word = "";
            }
        }
        else
        {
            if (word != "")
            {
                insert_word1(root, book_code, page, paragraph, sentence_no, 0, word);
                word = "";
            }
        }
    }
    /// TrieNode *sent1 = new TrieNode;
    /// insert_word(sent1, book_code, page, paragraph, sentence_no, 0, sentence);
    ///  make_links(sent1); // <------
    /// snt->child.push_back(sent1);
}

TrieNode *search_word(TrieNode *root, string word) /// searching a word and returning that trienode.
{
    TrieNode *curr = root;
    for (char c : word)
    {
        c = tolower(c);
        int index = c;
        if (!curr->child[index])
        {
            return nullptr;
        }
        curr = curr->child[index];
    }
    return curr;
}

double Dict::get_word_count(string word)
{
    // Implement your function here
    TrieNode *ans = search_word(root, word);
    if (ans)
    {
        return ans->wordcount; // returning the wordcount.
    }
    return -1; // placeholder value
}

void enterDict(TrieNode *root, const string &currentWord, ofstream &outputFile) // basically pretty print.
{
    if (!root)
    {
        return;
    }

    string updatedCurrentWord = currentWord; // Create a copy for modifications

    for (int i = 0; i < 128; i++)
    {
        if (root->child[i]) // if exists.
        {
            updatedCurrentWord.push_back(i);                           // pushback character.
            enterDict(root->child[i], updatedCurrentWord, outputFile); // update the word.
            updatedCurrentWord.pop_back();                             // pop back then.
        }
    }

    if (root->isendword == true) // print if endofword is true.
    {
        outputFile << currentWord << ", " << root->wordcount << endl;
    }
}

void Dict::dump_dictionary(string filename)
{
    // Implement your function here
    ofstream outputFile(filename);
    if (outputFile.is_open())
    {
        enterDict(root, "", outputFile); // traverse and update the file.
    }
}

void showtrie(TrieNode *n)
{
    if (n == nullptr)
        return;
    cout << n->id << endl;
    for (TrieNode *x : n->child)
    {
        showtrie(x);
    }
}
