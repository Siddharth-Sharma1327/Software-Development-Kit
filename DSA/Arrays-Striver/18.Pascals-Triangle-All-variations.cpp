#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// (i) R & C given find element in that place in pascal triangle-- "nCr" function
// value in pascal triangle is given by (n-1)C(r-1) at rth row and cth column

int nCr(int n, int r){
    long long res=1;
    for(int i=0;i<r;i++){
        res = res*(n-i);
        res = res/(i+1);
    }
    return res;
}
// ans -> nCr(R-1, C-1)
// T.C -> O(R)
// S.C -> O(1)


// (ii) generate Nth row of pascal triangle

// Brute force

vector<int> generateRow(int row){
    for(int c=1;c<=row;c++){
        cout<<nCr(row-1, c-1);
    }
}
// T.C -> O(row*c) = O(N*N)
// S.C -> O(1)

// Optimal soln----
vector<int> generateRow(int row){
    long long ans=1;
    vector<int> ansRow;
    ansRow.push_back(1);
    for(int col=1;col<row;col++){
        ans = ans*(row - col);
        ans = ans/(col);
        ansRow.push_back(ans);
    }
    return ansRow;
}
// T.C -> O(N)
// S.C -> O(1)


// (iii) print pascal triangle

// Brute force
vector<vector<int>> pascalTriangle(int N) {
    // Write your code here.
    vector<vector<int>> ans;

    for(int i=1;i<=N;i++){
        vector<int> temp;
        for(int col=1;col<=i;col++){
            temp.push_back(nCr(i-1, col-1));
        }
        ans.push_back(temp);
    }
    return ans;
}
// T.C -> O(N*N*N)
// S.C -> O(1)

// optimal soln
vector<int> generateRow(int row){
    long long ans=1;
    vector<int> ansRow;
    ansRow.push_back(1);
    for(int col=1;col<row;col++){
        ans = ans*(row - col);
        ans = ans/(col);
        ansRow.push_back(ans);
    }
    return ansRow;
}

vector<vector<int>> pascalTriangle(int N) {
    // Write your code here.
    vector<vector<int>> ans;

    for(int i=1;i<=N;i++){
        ans.push_back(generateRow(i));
    }
    return ans;
}
// T.C -> O(N*N)
// S.C -> O(1)

int main(){
    return 0;
}