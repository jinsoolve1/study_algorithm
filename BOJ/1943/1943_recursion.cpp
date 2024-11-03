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
#define f first
#define s second
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int N;
vector<pii> coin;
int dp[101][101010];
int solve(int idx, int amount) {
    if(idx == N) return amount == 0;
    int &ret = dp[idx][amount];
    if(ret != -1) return ret;
    ret = 0;
    for(int cnt=0; cnt<=coin[idx].s; cnt++) {
        ret = max(ret, solve(idx+1, amount - coin[idx].f*cnt));
        if(ret == 1) return ret;
    }
    return ret = 0;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int _=0; _<3; _++) {
        memset(dp, -1, sizeof dp);
        coin.resize(0);
        int total = 0;
        cin >> N;
        for(int i=0; i<N; i++) {
            int a,b; cin >> a >> b;
            total += a*b;
            coin.emplace_back(a,b);
        }
        if(total % 2 == 1) cout << 0 << '\n';
        else cout << solve(0,total/2) << '\n';
    }

    return 0;
}