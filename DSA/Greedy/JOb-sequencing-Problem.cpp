#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Here Idea is that when we sort the array of Job data type accord to their profits..and then creating a deadline array for storing the jobs ids which job is performed and then intuition is that a job is done at the very last interval where no job is performed so that the job with lesser deadlines can be done at starter dealine values
// if value of current jobs deadline wala index is ==-1 then i will fill their the current jobs id o/w i will travel towards left in the deadline array to the first value ==-1 and then will plave there current jobs id
struct Job 
{ 
    int id;	 // Job Id 
    int dead; // Deadline of job 
    int profit; // Profit if job is over before or on deadline 
};

class Solution 
{
    public:
    static bool comp(Job a, Job b){
        return a.profit > b.profit;
    }
    //Function to find the maximum profit and the number of jobs done.
    vector<int> JobScheduling(Job arr[], int n) 
    { 
        // your code here
        int cnt=0, prof=0;
    
        vector<Job> v;
        for(int i=0;i<n;i++){
            v.push_back(arr[i]);
        }
        
        sort(v.begin(), v.end(), comp);
        
        vector<int> deadline(n+1, -1);
        
        for(int i=0;i<n;i++){
            if(deadline[v[i].dead]==-1) deadline[v[i].dead]=v[i].id, prof+=v[i].profit, cnt++;
            else{
                int j=v[i].dead-1;
                while(j>=1){
                    if(deadline[j]==-1){
                       deadline[j]=v[i].id, prof+=v[i].profit,cnt++;
                       break; 
                    } 
                    else j--;
                }
            }
        }
        vector<int> ans(2, 0);
        ans[0]=cnt, ans[1]=prof;
        return ans;
    } 
};


int main(){
    return 0;
}