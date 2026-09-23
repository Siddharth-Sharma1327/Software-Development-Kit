#include<istream> 
#include<bits/stdc++.h>
using namespace std;



// (i) Brute Force---------
string read(int n, vector<int> book, int target)
{
    // Write your code here.
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(book[i]+book[j]==target) return "YES";
        }
    }
    return "NO";
}
// T.C -> O(N^2)
// S.C -> O(1)


// (ii) Better Soln-----------
//M-1
string read(int n, vector<int> book, int target)
{
    // Write your code here.
    map<int,int> mp;
    for(int i=0;i<n;i++){
        if(mp.find(target-book[i])!=mp.end()){
            return "YES";
        }
        mp[book[i]]=i;
    }
    return "NO";
}
// T.C -> O(NLogN)
// S.C -> O(N)

// M-2
string read(int n, vector<int> book, int target) {
  // Write your code here.
  sort(book.begin(), book.end());

  int i=0;
  int j=n-1;

  while(i<j){
      if(book[i]+book[j]<target){
          i++;
      }else if(book[i]+book[j]>target){
          j--;
      }else if(book[i]+book[j]==target) return "YES";
  }
  return "NO";
}

// T.C -> O(NLogN)
// S.C -> O(1)





int main(){
    return 0;
}