// Do NOT add any other includes
#include "search.h"

void maxHeap::merge(NodeNew a[], NodeNew b[], int a_len, int b_len, NodeNew c[], int start)
{
    int i = 0, j = 0;
    while (i < a_len && j < b_len)
    {
        if (a[i].sentence_no < b[j].sentence_no)
        {
            c[start + i + j] = a[i];
            i++;
        }
        else
        {
            c[start + i + j] = b[j];
            j++;
        }
    }
    while (i < a_len)
    {
        c[start + i + j] = a[i];
        i++;
    }
    while (j < b_len)
    {
        c[start + i + j] = b[j];
        j++;
    }
}

void maxHeap::mergesort(NodeNew main[], int start, int main_len)
{
    if (main_len <= 1)
    {
        return;
    }
    int a_len = main_len / 2;
    int b_len = main_len - a_len;
    NodeNew *a = new NodeNew[a_len];
    NodeNew *b = new NodeNew[b_len];
    for (int k = 0; k < a_len; k++)
        a[k] = main[start + k];
    for (int k = 0; k < b_len; k++)
        b[k] = main[start + k + a_len];
    mergesort(a, 0, a_len);
    mergesort(b, 0, b_len);
    merge(a, b, a_len, b_len, main, start);
    delete[] a;
    delete[] b;
}

maxHeap::maxHeap()
{

}

maxHeap::~maxHeap()
{
    
}

void maxHeap::insert(NodeNew n)
{
    if(size==0)
    {
        maxHeapArr[0] = n;
        size++;
        return;
    }
    if(size<capacity-1)
    {
        maxHeapArr[size] = n;
        size++;
        int i = size - 1;
        while(i>0 && maxHeapArr[parIdx(i)].sentence_no>maxHeapArr[i].sentence_no)
        {
            NodeNew temp = maxHeapArr[parIdx(i)];
            maxHeapArr[parIdx(i)] = maxHeapArr[i];
            maxHeapArr[i] = temp;
            i = parIdx(i);
        }
    }
    else if((size == capacity-1) &&count==0)
    {
        count++;
        maxHeapArr[size] = n;
        size++;
        int i = size - 1;
        while(i>0 && maxHeapArr[parIdx(i)].sentence_no>maxHeapArr[i].sentence_no)
        {
            NodeNew temp = maxHeapArr[parIdx(i)];
            maxHeapArr[parIdx(i)] = maxHeapArr[i];
            maxHeapArr[i] = temp;
            i = parIdx(i);
        }
        mergesort(maxHeapArr, 0, size);
    }
    else if((size==capacity-1)&&count>0)
    {
        maxHeapArr[size] = n;
        size++;
        int i = size - 1;
        while(i>0 && maxHeapArr[parIdx(i)].sentence_no>maxHeapArr[i].sentence_no)
        {
            NodeNew temp = maxHeapArr[parIdx(i)];
            maxHeapArr[parIdx(i)] = maxHeapArr[i];
            maxHeapArr[i] = temp;
            i = parIdx(i);
        }
    }
    else 
    {
        if(n.sentence_no>maxHeapArr[0].sentence_no)
        {
            removeMin();
            insert(n);
        }
    }
}

void maxHeap::removeMin()
{
    size--;
    maxHeapArr[0] = maxHeapArr[size];
    HeapifyDown(0);
}

void maxHeap::HeapifyDown(int idx)
{
    if(idx==size-1)
        return;
    if(rightIdx(idx)==size)
    {
        if(maxHeapArr[size-1].sentence_no>maxHeapArr[idx].sentence_no)
            return;
        else
        {
            NodeNew temp = maxHeapArr[size-1];
            maxHeapArr[size-1] = maxHeapArr[idx];
            maxHeapArr[idx] = temp;
            return;
        }
    }
    if(leftIdx(idx)>=size)
        return;
    if(maxHeapArr[idx].sentence_no<maxHeapArr[leftIdx(idx)].sentence_no && maxHeapArr[idx].sentence_no<maxHeapArr[rightIdx(idx)].sentence_no)
        return;
    if(maxHeapArr[leftIdx(idx)].sentence_no<maxHeapArr[rightIdx(idx)].sentence_no)
    {
        NodeNew temp = maxHeapArr[leftIdx(idx)];
        maxHeapArr[leftIdx(idx)] = maxHeapArr[idx];
        maxHeapArr[idx] = temp;
        HeapifyDown(leftIdx(idx));
    }
    else 
    {
        NodeNew temp = maxHeapArr[rightIdx(idx)];
        maxHeapArr[rightIdx(idx)] = maxHeapArr[idx];
        maxHeapArr[idx] = temp;
        HeapifyDown(rightIdx(idx));
    }
}

SearchEngine::SearchEngine(){
    vector<Datastorer1*>v[128][128];
    // Implement your function here  
}

SearchEngine::~SearchEngine(){
    // Implement your function here  
}

int same(int i,int j){
    if(i>j)return 1;
    if(i<j)return -1;
    return 0;
}

int issame(Datastorer1*d1,Datastorer1*d2){
    if(same(d1->book_code,d2->book_code)!=0)return same(d1->book_code,d2->book_code);
    if(same(d1->page,d2->page)!=0)return same(d1->page,d2->page);
    if(same(d1->para,d2->para)!=0)return same(d1->para,d2->para);
    if(same(d1->sentence_no,d2->sentence_no)!=0)return same(d1->sentence_no,d2->sentence_no);
    if(d1->offset==-1+d2->offset)return 0;
    if(d1->offset>-1+d2->offset)return 1;
    else return -1;    

}

vector<Datastorer1*> combine(vector<Datastorer1*>v1,vector<Datastorer1*>v2){
    int i=0,j=0,k;
    vector<Datastorer1*>ans;
    int s1=v1.size(),s2=v2.size();
    while(i<s1 && j<s2){
        k=issame(v1[i],v2[j]);
        ///cout<<k<<endl;
        if(k==1)j++;
        else if(k==-1)i++;
        else{
            ans.push_back(v2[j]);
            i++;
            j++;
        }
    }
    return ans;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    sentence=" "+sentence;
    for(int i=0;i<sentence.size()-1;i++){
        int c1=tolower(sentence[i]);
        int c2=tolower(sentence[i+1]);
        Datastorer1*d=new Datastorer1(book_code,page,paragraph,sentence_no,i);
        v[c1][c2].push_back(d);

    }
    // Implement your function here  
    return;
}

int isissame(Datastorer1*d1,Datastorer1*d2){
    if(same(d1->book_code,d2->book_code)!=0)return same(d1->book_code,d2->book_code);
    if(same(d1->page,d2->page)!=0)return same(d1->page,d2->page);
    if(same(d1->para,d2->para)!=0)return same(d1->para,d2->para);
    if(same(d1->sentence_no,d2->sentence_no)!=0)return same(d1->sentence_no,d2->sentence_no);
    return same(d1->offset,d2->offset);  
}

void srch(string pattern,vector<Datastorer1*>(&v)[128][128],vector<Datastorer1*>&ans){
    if (pattern.size() == 1) {
        int i = pattern[0];
        ans.clear(); // Clear the vector to ensure it's empty
        for (int j = 0; j < 128; j++) {
            ans.insert(ans.end(), v[j][i].begin(), v[j][i].end());
        }

        // Sort ans in increasing order
        for (int i = 0; i < ans.size(); i++) {
            for (int j = i + 1; j < ans.size(); j++) {
                if (isissame(ans[i], ans[j]) > 0) {
                    swap(ans[i], ans[j]);
                }
            }
        }
        for(Datastorer1*d:ans){
            cout<<d->book_code<<" "<<d->page<<" "<<d->para<<" "<<d->sentence_no<<" "<<d->offset<<endl;
        }
        return;
    }
    int i=pattern[0];
    int j=pattern[1];
    ans=v[i][j];
    int pos=2;
/*     for(Datastorer1*d:ans){
        cout<<(char)i<<' '<<(char)j<<' '<<d->book_code<<" "<<d->page<<" "<<d->para<<" "<<d->sentence_no<<" "<<d->offset<<endl;
    } */
    while(pos<pattern.size()){
        int i=pattern[pos-1];
        int j=pattern[pos];
/*         for(Datastorer1*d:ans){
            cout<<(char)i<<' '<<(char)j<<' '<<d->book_code<<" "<<d->page<<" "<<d->para<<" "<<d->sentence_no<<" "<<d->offset<<endl;
        } */
        ans=combine(ans,v[i][j]);
        pos++;
    }
}

Node* convert(Datastorer1*d,string pattern){
    Node*n=new Node;
    ///cout<<d->book_code<<" "<<d->page<<" "<<d->para<<" "<<d->sentence_no<<" "<<d->offset<<endl;
    n->book_code=d->book_code;
    n->page=d->page;
    n->paragraph=d->para;
    n->sentence_no=d->sentence_no;
    n->offset=d->offset-pattern.size()+1;
    return n;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    vector<Datastorer1*>ans;
    srch(pattern,v,ans);
/*     for(Datastorer1*d:ans){
        cout<<d->book_code<<" "<<d->page<<" "<<d->para<<" "<<d->sentence_no<<" "<<d->offset<<endl;
    } */
    n_matches=ans.size();
    Node* head = nullptr;
    Node* p = nullptr;
    for (int i = 0; i < n_matches; i++) {
        Node* newNode = convert(ans[i], pattern);
        if (i == 0) {
            head = p = newNode;
        } else {
            p->right = newNode;
            newNode->left = p;
            p = newNode;
        }
    }

    // Implement your function here  
    if(n_matches==0)return nullptr;
    return head;
}

void show(Node*d){
    if(d==nullptr)return;
    cout<<d->book_code<<" "<<d->page<<" "<<d->paragraph<<" "<<d->sentence_no<<" "<<d->offset<<endl;
    show(d->right);
}

