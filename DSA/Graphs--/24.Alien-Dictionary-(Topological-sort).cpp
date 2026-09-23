#include<iostream>
#include<bits/stdc++.h>
using namespace std;
                                    //APPROACH-->Given an array of strings in sorted order we have to return one of the valud sequence of alphabets of the Alien's dictionary.
class Solution{                     //we will treat alphabets as 0,1,2... and will compare two strings at a time and will find out why the first one comes first and the will create an indegree array of these nodes cum alphabets and adjancy list at the same time then will follow the procedure of the topological sort.
    public:
    string findOrder(string dict[], int N, int K) {      //array of strings, arrays length(N), and K no. of starting alphabets of standard dictionary
        //code here
        int indegree[K]= {0};          //indegree array of for all alphabets given is created    
        vector<int> adj[K];            //adjancy list of the alphabets
        char ch = 'a';                //for making alphabet to an integer
        for(int i=0;i<N-1;i++){
            auto it= dict[i].begin();   //ietrator for the current first string
            auto it1= dict[i+1].begin();  //iterator for the current second string
            while(it!=dict[i].end() && it1!=dict[i+1].end()){       //while loop untill one the current two strings becomes empty
                if((*it)!=*(it1)){              //whenever the two elements of the strings are not equal we get the reason why first one comes earlier than the second in sorted order.
                    indegree[(*it1) -ch]++;     //when a alphabet comes first than the other we will treat as them nodes of the graph and will fill the indegree array
                    adj[*(it)-ch].push_back(*(it1)-ch);   //simultaneously adjancy list is also stored for the nodes as converting given alphabets to integers from 0
                    break;       //as we one unequality we get why first one string comes first and then we break from the while loop
                }
                it++;
                it1++;
            }
        }
                                           //now we have indegree array, adjancy list of the graph simply we have to use the topological sort
        queue<int> q;
        for(int i=0;i<K;i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }
        
        vector<char> v = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        string ans;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            string x = {v[node]};  //whenever we pop an no. from the queue its corresponding alphabet in the vector is stored in the string
            ans.append(x);

            //second way-- not using alphabets vector
            /*
            string ans = "";
            ans += char(node + 'a')
            
            */
            
            for(auto it: adj[node]){
                
                indegree[it]--;
                if(indegree[it]==0){
                    q.push(it);
                }
            }
            
        }
        
        return ans;               //toptological order(aliens dictionary sequence of alphabets) is returned.
    }
};

//---------IMP-->  Test cases when the gicen dictionary order is wrong
        //      (1)when "abcd" comes before "abc"..we cannot tell why first one comes first
        //      (2)when the cyclic dependency is given--abc bat acd-->not possible for the a to come before and after of the b