#include<iostream>
#include<bits/stdc++.h>
using namespace std;







// (i) Brute force----
vector<int> findMissingRepeatingNumbers(vector < int > a) {
    // Write your code here
    int n = a.size();
    int repetor=-1, missing=-1;
    for(int i=1;i<=n;i++){
        int cnt=0;
        for(int j=0;j<n;j++){
            if(a[j]==i) cnt++;
        }
        if(cnt==2) repetor = i;
        if(cnt==0) missing = i;
        if(repetor!=-1 && missing!=-1) return {repetor, missing};
    }
}
// T.C -> O(N^2)
// S.C -> O(1)









// (ii) Better soln-----(Hashing)
vector<int> findMissingRepeatingNumbers(vector < int > a) {
    // Write your code here
    int n = a.size();
    int repetor=-1, missing=-1;
    vector<int> hash(n+1, 0);
    for(int i=0;i<n;i++) hash[a[i]]++;
    for(int i=1;i<=n;i++){
        if(hash[i]==2) repetor = i;
        if(hash[i]==0) missing = i;
    }
    return {repetor, missing};
}
// T.C -> O(N)
// S.C -> O(N)










// (iii) Optimal soln----( USING   MATHS)
vector<int> findMissingRepeatingNumbers(vector < int > a) {
    // Write your code here
    long long n = a.size();
    
    // repetor -> x  .... 1,2,3,2 {x=2}
    // missing -> y  .... 1,2,3,4 {y=4}

    // S -> sum of array
    // SN -> sum of 1st natural nos.
    // S - SN = repetor - missing = x - y;

    // S2 -> sum of squares of array elements
    // S2N -> sum of squares of 1st natural nos.
    // S2 -S2N = repetor^2 - missing^2 = x^2 - y^2

    long long SN = (n*(n+1))/2;
    long long S2N = ((n)*(n+1)*(2*n+1))/6;
    long long S = 0, S2=0;

    for(int i=0;i<n;i++){
        S += a[i];
        S2 += (long long)a[i]*(long long)a[i];
    }

    long long diff = S - SN;      //  x-y
    long long add = (S2 - S2N)/diff;  //  x+y

    long long x = (add + diff)/2;
    long long y = add - x;

    return {(int)x, (int)y};

}
//  T.C -> O(N)
//  S.C -> O(1)
















// (iii) Optimal soln------------(USING   XOR)
vector<int> findMissingRepeatingNumbers(vector < int > a) {
    // Write your code here
    long long n = a.size();
    int xr = 0;
    for(int i=0;i<n;i++){
        xr = xr^a[i];
        xr = xr^(i+1);
    }

    //Now find 1st set from right
    int bitNo=0;
    while(1){
        if((xr & (1<<bitNo)) !=0){
            break;
        }
        bitNo++;
    }

    //Now segregating elements into two groups of '0' and '1'
    int zero=0;
    int one=0;

    //for array elements
    for(int i=0;i<n;i++){

        // part of 1 club
        if((a[i]&(1<<bitNo)) != 0){
            one = one^a[i];
        }
        // part of 0 club
        else{
            zero = zero^a[i];
        }
    }

    //for 1 to n elements
    for(int i=1;i<=n;i++){

        // part of 1 club
        if((i&(1<<bitNo)) != 0){
            one = one^i;
        }
        // part of 0 club
        else{
            zero = zero^i;
        }
    }

    // now checking which one is repeator and missing number from 'zero' and 'one'
    int cnt=0;
    for(int i=0;i<n;i++){
        if(a[i]==zero) cnt++;
    }
    if(cnt==2) return {zero, one};
    else return {one, zero};

}
// T.C -> O(N)
// S.C -> O(1)


// ANOTHER WAY OR WRITING ABOVE CODE--------------
vector<int> findMissingRepeatingNumbers(vector < int > a) {
    // Write your code here
    long long n = a.size();
    int xr = 0;
    for(int i=0;i<n;i++){
        xr = xr^a[i];
        xr = xr^(i+1);
    }

    //Now find 1st set from right
    int number = (xr & ~(xr -1));

    //Now segregating elements into two groups of '0' and '1'
    int zero=0;
    int one=0;

    //for array elements
    for(int i=0;i<n;i++){

        // part of 1 club
        if((a[i]&number) != 0){
            one = one^a[i];
        }
        // part of 0 club
        else{
            zero = zero^a[i];
        }
    }

    //for 1 to n elements
    for(int i=1;i<=n;i++){

        // part of 1 club
        if((i&number) != 0){
            one = one^i;
        }
        // part of 0 club
        else{
            zero = zero^i;
        }
    }

    // now checking which one is repeator and missing number from 'zero' and 'one'
    int cnt=0;
    for(int i=0;i<n;i++){
        if(a[i]==zero) cnt++;
    }
    if(cnt==2) return {zero, one};
    else return {one, zero};

}












// (iii) Optimal Soln-------------(USING  negating the array elements idea----)
vector<int> findMissingRepeatingNumbers(vector < int > a) {
    // Write your code here
     int missing,repeat;
        for(int i=0;i<a.size();i++){
            if(a[abs(a[i])-1]<0) repeat=abs(a[i]);
            else a[abs(a[i])-1]*=-1;
        }

        for(int i=0;i<a.size();i++){
            if(a[i]>0) missing=i+1;
        }

        return {repeat,missing};

}
//  T.C -> O(N)
//  S.C -> O(1)



int main(){
    return 0;
}