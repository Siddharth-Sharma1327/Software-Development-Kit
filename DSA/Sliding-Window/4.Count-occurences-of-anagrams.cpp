#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Approach - 1
class Solution{
private: 
    bool f(vector<int> &v1, vector<int> &v2){
        for(int i=0;i<26;i++){
            if(v1[i]!=v2[i]) return false;
        }
        return true;
    }
public:
	int search(string pat, string txt) {
	    // code here
	    int ans=0;
	    int n = txt.length();
	    int k = pat.length();
	    
	    vector<int> v1(26, 0),v2(26, 0);
	    for(int i=0;i<k;i++) v1[pat[i]-'a']++;
	    
	    int i=0,j=0;
	    while(j<n){
	        v2[txt[j]-'a']++;
	        
	        if(j-i+1<k){
	            j++;
	        }else{
	            if(f(v1, v2)) ans++;
	            v2[txt[i]-'a']--;
	            i++;
	            j++;
	        }
	    }
	    return ans;
	}

};
// T.C-> O(N*26)
// S.C -> O(26)




// Approach - 2
class Solution{
public:
	int search(string pat, string txt) {
	    // code here
	    int ans=0;
	    int n = txt.length();
	    int k = pat.length();
	    
	    unordered_map<int, int> mp;
	    for(int i=0;i<k;i++) mp[pat[i]-'a']++;
	    int cnt = mp.size();
	    
	    int i=0,j=0;
	    while(j<n){
	        mp[txt[j]-'a']--;
	        if(mp[txt[j]-'a']==0) cnt--;
	        
	        if(j-i+1<k){
	            j++;
	        }else{
	            if(cnt==0) ans++;
	            mp[txt[i]-'a']++;
	            if(mp[txt[i]-'a']==1) cnt++;
	            i++;
	            j++;
	        }
	    }
	    return ans;
	}

};
// here the 'cnt' is the no. of distinct elments of 'pat' string. then window is moved and freq. of every elment is reduced and if it becomes 0..means an element of 'pat' string is reduced so cnt--..but
//  if the freq. increases from 0 to 1 ..means elment of 'pat' string has came again..
// in short here we reduce the freq of elment in start after that we increment the freq as we traverse and we reduce the freq. of first element of every window before moving to the next window
//----------check video----------------
// T.C-> O(N)
// S.C -> O(26)
int main(){
    return 0;
}