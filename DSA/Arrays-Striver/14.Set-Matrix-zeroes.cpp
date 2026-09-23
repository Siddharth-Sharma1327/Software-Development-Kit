#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Brute force-----------
void markRow(int i, vector<vector<int>> &matrix){
	for(int k=0;k<matrix[0].size();k++){
		if(matrix[i][k]!=0) matrix[i][k]=-1; 
	}
}

void markCol(int j, vector<vector<int>> &matrix){
	for(int k=0;k<matrix.size();k++){
		if(matrix[k][j]!=0) matrix[k][j]=-1; 
	}
}

vector<vector<int>> zeroMatrix(vector<vector<int>> &matrix, int n, int m) {
	// Write your code here.
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(matrix[i][j]==0){
				markRow(i, matrix);
				markCol(j, matrix);
			}
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(matrix[i][j]==-1) matrix[i][j]=0;
		}
	}
	return matrix;
}
// T.C -> O(N*M)*O(N+M) + O(N*M)
// S.C -> O(1)




// (ii) Better Soln-------------------
vector<vector<int>> zeroMatrix(vector<vector<int>> &matrix, int n, int m) {
	// Write your code here.
	vector<int> markRow(n, 0);
	vector<int> markCol(m, 0);

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(matrix[i][j]==0){
				markRow[i]=1;
				markCol[j]=1;
			}
		}
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(markRow[i]==1 || markCol[j]==1) matrix[i][j]=0;
		}
	}
	return matrix;
}
// T.C -> O(2*N*M)
// S.C -> O(N) + O(M)



// (iii) Optimal Soln------------------
vector<vector<int>> zeroMatrix(vector<vector<int>> &matrix, int n, int m) {
	// Write your code here.
	int col0 = 1;    //extra variable for col0 checking

	// marking first row and first col elements as 0 if they consists a 0
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(matrix[i][j]==0){
				if(j!=0){
					matrix[i][0]=0;
					matrix[0][j]=0;
				}else{
					matrix[i][0]=0;
					col0 = 0;
				}
			}
		}
	}

	// now iterating matrix excluding first row, first col as iterating them first will alter markRow and markCol which in turn would alter the matrix values
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			if(matrix[i][j]!=0){
				if(matrix[i][0]==0 || matrix[0][j]==0){
					matrix[i][j]=0;
				}
				
			}
			
		}
	}


	// Now row is iterated first as its elements are dependent on first cell which might get changed if we iterate column first and then that changed value would change the first row values
	for(int j=0;j<m;j++){
		if(matrix[0][0]==0) matrix[0][j]=0;
	}

	for(int i=0;i<n;i++){
		if(col0==0) matrix[i][0]=0;
	}
	return matrix;

}
// T.C -> O(2*N*M) + O(N) + O(M)
// S.C -> O(1)


int main(){
    return 0;
}