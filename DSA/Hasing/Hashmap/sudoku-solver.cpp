#include<iostream>
#include<bits/stdc++.h>
using namespace std;


bool row(vector<vector<int>> bs, int i, int t, int n){
    for(int j=0;j<n;j++){
        if(bs[i][j]==t){
            return false;
        }
    }
    return true;
}

bool col(vector<vector<int>> bs, int j, int t, int n){
    for(int k=0;k<n;k++){
        if(bs[k][j]==t){
            return false;
        }
    }
    return true;
}

bool matrix(vector<vector<int>> bs, int i, int j, int t){
    int z=i/3;
    int r=j/3;
    for(int x=3*z;x<z+3;x++){
        for(int y=3*r;y<r+3;r++){
            if(bs[i][j]==t){
                return false;
            }
        }
    }

    return true;
}
bool solve(vector<vector<int>> bs, int i, int j, int n){
    if(bs[i][j]!=0){
        if(j<n-1){
            j++;
        }else if(j==n-1 && i<n-1){
            i++;
            j=0;
        }
        if(solve(bs,i,j,n)){
            return true;
        }else {
            return false;
        }
    }else if(bs[i][j]==0){
        for(int t=1;t<=9;t++){
            if(row(bs,i,t,n) && col(bs,j,t,n) && matrix(bs, i, j, t)){
                bs[i][j]=t;


                if(j<n-1){
                    if(solve(bs, i, j+1, n)){
                        return true;
                    }else {
                        bs[i][j]='.';
                    }
                }else if(j==n-1 && i<n-1){
                    if(solve(bs, i+1,j , n)){
                        return true;
                    }else {
                        bs[i][j]='.';
                    }
                }else if(j==n-1 && i==n-1){
                    return true;
                }
               
            }else {
                t++;
            }
        }

        return false;
    }
}

void sudokusolver(vector<vector<int>> &s){
    int n =s[0].size();
    solve(s,0,0,n);
}

int main(){
    int n;
    cin>>n;
    vector<vector<int>> s;
    for(int i=0;i<n;i++){
        vector<int> m;
        for(int j=0;j<n;j++){
            int temp;
            cin>>temp;
            m.push_back(temp);
        }
        s.push_back(m);
    }
    sudokusolver(s);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<s[i][j]<<" ";
        }
        cout<<endl;
    }
    
    return 0;
}