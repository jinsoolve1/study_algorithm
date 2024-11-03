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

map<pll, int> dp;

int solve(ll l, ll r) {
    if(l == 0 && r == 0) return 0;
    if(dp.count({l,r})) return dp[{l,r}];

    int ret = 0;
    for(int i=1; i<=30; i++) {
        ll s = (1ll << i) - 1; // 2^i - 1
        ll e = (1ll << (i+1)) - 2; // 2^(i+1) - 2
        s = max(s,l), e = min(e,r);

        // 2^i - 1 만큼 점프하고 남은 길이
        ll ss = s - (1ll << i) + 1;
        ll ee = e - (1ll << i) + 1;

        if(s <= e) ret = max(ret, solve(ss, ee) + i);
    }

    return dp[{l,r}] = ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        ll x, y; cin >> x >> y;
        cout << solve(x,y) << endl;
    }

    return 0;
}