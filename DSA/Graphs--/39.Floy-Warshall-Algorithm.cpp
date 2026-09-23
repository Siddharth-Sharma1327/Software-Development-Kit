
#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Solution {
  public:
	void shortest_distance(vector<vector<int>>&matrix){
	    // Code here
	    int n = matrix.size();
	    
	    for(int i=0;i<n;i++){
	        for(int j=0;j<n;j++){
	            if(matrix[i][j]==-1){
	                matrix[i][j]=1e9;
	            }
	            if(i==j) matrix[i][j]=0;
	        }
	    }
	    
	    
	    for(int k=0;k<n;k++){
	        for(int i=0;i<n;i++){
	            for(int j=0;j<n;j++){
	                matrix[i][j] = min(matrix[i][j], matrix[i][k]+matrix[k][j]);
	            }
	        }
	    }
	    
	   // for ddetecting the negative cycle-----
	   //for(int i=0;i<n;i++){
	   //    if(matrix[i][i]<0){
	   //        cout<<"There is a negative cycle"<<endl;
	   //    }
	   //}
	    
	    
	    
	    
	    for(int i=0;i<n;i++){
	        for(int j=0;j<n;j++){
	            if(matrix[i][j]==1e9) matrix[i][j]=-1;
	        }
	    }
	    
	   // T.C --> O(N3)
	   // S.C --> O(N2)  (and not O(1)->we are using the given matrix only, though our space complexity is O(N2) as we are working on that much of space )
	    
	    
	}
};


