#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// EVERYTHING IS SAME AS Q.17.........




// (i) Brute force-----
// Using three loops
// T.C -> O(N^3)
// S.C -> O(1)



// (ii) Better soln-----
// Using two loops
// T.C -> O(N^2)
// S.C -> O(1)



// (iii) Optimal Soln---------
int subarraysWithSumK(vector < int > a, int b) {
    // Write your code here
    int n = a.size();
    map<int,int> mp;
    mp[0]=1;
    int prefXor=0;
    int cnt=0;

    for(int i=0;i<n;i++){
        prefXor = prefXor^a[i];
        int remainXor = prefXor^b;
        cnt+=mp[remainXor];
        mp[prefXor]++;
    }

    return cnt;
}
// T.C -> O(N*LogN){if ordered map} OR O(N){if uordered_map but O(N*N) in its worst case }
// S.C -> O(N)


int main(){
    return 0;
}