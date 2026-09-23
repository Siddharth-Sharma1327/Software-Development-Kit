#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution {
private:
   
public:
    int wordLadderLength(string startWord, string targetWord, vector<string>& wordList) {
        // Code here
       
        queue<pair<string,int>> q;
        q.push({startWord,1});
        unordered_set<string> st(wordList.begin(), wordList.end());
        st.erase(startWord);
        
        while(!q.empty()){
            string word = q.front().first;
            int steps = q.front().second;
            q.pop();
            if(word==targetWord) return steps;
            for(int i=0;i<word.length();i++){
                char original = word[i];
                for(char ch= 'a';ch<='z'; ch++){
                    word[i]=ch;
                    if(st.find(word) != st.end()){
                        st.erase(word);
                        q.push({word, steps+1});
                    }
                }
                word[i]=original;
            }
        }
        
        
        return 0;
     
    }
};
//Space Complexity-->O(N) + O(N) (for queue and set)
//Time Complexity--> O(N*wordlength*26)




// MY APPROACH----visualising them as undirected graph with unit weights where every node having neigbour nodes which have only one letter difference...then finding shortest path of dest node from source node
class Solution {
public:

    bool check(int i, int j, vector<string> &newList){
        if(i==j) return false;
        
        int cnt=0;
        for(int s=0;s<newList[i].length();s++){
            if(newList[i][s]!=newList[j][s]) cnt++;
        }
        if(cnt==1) return true;
        else return false;
    }

    int wordLadderLength(string startWord, string targetWord, vector<string>& wordList) {
        // Code here
        int n = wordList.size();
        int src=n;
        int dest=-1;
        for(int i=0;i<n;i++){
            if(wordList[i]==startWord){
               src=i; 
            } 
            if(wordList[i]==targetWord) dest=i;
        }
        vector<string> newList=wordList;
        if(src==n){                            //if source node string is note there in wordList it is pushed
           newList.push_back(startWord);
           n+=1;
        } 
        vector<int> adj[n];         //adjacency list
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(check(i, j, newList)){       //if strings have difference of one letter make them adjacent nodes...undirected is done in u-v case and v-u case
                    adj[i].push_back(j);
                }
            }
        }
        
        vector<int> dist(n, 0);             // finding shortest path of dest string from source node
        queue<int> q;
        dist[src]=1;
        q.push(src);
        
        while(!q.empty()){                  //since undirected graph with "UNIT WEIGHTS" it is stored in sorted order i.e no node is pushed more than once in queue
            int node = q.front();
            q.pop();
            
            for(auto it: adj[node]){
                if(dist[it]==0 || dist[node]+1<dist[it]){
                    dist[it] = dist[node]+1;
                    q.push(it);
                }
            }
        }
        
        return dist[dest];
    }
};


// T.C -> O(N) + O(N*N*M) + O(N) + O(N)*M---> since at max M nodes will be connected to any node as connected nodes have only one letter difference and max length of each string is M
// S.C -> O(N) + O(N*M)(at max M neighbours of any node) + O(N) + O(N)