//http://codersbrunch.blogspot.com/2017/04/1020.html
#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include <climits>

using namespace std;
typedef long long ll;
const int s[] = { 6,2,5,5,4,5,6,3,7,5,6 };
int a[15], n, d;
ll num, po = 1, dp[2][16][106];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str; cin >> str;
    for(n=0; n<str.length(); n++) {
        a[n] = str[n] - '0';
        num = num * 10 + a[n];
        d += s[a[n]];
        po *= 10;
    }
    fill(&dp[0][0][0], &dp[1][15][106], po * 2);
    dp[0][n][0] = 0;
    long long p = 1;
    for (int i = n; i--; p *= 10) {
        for (int j = 0; j < 10; j++) {
            for (int k = s[j]; k < 106; k++) {
                dp[0][i][k] = min(dp[0][i][k], dp[0][i + 1][k - s[j]] + j*p);
                if (j>a[i]) dp[1][i][k] = min(dp[1][i][k], dp[0][i + 1][k - s[j]] + j*p);
            }
        }
        for (int j = s[a[i]]; j < 106; j++) dp[1][i][j] = min(dp[1][i][j], dp[1][i + 1][j - s[a[i]]] + a[i] * p);
    }
    cout << min(dp[0][0][d] + po, dp[1][0][d]) - num << '\n';
    return 0;
}