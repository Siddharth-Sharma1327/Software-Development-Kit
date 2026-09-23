#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct Item{
    int value;
    int weight;
};

// Approach - 1 (Using Priority-Queue(MAx-Heap))
#define pp pair<double, pair<int,int>>

class Solution
{
    public:
    //Function to get the maximum total value in the knapsack.
    double fractionalKnapsack(int W, Item arr[], int n)
    {
        // Your code here
        double ans=0;
        double Wx = (double)W;
        priority_queue<pp> pq;
        for(int i=0;i<n;i++){
            pq.push({((double)arr[i].value/arr[i].weight), {arr[i].value, arr[i].weight}});
        }
        while(Wx && !pq.empty()){
            double rate = pq.top().first;
            int curV = pq.top().second.first;
            int curW = pq.top().second.second;
            pq.pop();
            
            if(Wx>=(double)curW){
                ans += (double)curV;
                Wx -= (double)curW;
            }else{
                ans += (double)(rate*Wx);
                Wx -= (double)(Wx);
            }
        }
        return ans;
    }
        
};

// T.C -> O(N*LogN) + O(N)
// S.C -> O(N)







// Approach -  2 (using sorting the guven array- no extra space) 
class Solution {
   public:
      bool static comp(Item a, Item b) {
         double r1 = (double) a.value / (double) a.weight;
         double r2 = (double) b.value / (double) b.weight;
         return r1 > r2;
      }
   // function to return fractionalweights
   double fractionalKnapsack(int W, Item arr[], int n) {

      sort(arr, arr + n, comp);

      int curWeight = 0;
      double finalvalue = 0.0;

      for (int i = 0; i < n; i++) {

         if (curWeight + arr[i].weight <= W) {
            curWeight += arr[i].weight;
            finalvalue += arr[i].value;
         } else {
            int remain = W - curWeight;
            finalvalue += (arr[i].value / (double) arr[i].weight) * (double) remain;
            break;
         }
      }

      return finalvalue;

   }
};
// T.C -> O(N*LogN) + O(N)
// S.C -> O(1)
int main(){
    return 0;
}