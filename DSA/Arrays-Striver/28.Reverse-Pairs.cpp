#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// (i) Brute force-----(Using two loops)

// T.C -> O(N^2)
// S.C -> O(1)














// (ii) Optimal Soln-------(USING MERGE SORT)

void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // temporary array
    int left = low;      // starting index of left half of arr
    int right = mid + 1;   // starting index of right half of arr

    //storing elements in the temporary array in a sorted manner//

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    // if elements on the left half are still left //

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    //  if elements on the right half are still left //
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // transfering all elements from temporary to arr //
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

// extra functioon added in merge sort to count pairs..while time of merging
int countPairs(vector<int> &arr, int low, int mid, int high){
    int cnt=0;
    int right = mid+1;

    //O(n1 + n2)----here every element of left & right halves is visited once only---same as that of two pointers
    for(int i=low;i<=mid;i++){ //O(n1)
        
        //O(n2)
        while(right<=high && arr[i]>2*arr[right]) right++;
        cnt += right - (mid+1);

    }

    return cnt;
}

int mergeSort(vector<int> &arr, int low, int high) {
    int cnt=0;
    if (low >= high) return 0;
    int mid = (low + high) / 2 ;
    cnt += mergeSort(arr, low, mid);  // left half
    cnt += mergeSort(arr, mid + 1, high); // right half

    // O(n)---array length
    cnt += countPairs(arr, low, mid, high);// counting pairs while merging
    // O(n)---array length
    merge(arr, low, mid, high);  // merging sorted halves

    return cnt;
}

int team(vector <int> & skill, int n)
{
    // Write your code here.
    return mergeSort(skill, 0, n-1);
}

// T.C -> O(LogN)*O(N + N)---same as that of merge sort just we are iterating twice while merging
//...........................once for the merge sort and another for 'countPairs' function
// S.C -> O(N)

int main(){
    return 0;
}