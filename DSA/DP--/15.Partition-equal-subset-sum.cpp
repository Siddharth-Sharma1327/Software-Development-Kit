#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//Space Otimised solution---------
bool canPartition(vector<int> &arr, int n)
{
	// Write your code here.
    int k1=0;
    for(int i=0;i<n;i++){
        k1+=arr[i];
    }
    if(k1%2!=0) return false;
    else{
        int k = k1/2;
         vector<bool> prev(k+1, 0), curr(k+1, 0);
        prev[0]= curr[0] = true;
        if(arr[0 < k+1]) prev[arr[0]] = true;

        for(int ind=1;ind<n;ind++){
            for(int target=1;target<=k;target++){
                bool notTake = prev[target];
                bool take = false;
                if(target>=arr[ind]) take=prev[target-arr[ind]];

                curr[target] = take | notTake;

            }
            prev=curr;
        }

        return prev[k]; 
    }
}
int main(){
     return 0;
}

// if two exaclty subsets with equal sum for given arr then if we can find one subset with sum = totSum / 2 then sum of remaining elements will be = totSum / 2 only 