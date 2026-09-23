#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int sum5=0;
        int sum10=0;
        for(int i=0;i<bills.size();i++){
            if(bills[i]==5) sum5++;
            else if(bills[i]==10){
                if(sum5>=1){
                    sum10++;
                    sum5--;
                }else return false;
            }else{
                if(sum10>=1 && sum5>=1){
                    sum10--;
                    sum5--;
                }else if(sum5>=3){
                    sum5-=3;
                }else return false;
            }
        }
        return true;
    }
};
// T.C -> O(N)
// S.C -> O(1)

int main(){
    return 0;
}