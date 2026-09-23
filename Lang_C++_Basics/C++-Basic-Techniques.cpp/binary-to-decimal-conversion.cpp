#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//--------- if input is 'int'

int binaryToDecimal(int n)
{
    int dec_num = 0;
    int power = 0;
    while (n > 0)
    {
        if (n % 10 == 1)
        { // extracting the last digit
            dec_num += (1 << power);
        }
        power++;
        n = n / 10;
    }
    return dec_num;
}
// T.C -> O(k)  k--no of bits
// S.C -> O(1)





//--------- if input is 'string'
int binary_to_decimal(string str)
{
    int ans = 0;
    int n = str.size();
    for (int i = 0; i < n; i++)
        // Calculating 2^i * s[i]
        ans += (1 << (n - i - 1)) * (str[i] - '0');
    return ans;
}

// T.C -> O(k)
// S.C-> O(1)

int main()
{
    return 0;
}