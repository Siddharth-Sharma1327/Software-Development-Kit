#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//(i) Brute force---------

vector<vector<int>> mergeOverlappingIntervals(vector<vector<int>> &arr){
	// Write your code here.
	int n = arr.size();
	vector<vector<int>> ans;

	sort(arr.begin(), arr.end());

	for(int i=0;i<n;i++){
		int start = arr[i][0];
		int end = arr[i][1];


		//if the current interval is already merged then no need to check for it
		if(!ans.empty() && end<=ans.back()[1]){
			continue;
		}

		//finding all the intervals which can be merged with the current one
		for(int j=i+1;j<n;j++){
			if(arr[j][0] <= end){
				end = max(end, arr[j][1]);
			}else{
				//the moment we got interval whose start > end of current then no need to check further as array is sorted so those will also be greater only
				break;
			}
		}
		ans.push_back({start, end});
	}

	return ans;
	
}
// T.C -> O(NLog(N)) + 2*O(N){here not n^2 as every element is visited twice only}
// S.C -> O(N)---{ans array}



//(ii) OPtimsied Soln---------
vector<vector<int>> mergeOverlappingIntervals(vector<vector<int>> &arr){
	// Write your code here.
	int n = arr.size();
	vector<vector<int>> ans;

	sort(arr.begin(), arr.end());

	for(int i=0;i<n;i++){
		
        //if ans array is empty OR current one's end is greater than the end of last interval stored in ans array-> then new interval is pushed into the ans array
		if(ans.empty() || arr[i][0] > ans.back()[1]){
			ans.push_back(arr[i]);
		}else{
            //this is condition where the current one's end <= the end of last interval stored in ans array..so include it
			ans.back()[1] = max(ans.back()[1], arr[i][1]);
		}

	}

	return ans;
	
}
// T.C -> O(NLog(N)) + O(N){here every element is visited only once}
// S.C -> O(N)---{ans array}
int main(){
    return 0;
}