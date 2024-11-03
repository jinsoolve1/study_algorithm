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

const int mxn = 3e6+1;
vector<ll> dp(mxn,0), fibo(34);

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fibo[0]=0, fibo[1]=1;
    for(int i=2; i<34; i++) fibo[i] = fibo[i-1] + fibo[i-2];

    bool used[34];
    for(int i=1; i<mxn; i++) {
        memset(used, 0, sizeof used);
        for(int j=1; i>=fibo[j]; j++) used[dp[i-fibo[j]]] = true;
        while(used[dp[i]]) dp[i]++;
    }

    int n, p, r=0; cin >> n;
    while(n--) cin >> p, r ^= dp[p];
    cout << (r ? "koosaga" : "cubelover") << endl;

    return 0;
}