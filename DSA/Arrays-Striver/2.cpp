#include<iostream>
#include <bits/stdc++.h> 

using namespace std;


// Q1
// Left rotate array by one place (using O(1) extra space)
vector<int> rotateArray(vector<int>& arr, int n) {
    // Write your code here.
    int temp=arr[0];
    for(int i=1;i<n;i++){
        arr[i-1]=arr[i];
    }
    arr[n-1]=temp;
    return arr;
}







// Q2
// Left rotate array by 'd' place (using O(1) extra space)
// (i) Brute force-
void leftRotate(vector<int> &arr, int d, int n){
    d=d%n;

    vector<int> temp;
    for(int i=0;i<d;i++){
        temp.push_back(arr[i]);
    }

    for(int i=d;i<n;i++){
        arr[i-d]=arr[i];
    }

    for(int i= n-d;i<n;i++){
        arr[i] = temp[i - (n-d)];
    }

}
vector<int> rotateArray(vector<int>arr, int k) {
    // Write your code here.
    leftRotate(arr, k, arr.size());
    return arr;

}
// T.C -> O(d) + O(n-d) + O(d) = O(d)
// S.C -> O(d)


// (i) OPtimised -
void leftRotate(vector<int> &arr, int d, int n){
    d=d%n;

    reverse(arr.begin(), arr.begin()+d);
    reverse(arr.begin()+d, arr.begin()+n);
    reverse(arr.begin(), arr.begin()+n);

    return;

}
vector<int> rotateArray(vector<int>arr, int k) {
    // Write your code here.
    leftRotate(arr, k, arr.size());
    return arr;

}


// T.C -> O(d) + O(n-d) + O(n) = O(2n)
// S.C -> O(1)







// Q3
// Move zeroes to end of array---------------

// (i) Brute force--
vector<int> moveZeros(int n, vector<int> a) {
    // Write your code here.
    vector<int> temp;
    for(int i=0;i<n;i++){
        if(a[i]!=0) temp.push_back(a[i]);
    }

    for(int i=0;i<temp.size();i++){
        a[i]=temp[i];
    }

    for(int i=temp.size();i<n;i++){
        a[i]=0;
    }
    return a;
}

// T.C -> O(2N)
// S.C -> O(N)


// (ii) Optimised soln:-

vector<int> moveZeros(int n, vector<int> a) {
    // Write your code here.
    int j=-1;
    for(int i=0;i<n;i++){
        if(a[i]==0){
            j=i;
            break;
        }
    }

    // no zeroes in array
    if(j==-1) return a;

    for(int i=j+1;i<n;i++){
        if(a[i]!=0){
            swap(a[i], a[j]);
            j++;
        }
    }

    return a;
}


// T.C -> O(N)
// S.C -> O(1)



// Q4
// Union of two sorted arrays-----
// (i) Brute force-----
#include<bits/stdc++.h>
vector < int > sortedArray(vector < int > a, vector < int > b) {
    // Write your code here
    vector<int> ans;
    int m = a.size();
    int n = b.size();

    set<int> st;
    for(int i=0;i<m;i++){
        st.insert(a[i]);
    }

    for(int i=0;i<n;i++){
        st.insert(b[i]);
    }

    for(auto it: st){
        ans.push_back(it);
    }

    return ans;
}
// T.C -> O(mlogm + nlogn) + O(n+m)
// S.C -> O(n+m) + O(n+m)  -> ans array & set




// (ii) OPtimised Soln-------
vector < int > sortedArray(vector < int > a, vector < int > b) {
    // Write your code here
    vector<int> ans;
    int m = a.size();
    int n = b.size();

    int i=0, j=0;

    while(i<m && j<n){
        if(a[i]<b[j]){
            if(ans.empty() || a[i]!=ans.back()){
                ans.push_back(a[i]);
                i++;
            }else i++;
        }else if(a[i]==b[j]){
            if(ans.empty() || a[i]!=ans.back()){
                ans.push_back(a[i]);
                i++;
                j++;   
            }else{
                i++;
                j++;
            }
        }else if(a[i]>b[j]){
            if(ans.empty() || b[j]!=ans.back()){
                ans.push_back(b[j]);
                j++;
            }else j++;
        }
    }

    while(i<m){
        if(ans.empty() || a[i]!=ans.back()){
                ans.push_back(a[i]);
                i++;
        }else i++;
    }

    while(j<n){
       if(ans.empty() || b[j]!=ans.back()){
                ans.push_back(b[j]);
                j++;
        }else j++; 
    }

    return ans;
}
// T.C -> O(n+m)
// S.C -> O(n+m) -> ans array




// Q5
// Intersection of two sorted arrays--------
// (i) Brute force-------
#include <bits/stdc++.h> 
vector<int> findArrayIntersection(vector<int> &arr1, int n, vector<int> &arr2, int m)
{
	// Write your code here.
	vector<int> ans;
	vector<int> vis(m, 0);

	for(int i=0;i<n;i++){

		for(int j=0;j<m;j++){
			if(arr1[i]==arr2[j] && !vis[j]){
				ans.push_back(arr1[i]);
				vis[j]=1;
				break;
			}

			if(arr2[j]>arr1[i]) break;
		}
	}
	return ans;
}
// T.C -> O(n^2)
// S.C -> O(n)

// (ii) Better Soln---------
#include <bits/stdc++.h> 
vector<int> findArrayIntersection(vector<int> &arr1, int n, vector<int> &arr2, int m)
{
	// Write your code here.
	vector<int> ans;
	unordered_map<int,int> mp;   //O(1) or O(n)-worst
    map<int,int> mp;             //O(logn)
	for(int i=0;i<n;i++) mp[arr1[i]]++;

	for(int i=0;i<m;i++){
		if(mp[arr2[i]]>=1){
			ans.push_back(arr2[i]);
			mp[arr2[i]]--;
		}
	}
	return ans;
}

// T.C -> O(n^2){unordered_map worst} or O(nlogn){map}
// S.C -> O(n)


// (iii) Optimised Soln--------
#include <bits/stdc++.h> 
vector<int> findArrayIntersection(vector<int> &arr1, int n, vector<int> &arr2, int m)
{
	// Write your code here.
	vector<int> ans;
	int i=0, j=0;
	while(i<n && j<m){
		if(arr1[i]<arr2[j]){
			i++;
		}else if(arr1[i]==arr2[j]){
			ans.push_back(arr1[i]);
			i++;
			j++;
		}else if( arr1[i]>arr2[j]){
			j++;
		}
	}
	return ans;
}
// T.C-> O(n)
// S.C -> O(1)




