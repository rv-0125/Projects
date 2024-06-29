#include <assert.h>
#include <sstream>
// #include "NodeNew.h"
#include "qna_tool.h"
// #include "NodeNew.h"

using namespace std;

bool isSpecialCharacter(char c) {
    switch (c) {
        case ' ':
        case ',':
        case '.':
        case '-':
        case ':':
        case '!':
        case '\"':
        case '\'':
        case '(':
        case ')':
        case '?':
        case '[':
        case ']':
        case ';':
        case '@':
            return true;
        default:
            return false;
    }
}

void Unnecessary::insert(string word)
{
    TrieNode2 *curr = root;
    for (char c : word)
    {
        if (!curr->child[c - 'a'])
        {
            curr->child[c - 'a'] = new TrieNode2;
        }
        curr = curr->child[c - 'a'];
    }
    curr->isEndofWord = true;
}

bool Unnecessary::search(string word)
{
    TrieNode2 *curr = root;
    for (char c : word)
    {
        if (!curr->child[c - 'a'])
        {
            return false;
        }
        curr = curr->child[c - 'a'];
    }
    return curr->isEndofWord;
}

Unnecessary *unn_dictionary()
{
    Unnecessary *t = new Unnecessary;
    // insert one lettered words.
    for (int c = 'a'; c <= 'z'; c++)
    {
        t->insert(string(1, c));
    }
    // insert two lettered words->
    string word;
    for (char c = 'a'; c <= 'z'; c++)
    {
        for (char d = 'a'; d <= 'z'; d++)
        {
            word += c;
            word += d;
            t->insert(word);

            word.clear();
        }
    }
    // insert question words->
    t->insert("what");
    t->insert("who");
    t->insert("where");
    t->insert("when");
    t->insert("why");
    t->insert("can");
    t->insert("how");
    t->insert("the");
    // insert pronouns->
    t->insert("him");
    t->insert("her");
    t->insert("they");
    t->insert("them");
    t->insert("she");
    t->insert("you");
    t->insert("your");
    t->insert("their");
    // past tense
    t->insert("did");
    t->insert("not");
    t->insert("could");
    t->insert("would");
    t->insert("should");
    t->insert("was");
    t->insert("had");
    t->insert("have");
    t->insert("may");
    t->insert("might");
    // miscellenous
    t->insert("and");
    t->insert("will");
    t->insert("but");
    t->insert("very");
    t->insert("much");
    t->insert("too");
    t->insert("got");
    t->insert("all");
    t->insert("some");
    t->insert("none");
    t->insert("then");
    t->insert("this");
    t->insert("that");
    t->insert("those");
    t->insert("thus");
    t->insert("hence");
    t->insert("therefore");
    t->insert("henceforth");
    t->insert("nevertheless");
    t->insert("each");
    t->insert("are");
    t->insert("were");
    t->insert("cannot");
    t->insert("with");
    t->insert("about");
    t->insert("explain");
    t->insert("brief");
    t->insert("off");
    t->insert("many");
    t->insert("less");
    t->insert("few");
    t->insert("lot");
    t->insert("take");
    t->insert("took");
    t->insert("here");
    t->insert("there");
    t->insert("little");
    t->insert("best");
    t->insert("good");
    t->insert("any");
    t->insert("since");
    t->insert("well");
    t->insert("doing");
    t->insert("into");
    t->insert("other");
    t->insert("from");
    t->insert("for");
    t->insert("way");
    t->insert("hereafter");
    t->insert("such");
    t->insert("just");
    t->insert("only");
    t->insert("while");
    t->insert("still");
    t->insert("everything");
    t->insert("something");
    t->insert("nothing");
    t->insert("anything");
    t->insert("without");
    t->insert("yet");
    t->insert("being");
    t->insert("been");
    t->insert("both");
    t->insert("over");
    t->insert("often");
    t->insert("india");
    t->insert("never");
    t->insert("people");
    t->insert("again");
    t->insert("also");
    t->insert("even");
    t->insert("eventhough");
    t->insert("though");
    t->insert("just");
    t->insert("off");
    t->insert("has");
    t->insert("although");
    t->insert("however");
    t->insert("lieu");
    t->insert("whether");
    t->insert("upon");
    t->insert("next");
    t->insert("almost");
    t->insert("ago");
    t->insert("out");
    t->insert("made");
    t->insert("between");
    t->insert("draw");
    t->insert("attention");
    t->insert("bit");
    t->insert("explains");
    t->insert("explained");
    t->insert("explaining");
    t->insert("brief");
    t->insert("briefing");
    t->insert("mahatma");
    t->insert("gandhi");
    t->insert("autobiography");
    t->insert("collected");
    t->insert("works");
    return t;
}

vector<int> stringParse(string s)
{
    string a = "", b = "", c = "";
    int i = 1;
    while (s[i] != ',')
    {
        a += s[i];
        i++;
    }
    i++;
    while (s[i] != ',')
    {
        b += s[i];
        i++;
    }
    i++;
    while ((i + 1) != s.size())
    {
        c += s[i];
        i++;
    }
    vector<int> d;
    d.push_back(stol(a));
    d.push_back(stol(b));
    d.push_back(stol(c));
    return d;
}

string posString(int a, int b, int c)
{
    return "(" + to_string(a) + "," + to_string(b) + "," + to_string(c) + ")";
}

TrieNode *returnNode(TrieNode *root, string word)
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

void Count::insert(string word)
{
    Trie_count *curr = root;
    for (char c : word)
    {
        c = tolower(c);
        int index = c;
        if (!curr->child[index])
        {
            curr->child[index] = new Trie_count;
        }
        curr = curr->child[index];
    }
    curr->isEndofWord = true;
    curr->wordcount++;
}

Trie_count *Count::search(string word)
{
    Trie_count *curr = root;

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

string lowerConverter1(string word)
{
    string result = "";
    for (char x : word)
    {
        result = result + (char)tolower((char)x);
    }
    return result;
}

QNA_tool::QNA_tool()
{
    // Implement your function here
    ifstream storeCsv;
    storeCsv.open("unigram_freq.csv");
    string s;
    getline(storeCsv, s);
    while (getline(storeCsv, s))
    {
        string a = "", b = "";
        int i = 0;
        while (s[i] != ',')
        {
            a += s[i];
            i++;
        }
        i++;
        while (i != s.size())
        {
            b += s[i];
            i++;
        }
        csvStorer.addTransaction(a, stol(b));
    }
}

QNA_tool::~QNA_tool()
{
    // Implement your function here
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here
    mainStorage.insert_sentence(book_code, page, paragraph, sentence_no, sentence);
    return;
}

Node *QNA_tool::get_top_k_para(string question, int k)
{
    // Implement your function here
    Chaining words;
    vector<string> meow;
    int start = 0;
    Chaining meowtwo;
    Unnecessary *t = unn_dictionary();
    for (int i = 0; i < question.size(); i++)
    {
        if (question[start] == ' ' || question[start] == '.')
        {
            start++;
            continue;
        }
        //||question[i]=='˙'||question[i]=='—'
        if (isSpecialCharacter(question[i]))
        {
            if (i == 0)
            {
                start++;
                continue;
            }
            string x = lowerConverter1(question.substr(start, i - start));
            if (t->search(x) == false)
            {
                if (meowtwo.getBalance(x) <= 0)
                    meow.push_back(x);
                meowtwo.addTransaction(x, 1);
                start = i + 1;
                if (question[start] == ':')
                {
                    start++;
                    i++;
                }
                if (question[start] == ' ')
                {
                    start++;
                    i++;
                }
            }
        }
    }
    if (start != question.size())
    {
        string x = lowerConverter1(question.substr(start, question.size() - start));
        if (meowtwo.getBalance(x) <= 0)
            meow.push_back(x);
        meowtwo.addTransaction(x, 1);
    }
    // Chaining scoreOfWord;
    // for (string x : meow)
    // {
    //     scoreOfWord.createAccount(x, double((double(mainStorage.get_word_count(x) + 1)) / (double(csvStorer.getBalance(x) + 1))));
    // }
    topKPara = maxHeap(k);
    Chaining nonZeroPara;
    vector<string> paraLoc;
    TrieNode *root = mainStorage.getRoot();
    for (string word : meow)
    {
        TrieNode *work = returnNode(root, word);
        // cout<<"problem not here in word "<<word<<"\n";
        if (work)
        {
            vector<Datastorer> eachLoc = work->data;
            int i = 0;
            for (auto sth : eachLoc)
            {
                string x = posString(sth.book_code, sth.page, sth.para);
                if (nonZeroPara.getBalance(x) <= 0)
                    paraLoc.push_back(x);
                nonZeroPara.addTransaction(x, double((meowtwo.getBalance(word) * meowtwo.getBalance(word)) / mainStorage.get_word_count(x)));
            }
        }
    }
    for (string x : paraLoc)
    {
        vector<int> umm = stringParse(x);
        NodeNew a = NodeNew(umm[0], umm[1], umm[2], nonZeroPara.getBalance(x), 0);
        topKPara.insert(a);
    }
    topKPara.mergesort(topKPara.maxHeapArr, 0, k);
    arr = new Node[k];
    for (int i = 0; i < topKPara.size; i++)
    {
        arr[i] = Node(topKPara.maxHeapArr[i].book_code, topKPara.maxHeapArr[i].page, topKPara.maxHeapArr[i].paragraph, 0, 0);
    }
    for (int i = 0; i < k - 1; i++)
    {
        arr[k - 1 - i].right = &arr[k - 2 - i];
        arr[i].left = &arr[i + 1];
    }
    arr[k - 1].left = NULL;
    arr[0].right = NULL;
    return &arr[k - 1];
}

string separators2 = ". , - : ! \" \' ( ) ? [ ] ; @";
bool check2(char c, string separators2) // checking character in separators.
{
    return separators2.find(c) != string::npos;
}

Count *quest(string question)
{
    Count *ques;
    string word = "";
    for (int i = 0; i < question.size(); i++)
    {
        if (!check2(question[i], separators2))
        {
            word += question[i];
            if (i == question.size() - 1)
            {
                ques->insert(word);
                word = "";
            }
        }
        else
        {
            if (word != "")
            {
                ques->insert(word);
                word = "";
            }
        }
    }

    return ques;
}

void QNA_tool::query(string question, string filename)
{
    // Implement your function here
    // std::cout << "Q: " << question << std::endl;
    // std::cout << "A: "
    //           << "Studying COL106 :)" << std::endl;
    quest(question);
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph)
{

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;

    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence))
    {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ','))
        {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos)
            {
                token = token.substr(start, end - start + 1);
            }

            // Check if the element is a number or a string
            if (token[0] == '\'')
            {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            }
            else
            {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if (
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph))
        {
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node *root, int k, string API_KEY, string question)
{

    // first write the k paragraphs into different files

    Node *traverse = root;
    int num_paragraph = 0;

    while (num_paragraph < k)
    {
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();

    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}