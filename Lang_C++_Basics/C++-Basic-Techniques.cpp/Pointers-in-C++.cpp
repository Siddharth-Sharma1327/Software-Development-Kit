#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Void Pointers---------
 
void print( void* ptr, char type){
    switch (type)
    {
    case 'i':
        cout << *( (int*)ptr) << endl;   // (int*) is typcasting of 'ptr' into int pointer then referenced to access its value.
        break;
    case 'c':
        cout << *( (char*)ptr) << endl;
        break;
    default:
        break;
    }
}


int main(){

    int number = 5;
    char letter = 'a';
    print( &number, 'i' );
    print( &letter, 'c' );
    return 0;
}






// How to use pointers and arrays------
int main(){

    int luckyNumbers[] = {1,2,3,4,5};

    for(int i = 0; i < 5; i++){
        cout<<luckyNumbers[i]<<" ";
    }
    cout<<endl;

    for(int i = 0; i < 5; i++){
        cout<< *(luckyNumbers + i) <<" ";
    }
    cout<<endl;
    return 0;
}