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
#include <set>
#include <unordered_set>
#include <climits>

#define endl "\n"
#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int N, M;
ll dp[21][21];

ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(b, a%b);
}

ll solve(int n, int k) {
    if(n == 0) return 1;
    if(k == 0) return 0;
    ll &ret = dp[n][k];
    if(ret != -1) return ret;
    return ret = solve(n-1,k-1) + (n-1)*solve(n-1,k);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);
    cin >> N >> M;
    ll num = solve(N,M), deno = solve(N,N);
    ll div = gcd(num, deno);
    num /= div, deno /= div;
    cout << num << "/" << deno << endl;

    return 0;
}