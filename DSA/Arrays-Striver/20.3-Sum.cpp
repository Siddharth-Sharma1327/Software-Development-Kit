#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// (i) Brute Force-------------
#include<bits/stdc++.h>
vector<vector<int>> triplet(int n, vector<int> &arr)
{
    // Write your code here.
    set<vector<int>> st;

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            for(int k=j+1;k<n;k++){
                if(arr[i]+arr[j]+arr[k]==0){
                    vector<int> temp = {arr[i], arr[j], arr[k]};
                    sort(temp.begin(), temp.end());

                    //O(Log(no. of triplets)
                    st.insert(temp);
                }
            }
        }
    }

    vector<vector<int>> ans(st.begin(), st.end());
    return ans;

}
// T.C -> O(N^3)*O(Log(no. of triplets))
// S.C -> 2*O(no. of triplets)


// (ii) Better Soln-----------------
vector<vector<int>> triplet(int n, vector<int> &arr)
{
    // Write your code here.
    set<vector<int>> st;

    for(int i=0;i<n;i++){
        set<int> hashSet;
        for(int j=i+1;j<n;j++){
            int third = -(arr[i] + arr[j]);
            if(hashSet.find(third) != hashSet.end()){
                vector<int> temp =  {arr[i], arr[j], third};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
            hashSet.insert(arr[j]);
        }
    }

    vector<vector<int>> ans(st.begin(), st.end());
    return ans;

}

// T.C -> O(N^2)*(O(LogM) + O(Log(no. of triplets))).....M = hashSet size
// S.C -> O(N) + 2*O(no. of triplets)




// (iii) Optimal Soln----
vector<vector<int>> triplet(int n, vector<int> &arr)
{
    // Write your code here.
    vector<vector<int>> ans;

    //O(NLogN)
    sort(arr.begin(), arr.end());

    // O(N)
    for(int i=0;i<n;i++){

        //finding element not equal to previous one to consider only unique triplets
        if(i>0 && arr[i]==arr[i-1]) continue;

        //two pointers
        int j = i+1;
        int k = n-1; 

        //O(N)
        while(j<k){
            int sum = arr[i] + arr[j] + arr[k];

            if(sum<0){
                j++;
            }else if(sum>0){
                k--;
            }else{
                vector<int> temp = {arr[i], arr[j], arr[k]};
                //no need to sort as already in sorted order
                ans.push_back(temp);
                //changing both pointers because both these elements can't be used to form triplet as above they are used once..
                j++;
                k--;

                //finding new indices for j,k but elements not equal to previous ones
                //...to have only unique triplets
                while(j<k && arr[j]==arr[j-1]) j++;
                while(j<k && arr[k]==arr[k+1]) k--;

                // when j,k crosses eachother for current 'i' all triplets are checked and we do i++..
            }
        }
    }
    return ans;

}
// T.C -> O(NLogN) + O(N*N)
// S.C -> O(no. of triplets)



int main(){
    return 0;
}