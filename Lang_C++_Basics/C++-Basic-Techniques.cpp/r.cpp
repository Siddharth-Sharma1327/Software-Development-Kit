#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;  

struct Element {
    int type, weight, value;
};

bool cmp(Element a, Element b) {
    return a.weight < b.weight;
}

int main() {
    int n, w, t, x, y, z;
    cin >> n >> w;
    vector<Element> elements(n);
    for (int i = 0; i < n; i++) {
        cin >> t >> x >> y;
        elements[i] = {t, x, y};
    }

    cout << dp[n][w] << endl;
    return 0;
}

    sort(elements.begin(), elements.end(), cmp);
    int dp[n + 1][w + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (elements[i - 1].weight <= j) {
                dp[i][j] = max(elements[i - 1].value + dp[i - 1][j - elements[i - 1].weight], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][w];