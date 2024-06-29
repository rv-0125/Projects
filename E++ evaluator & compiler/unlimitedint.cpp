#include<iostream>
#include "ulimitedint.h"



UnlimitedInt::UnlimitedInt(){
    this->size=1;
    this->sign=1;
    this->capacity=10;
    this->unlimited_int=new int[capacity];
}

UnlimitedInt::UnlimitedInt(string s) {
    capacity = s.length();
    size = 0;
    if (s[0] == '-') {
        sign = -1;
        s = s.substr(1);
    } else {
        sign = 1;
    }

    unlimited_int = new int[capacity]();

    for (int i = s.length() - 1; i >= 0; i--) {
        unlimited_int[size++] = s[i] - '0';
    }
}


UnlimitedInt::UnlimitedInt(int i){
    size = 0;
    capacity = 10;
    if(i<0){
        sign=-1;
    }else if(i>0){
        sign=1;
    }else{
        sign=0;
    }
    i = abs(i);
    unlimited_int = new int[capacity]();

    while (i > 0) {
        if (size == capacity) {
            capacity *= 2;
            int* new_unlimited_int = new int[capacity]();
            for (int j = 0; j < size; j++) {
                new_unlimited_int[j] = unlimited_int[j];
            }
            delete[] unlimited_int;
            unlimited_int = new_unlimited_int;
        }
        unlimited_int[size++] = i % 10;
        i /= 10;
    }

    if (size == 0) {
        size = 1;
    }

}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    this->size=sz;
    this->sign=sgn;
    this->capacity=cap;
    this->unlimited_int=new int[cap];
    for(int i=0;i<sz;i++){
        unlimited_int[i]=ulimited_int[i];
    }
}

UnlimitedInt::~UnlimitedInt(){
    size=0;
    capacity=0;
    sign=0;
    delete[] unlimited_int;
    unlimited_int=nullptr;
}

int UnlimitedInt::get_size(){
    return size;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
  
    if(i1->get_sign() != i2->get_sign()){
        if(i2->get_sign()==-1){
            i2->sign = 1; 
            UnlimitedInt* sum1 = sub(i1, i2); 
            return sum1;
        }
        else if(i1->get_sign()==-1){
            i1->sign = 1;  
            UnlimitedInt* sum1 = sub(i2, i1); 
            return sum1;
        }
    }
    int signature = 1;
    if(i1->get_sign() == -1){
        signature = -1;
    }
    int carry=0;
    int s1=i1->get_size();
    int s2=i2->get_size();
    int maxi= std::max(s1,s2);
    int s3= maxi;
    
    int* new_unlimited_int = new int[s3+1];
    
    for (int i = 0; i < maxi; i++) {
            int temp = carry;
            if (i < s1)
                temp += i1->unlimited_int[i];
            if (i < s2)
                temp += i2->unlimited_int[i];

            new_unlimited_int[i]= temp % 10; 
            carry = temp / 10;          
        }
    if (carry > 0) {
        new_unlimited_int[s3]=carry;
        s3++;
        
    }
    else{
        int* fin = new int[s3];
        for(int i=0;i<s3;i++){
            fin[i] = new_unlimited_int[i];
        }
        new_unlimited_int = fin;
    }
    UnlimitedInt* sum1 = new UnlimitedInt(new_unlimited_int,s3,signature,s3);
    return sum1;
    
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->get_sign() * i2->get_sign() == -1) {
        if (i1->get_sign() == 1) {
            i2->sign = 1;
            UnlimitedInt* diff = add(i1, i2);
            i2->sign = -1;
            return diff;
        } else {
            i1->sign = 1;
            UnlimitedInt* diff = add(i1, i2);
            diff->sign = -1;
            i1->sign = -1;
            return diff;
        }
    } else if (i1->get_sign() == -1 && i2->get_sign() == -1) {
        i1->sign = 1;
        i2->sign = 1;
        UnlimitedInt* diff = sub(i2, i1);
        return diff;
    }

    int s1 = i1->get_size();
    int s2 = i2->get_size();
    int* big = i1->unlimited_int;
    int* small = i2->unlimited_int;
    int signature = 1;
    int n1 = s1, n2 = s2;

    if (s2 > s1) {
        big = i2->unlimited_int;
        small = i1->unlimited_int;
        signature = -1;
        n1 = s2;
        n2 = s1;
    } else if (s1 == s2) {
        for (int i = 0; i < s1; i++) {
            if (i1->unlimited_int[s1 - 1 - i] < i2->unlimited_int[s2 - 1 - i]) {
                big = i2->unlimited_int;
                small = i1->unlimited_int;
                signature = -1;
                n1 = s2;
                n2 = s1;
                break;
            } else if (i1->unlimited_int[s1 - 1 - i] > i2->unlimited_int[s2 - 1 - i]) {
                break;
            }
        }
    }

    int carry = 0;
    int* new_unlimited_int = new int[n1];

    for (int i = 0; i < n2; i++) {
        int sub = (big[i] - small[i] - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        } else {
            carry = 0;
        }
        new_unlimited_int[i] = sub;
    }

    for (int i = n2; i < n1; i++) {
        int sub = (big[i] - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        } else {
            carry = 0;
        }
        new_unlimited_int[i] = sub;
    }
    
    int i=n1-1;
    while(i>=0 && new_unlimited_int[i]==0){
        n1--;
        i--;
    }

    UnlimitedInt* diff = new UnlimitedInt(new_unlimited_int, n1, signature, n1);
    delete[] new_unlimited_int; // Delete the dynamically allocated array
    return diff;
}


UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* product=new UnlimitedInt();
    if(i1->get_sign()!=i2->get_sign()){
        product->sign=-1;
    }

    if(i1->get_size()==1&& i1->get_array()[0]==0 || i2->get_size()==1&& i2->get_array()[0]==0){
        return new UnlimitedInt();
    }
    int s1= i1->get_size();
    int s2= i2->get_size();
    int carry=0;
    product->capacity=s1+s2;
    int* new_unlimited_int = new int[product->capacity]();
    for (int j = 0; j < product->capacity; j++) {
        new_unlimited_int[j] = 0;
    }
    delete[] product->unlimited_int;
    product->unlimited_int = new_unlimited_int;
    UnlimitedInt* b = (s1 >= s2) ? i1 : i2; 
    UnlimitedInt* s = (s1 < s2) ? i1 : i2; 

    for(int i=0;i<s->size;i++){
        for(int j=0;j<b->size;j++){
            int temp= s->unlimited_int[i] * b->unlimited_int[j];
            temp=temp+ carry;
            temp+=product->unlimited_int[i+j];
            product->unlimited_int[i+j]=temp %10;
            carry=temp/10;
        }
    }
    product->size=s1+s2;
    int k=s1+s2-1;
    while(k>=0 && product->unlimited_int[k]==0){
        product->size--;
        k--;
    }
    if(carry>0){
        product->unlimited_int[k+1]=carry;
        product->size++;
    }

    return product;
}



int compare(int* a1, int* a2, int low1, int low2, int high1, int high2) {
    int count = 0;

    if (high1 > high2 ) {
        return 1;
    }
    if (high1 < high2 ) {
        return 2;
    }
    while (low1 <= high1 && low2 <= high2) {
        if (a1[low1] > a2[low2]) {
            count = 1;
            break;
        }
        else if (a1[low1] < a2[low2]) {
            count = 2;
            break;
        }
        low1++;
        low2++;
    }

    return count;
}


bool comp(int* a,int* b, int sz, int low){
    for(int i=0;i<sz;i++){
        if(a[low+i]<b[i]){
            return true;
        }
        else if(a[low+i]>b[i]){
            return false;
        }
    }
    return false;
}

void subt(int* a, int* b, int sz, int low){
    int itr1 = low+sz-1;
    int itr2 = sz-1;
    int borrow = 0;
    int diff = 0;
    while (itr2 >= 0) {
        diff = a[itr1] - b[itr2] - borrow;
        if (diff < 0) {
            diff = 10 + diff;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        a[itr1] = diff;
        itr1--;
        itr2--;
    }

}


UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {
    int final_sgn = (i1->sign * i2->sign);
    UnlimitedInt* i11=new UnlimitedInt(i1->get_array(),i1->get_capacity(),i1->get_sign(),i1->get_size());
    UnlimitedInt* i21=new UnlimitedInt(i2->get_array(),i2->get_capacity(),i2->get_sign(),i2->get_size());

    if ((i11->size == 1 && i11->unlimited_int[0] == 0) || (i21->size == 1 && i21->unlimited_int[0] == 0))  {
        return new UnlimitedInt("0");
    }

    if (i11->get_size()<i21->get_size()) {
        return new UnlimitedInt("0");
    }
    int s1=i11->get_size();
    int s2=i21->get_size();
     if (s1==s2) {
        int* arr1 = new int[s1];
        int* arr2 = new int[s2];
        for(int i=0;i<s1;i++){
            arr1[i]=i11->unlimited_int[s1-i-1];
        }
        for(int i=0;i<s2;i++){
            arr2[i]=i11->unlimited_int[s2-i-1];
        }
        int u1 = s1 - 1;
        int u2 = s2 - 1;
        int ref = compare(arr1, arr2, 0, 0, u1, u2);
        if (ref == 2) {
            
                UnlimitedInt* res = new UnlimitedInt("0");
                return res;
        }
            
    }

    int size = 0;
    int* a = new int[i11->size];
    int* b = new int[i21->size];
    for (int i = 0; i < s1; i++) {
        a[i] = i11->unlimited_int[s1-1-i];
    }
    for (int i = 0; i < s2; i++) {
        b[i] = i21->unlimited_int[s2-i-1];
    }

    int* quo= new int[s1];
    for(int i=0;i<s1;i++){
        quo[i]=-1;
    }
    int j=0;
    for(int i=0;i<=(s1-s2);i++){
        int x = 0;
        while(!comp(a,b,s2,i)){
            x++;
            subt(a,b,s2,i);
        }
        quo[s1-1-j]=x;
        j++;
        
    }
    // for(int i=0;i<s1;i++){
    //     cout<<quo[i];
    //     cout<<endl;
    // }
    
    int sz=j;
    int count=0;
    for(int i=0;i<s1;i++){
        if(quo[i]==-1){
            count=i+1;
        }
    }
    // cout<<"count"<<count<<endl;
    for (int i = count; i < s1; i++) {
        quo[i - count] = quo[i];
        
    }
    // for(int i=0;i<s1;i++){
    //     cout<<quo[i];
    //     cout<<endl;
    // }
   

    UnlimitedInt* result = new UnlimitedInt(quo, sz, final_sgn, sz);

    bool allZero = true;
    for (int i = 0; i < size; i++) {
        if (a[i] != 0) {
            allZero = false;
            break; 
        }
    }


    return result;
}


UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* res= div(i1,i2);
    // cout<<"array";
    // for(int i=0;i<res->get_size();i++){
    //     cout<<res->unlimited_int[i];
    // }
    // cout<<endl;
    UnlimitedInt* mult= mul(res,i2);
    // cout<<"array";
    // for(int i=0;i<mult->get_size();i++){
    //     cout<<mult->unlimited_int[i];
    // }
    // cout<<endl;
    UnlimitedInt* rem= sub(i1,mult);
    return rem;
}

string UnlimitedInt::to_string(){
    if (size == 1 && unlimited_int[0] == 0) {
        return "0";
    }
    string answer;
    if (sign == -1) {
        answer += "-";
    }
    for (int i = size-1; i >=0; i--) {
        answer += std::to_string(unlimited_int[i]);
    }

    return answer;

}





// int main() {
//     // Create UnlimitedInt objects
//     UnlimitedInt num1("123456789012345678901234567890");
//     UnlimitedInt num2("187654321098765432109876543210");
//     UnlimitedInt num3(12345);
//     UnlimitedInt num4(-1234577888);
//     UnlimitedInt num5("10");
//     std::cout << "num5: " << num5.to_string() << std::endl;

//     // Perform arithmetic operations
//     UnlimitedInt* sum = UnlimitedInt::add(&num1, &num2);
//     UnlimitedInt* diff = UnlimitedInt::sub(&num1, &num2);
//     UnlimitedInt* product = UnlimitedInt::mul(&num4, &num5);
//     UnlimitedInt* quotient = UnlimitedInt::div(&num4, &num3);
//     UnlimitedInt* remainder = UnlimitedInt::mod(&num4, &num3);

//     // Display results
//     std::cout << "num1: " << num1.to_string() << std::endl;
//     std::cout << "num2: " << num2.to_string() << std::endl;
//     std::cout << "num3: " << num3.to_string() << std::endl;
//     std::cout << "num4: " << num4.to_string() << std::endl;
    

//     std::cout << "Sum: " << sum->to_string() << std::endl;
//     std::cout << "Difference: " << diff->to_string() << std::endl;
//     std::cout << "Product: " << product->to_string() << std::endl;
//     std::cout << "Quotient: " << quotient->to_string() << std::endl;
//     std::cout << "Remainder: " << remainder->to_string() << std::endl;

//     // Clean up dynamically allocated memory
//     delete sum;
//     delete diff;
//     delete product;
//     delete quotient;
//     delete remainder;

//     return 0;
// }
