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

const int mod = 1e3, mxn = 501;
int N;
int loc[mxn], spring[mxn];
bool carry[mxn], adj[mxn][mxn];;
int dp[mxn][mxn];

int solve(int org, int dst) {
    int &ret = dp[org][dst];
    if(ret != -1) return ret;
    ret = adj[org][N] && adj[N][dst];
    for(int u = max(org,dst)+1; u <= N; u++) {
        if(adj[org][u]) ret = (ret + solve(u,dst)) % mod;
        if(adj[u][dst] && carry[u]) ret = (ret + solve(org,u)) % mod;
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);
    memset(adj, 0, sizeof adj);
    cin >> N;
    for(int i=1; i<=N; i++) cin >> loc[i] >> spring[i] >> carry[i];
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            if(i == j) continue;
            if(abs(loc[i]-loc[j]) <= spring[i]) adj[i][j] = true;
        }
    }
    cout << solve(1,1) << endl;

    return 0;
}