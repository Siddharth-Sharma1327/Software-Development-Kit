#include<iostream>
#include <bits/stdc++.h> 
using namespace std;

long long int maximumNonAdjacentSum(vector<int> &nums){
    // Write your code here.
    int n = nums.size();
    
    long long int prev = nums[0];
    long long int prev2 = 0;
    for(int i=1;i<n;i++){
        
        long long int take = nums[i];
        if(i>1) take+=prev2;
        
        long long int nontake = 0 + prev;
        long long int curri = max(take, nontake);
        prev2 = prev;
        prev=curri;
    }
    
    return prev;
}
long long int houseRobber(vector<int>& valueInHouse)
{
    // Write your code here.                            //here just two different arrays excluding 1st and last elements are created as they were adjacent
    int n = valueInHouse.size();                        //Note here there would be similar cases in both sets of arrays but we are interested in only max. value so this works otherwise we had to think
    vector<int> temp1, temp2;
    if(n==1) return valueInHouse[0];
    for(int i=0;i<n;i++){
        if(i!=0) temp1.push_back(valueInHouse[i]);
        if(i!=n-1) temp2.push_back(valueInHouse[i]);
    }
    
    return max(maximumNonAdjacentSum(temp1), maximumNonAdjacentSum(temp2));
}