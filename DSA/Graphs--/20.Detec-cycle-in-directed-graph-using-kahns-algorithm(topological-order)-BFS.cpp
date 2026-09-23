#include<iostream>
#include<bits/stdc++.h>

using namespace std;
class {
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        

	    // code here
	    //creating indegree array for all thye nodes of the graph
	   int indegree[V] = {0};      //indegree array is created for measuring the no. of indegrees at each node
	   for(int i=0;i<V;i++){       //indegree of each node is calculated
	       for(auto it: adj[i]){
	           indegree[it]++;
	       }
	   }
	   
	   //pushing all the nodes with 0 indegree into the queue
	   queue<int> q;                    //queue is created
	   for(int i=0;i<V;i++){            // all the nodes with indegree value equal to the 0 are pushed into the queue..(as these nodes will come before the other nodes in the topological order)
	       if(indegree[i]==0){
	           q.push(i);
	       }
	   }
	   
	   int cnt=0;          //answer vector
	   while(!q.empty()){
	       int node = q.front();       //fornt of the queue is stored
	       q.pop();
	       cnt++;       //after poping node form the queue it is pushed into the answer vector
	       
	       //node is in the topo sort
	       //remove all the edges wof this node with other nodes by traversing its adjacent noddes
	       
	       for(auto it: adj[node]){    //adjacent nodes of the currently poped node iterated for reducing their bond with the current node
	           indegree[it]--;         //reduced bond
	           
	           if(indegree[it]==0)  q.push(it);     //while reducing the bond whenever we get that node has 0 indegrees then it is pushed into the queue
	       }
	       
	   }
	   
	   //return topo;                        //after queue is empty answer vetor is returned
        if(cnt==V) return false;
        return true;

    }
};