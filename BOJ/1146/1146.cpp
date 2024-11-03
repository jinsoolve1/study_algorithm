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

const int mod = 1e6;
int N;
int dp[100][100][2];
int ans = 0;

int solve(int left, int right, bool inc) {
    if(left == 0 && right == 0) return 1;
    int &ret = dp[left][right][inc];
    if(ret != -1) return ret;
    ret = 0;
    if(inc) for(int i=1; i<=right; i++)
        ret = (ret + solve(left+i-1,right-i,!inc)) % mod;
    else for(int i=1; i<=left; i++)
        ret = (ret + solve(left-i,right+i-1,!inc)) % mod;
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);
    cin >> N;
    if(N == 1) {
        cout << "1\n";
        return 0;
    }
    for(int l=0, r=N-1; r>=0; l++, r--) {
        ans = (ans + solve(l,r,true)) % mod;
        ans = (ans + solve(l,r,false)) % mod;
    }
    cout << ans << '\n';

    return 0;
}