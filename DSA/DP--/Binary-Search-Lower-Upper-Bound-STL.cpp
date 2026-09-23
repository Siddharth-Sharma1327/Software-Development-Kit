#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
// BINARY_SERACH IN STL----------(binary_serach( , , ))

// Check if X exists in the sorted array or not?

int a[] ={1, 4, 5, 8, 9};
bool res = binary_search(a, a+5, 3);

if(res==true) cout<<"TRUE"<<endl;
else cout<<"FALSE"<<endl;
res = binary_search(a, a+5, 4);
if(res==true) cout<<"TRUE"<<endl;
else cout<<"FALSE";

// For vector--> bool res = binary_search(a.begin(), a.end(), x) - a.begin();




// LOWER_BOUND IN STL ----------------(LOWER_BOUND( ,  , ))
int b[] {1, 4, 5, 6, 9, 9};

int ind = lower_bound(b, b+6, 4)-b;
cout<<ind<<endl;
ind = lower_bound(b, b+6, 7)-b;
cout<<ind<<endl;
ind = lower_bound(b, b+6, 10)-b;
cout<<ind<<endl;


// For vector--> ind = lower_bound(b.begin(), b.end(), x) - b.begin();




// UPPER_BOUND IN STL ----------------(UPPER_BOUND( , , ))

int c[] = {1, 4, 5, 6, 9, 9};

int ind1 = upper_bound(c,  c+6, 4) - c;
cout<<ind1<<endl;
ind1 = upper_bound(c, c+6, 7) - c;
cout<<ind1<<endl;
ind1 = upper_bound(c, c+6, 10) - c;
cout<<ind1<<endl;


// For vector---> ind1 = upper_bound(c.begin(), c.end(), x) - c.begin();



// ALL T.C IS O(logN)-------------------------------
    return 0;
}