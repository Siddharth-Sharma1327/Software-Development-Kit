#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//Q no. of pairs {i, j} such that j>i && arr[i]>arr[j]


// (i) Brute force-----
// Using two loops i=0->n  and j=i->n
// T.C -> O(N^2)
// S.C -> O(1)















// (ii) Optimal Soln----  (USING MERGE SORT ALGO---)

int merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // temporary array
    int left = low;      // starting index of left half of arr
    int right = mid + 1;   // starting index of right half of arr
    int cnt=0;
    //storing elements in the temporary array in a sorted manner//

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        // if arr[left] > arr[right]
        else {
            cnt+= (mid-left+1);
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

    return cnt;
}

int mergeSort(vector<int> &arr, int low, int high) {
    
    if (low >= high) return 0;
    int mid = (low + high) / 2 ;
    int cntLeft = mergeSort(arr, low, mid);  // left half
    int cntRight = mergeSort(arr, mid + 1, high); // right half
    int cntMegre = merge(arr, low, mid, high);  // merging sorted halves

    return (cntLeft + cntRight + cntMegre);
}


int numberOfInversions(vector<int>&a, int n) {
    // Write your code here.
    return mergeSort(a, 0, n-1);
}

// I ended up by sorting the array so if don't want to distort the original array then use its copy....

// T.C -> O(NLogN)
// S.C -> O(N)



int main(){
    return 0;
}