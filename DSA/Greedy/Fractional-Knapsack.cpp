#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// VERY IMP QUESTION--------------------------


//class implemented
struct Item{
    int value;
    int weight;
};

// So here firstly the ratio of value to the weight of every item is calculated and then it is stored in the vector along with its Item class and then vector is sorted on the basis of the of these ratio values and then a value is simply taken if its weight is lesser than W or else taken fractionally(rate*remaing_weight)
// idea is that using greedy take value with bigger ratio first and then use fraction for the remaining weight capacity
// Think like by cal. the ratio we get to know that in same amnt of weight how much the item contributes in the value (and simply we will take the higher ratio items first).

class Solution
{
    public:
    static bool comp(pair<double, Item> a, pair<double, Item> b){
        return a.first > b.first;
    }
    //Function to get the maximum total value in the knapsack.
    double fractionalKnapsack(int W, Item arr[], int n)
    {
        // Your code here
        vector<pair<double, Item>> v;
        for(int i=0;i<n;i++){
            double ratio = (1.0*arr[i].value)/arr[i].weight;         //Here multiplication with 1.0 is important as both num/denom are integer values
            pair<double,Item> p = make_pair(ratio, arr[i]);
            v.push_back(p);
        }
        
        sort(v.begin(), v.end(), comp);
        
        double Totvalue=0;
        for(int i=0;i<n;i++){
            if(v[i].second.weight>W){
                Totvalue+= W*v[i].first;
                W=0;
                break;
            }else {
                Totvalue+=v[i].second.value;
                W = W - v[i].second.weight;
            }
        }
        return Totvalue;
    }
        
};





int main(){
    return 0;
}