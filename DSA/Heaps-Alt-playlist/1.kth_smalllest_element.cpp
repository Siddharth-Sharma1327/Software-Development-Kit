class Solution {
  public:
    int kthSmallest(vector<int> &arr, int k) {
        // code here
        int n = arr.size();
        priority_queue<int> pq;
        
        // 1) push first k elements into pq
        for(int i=0; i<k; i++){
            pq.push(arr[i]);
        }
        
        // 2) compare next n-k elements with pq.top() if lesser elments are there
        for(int i=k; i<n; i++){
            if(arr[i] < pq.top()){
                pq.pop();
                pq.push(arr[i]);
            }
        }
        
        // 3) ans = pq.top()
        int ans = pq.top();
        return ans;
    }
};


// Time Complexity: O((n-k)logk) + O(klogk) ~ O(nlogk)
// Space Complexity: O(k) for priority queue



// ii) Optimal Solution - Using pivot and quick select algorithm