#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Here the idea of largest area of histogram is used------------------------

    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<int> st;
        int maxA=0;
        
        for(int i=0;i<=n;i++){
            
            while(!st.empty() && (i==n || heights[st.top()]>=heights[i])){
                int height = heights[st.top()];
                st.pop();
                int width;
                if(st.empty()) width = i;
                else width = i-st.top()-1;
                
                maxA= max(maxA, height*width);
            }
            
            st.push(i);
        }
        return maxA;
    }



int maximalAreaOfSubMatrixOfAll1(vector<vector<int>> &mat, int n, int m){
	// Write your code here.
	int maxArea=0;
	vector<int> heights(m, 0);


	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(mat[i][j]==1) heights[j]++;
            else heights[j]=0;
		}

        int area = largestRectangleArea(heights);
        maxArea = max(maxArea, area);
	}

    return maxArea;
	
}


// T.C --> O(N*(M + N)) (inside N is of the area of histogram function's time complexity)
// S.C --> O(M) + O(M) (heights vector + stack of size m)
int main(){
    return 0;
}