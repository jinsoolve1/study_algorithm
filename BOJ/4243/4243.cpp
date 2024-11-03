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

int N, a;
vector<ll> t, tsum;
ll dp[101][101][2];

// dir : true->right, false->left
ll solve(ll l, ll r, bool dir) {
    if(l == 1 && r == N) return 0;
    ll &ret = dp[l][r][dir];
    if(ret != -1) return ret;
    ret = numeric_limits<ll>::max();
    ll cnt = N-r + l-1;
    if(dir) {
        if(l>1) ret = min(ret, solve(l-1,r,false) + cnt * (tsum[r-1]-tsum[l-2]));
        if(r<N) ret = min(ret, solve(l,r+1,true) + cnt * t[r]);
    }
    else {
        if(l>1) ret = min(ret, solve(l-1,r,false) + cnt * t[l-1]);
        if(r<N) ret = min(ret, solve(l,r+1,true) + cnt * (tsum[r]-tsum[l-1]));
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        cin >> N >> a; t.resize(N); tsum.resize(N);
        tsum[0] = 0;
        for(int i=1; i<N; i++) {
            cin >> t[i];
            tsum[i] = t[i] + tsum[i-1];
        }
        memset(dp, -1, sizeof dp);
        cout << solve(a,a,0) << endl;
    }

    return 0;
}