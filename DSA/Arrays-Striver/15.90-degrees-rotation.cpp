#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// (i) Brute force---
void rotateMatrix(vector<vector<int>> &mat){
	// Write your code here.
	int n = mat.size();
	int m = mat[0].size();

	vector<vector<int>> ans(m, vector<int>(n, 0));

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			ans[j][n-1-i] = mat[i][j]; 
		}
	}
	mat=ans;
	
	
}
// T.C -> O(N*M)
// S.C -> O(N*M)


// (ii) OPtimal soln-----
void rotateMatrix(vector<vector<int>> &mat){
	// Write your code here.
	int n = mat.size();

	// transpose of matrix-----
	for(int i=0;i<n;i++){
		for(int j=0;j<i;j++){
			swap(mat[i][j], mat[j][i]); 
		}
	}

	// reverse the half columns of matrix---
	for(int i=0;i<n;i++){
		for(int j=0;j<n/2;j++){
			swap(mat[i][j], mat[i][n-1-j]);
		}
	}	
	
}
// T.C -> O(N*(N-1)/2) + O(N*(N/2))
// S.C -> O(1)


// Roatate  by 90 deg in anti-clocwise--
// idea---- first find transpose then swap the rows

// Roatate  by 90 deg in clocwise--
// idea---- first find transpose then swap the columns----same as above


int main(){
    return 0;
}