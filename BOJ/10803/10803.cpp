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

#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int dp[10001][101];
int solve(int n, int m) {
    if(n%m == 0) return n/m;
    if(n == m) return 1;

    int &ret = dp[n][m];
    if(ret != -1) return ret;

    ret = n*m;
    if(n >= 3*m) return ret = min(ret, solve(n-m,m) + 1);
    for(int i=1; i<=n/2; i++) ret = min(ret, solve(n-i, m) + solve(i,m));
    for(int j=1; j<=m/2; j++) ret = min(ret, solve(n, m-j) + solve(n,j));
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);
    int n, m; cin >> n >> m;
    cout << solve(n,m) << '\n';

    return 0;
}