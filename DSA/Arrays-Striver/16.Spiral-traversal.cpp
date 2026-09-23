#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Only one optimal approach is there------- if asked only to check Implementation idea and clean code
 
vector<int> spiralMatrix(vector<vector<int>>&MATRIX) {
    // Write your code here.
    vector<int> ans;
    int n = MATRIX.size();
    int m = MATRIX[0].size();
    
    int top=0;
    int bottom=n-1;
    int left=0;
    int right=m-1;


    while(left<=right && top<=bottom){

        for(int i=left;i<=right;i++){
            ans.push_back(MATRIX[top][i]);
        }
        top++;

        for(int i=top;i<=bottom;i++){
            ans.push_back(MATRIX[i][right]);
        }
        right--;

        if(top<=bottom){
            for(int i=right;i>=left;i--){
            ans.push_back(MATRIX[bottom][i]);
            }
            bottom--;
        }
        
        if(left<=right){
            for(int i=bottom;i>=top;i--){
            ans.push_back(MATRIX[i][left]);
            }
            left++;
        }
 
    }

    return ans;
}
// T.C -> O(N*M)
// S.C -> O(N*M)  ans array
int main(){
    return 0;
}