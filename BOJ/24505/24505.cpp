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

const int mxn = 1e5+1;
const int mod = 1e9+7;

int N;
ll ans = 0;
ll fenwick[12][mxn];

void update(int cnt, int idx, int value) {
    while(idx < mxn) {
        fenwick[cnt][idx] = (fenwick[cnt][idx] + value) % mod;
        idx += (idx & -idx);
    }
}
ll sum(int cnt, int idx) {
    ll ret = 0;
    while(idx) {
        ret = (ret + fenwick[cnt][idx]) % mod;
        idx -= (idx & -idx);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(fenwick, 0, sizeof fenwick);

    cin >> N;
    while(N--) {
        int x; cin >> x;
        update(1,x,1);
        for(int i=2; i<12; i++) update(i, x, sum(i-1,x-1));
    }
    cout << sum(11, 1e5) << endl;

    return 0;
}