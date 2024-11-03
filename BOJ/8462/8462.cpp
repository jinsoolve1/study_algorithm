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
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int sqrt_n;
struct Query {
    int idx, l, r;

    bool operator<(Query other) const {
        if(l/sqrt_n == other.l/sqrt_n) return r < other.r;
        return l < other.l;
    }
};

const int mxn = 1e6+1;
int n, t;
ll res;
vector<ll> a, ans;
vector<Query> qs;
int cnt[mxn];

void add(int idx) {
    ll s = a[idx], ks = cnt[s];
    res -= s*ks*ks;
    ks = ++cnt[s];
    res += s*ks*ks;
}
void remove(int idx) {
    ll s = a[idx], ks = cnt[s];
    res -= s*ks*ks;
    ks = --cnt[s];
    res += s*ks*ks;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(cnt, 0, sizeof cnt);

    cin >> n >> t;
    a.resize(n+1); sqrt_n = sqrt(n);
    for(int i=1; i<=n; i++) cin >> a[i];
    for(int i=0; i<t; i++) {
        int l, r; cin >> l >> r;
        qs.push_back({i,l,r});
    }
    sort(all(qs));
    ans.resize(t);
    int l = qs[0].l, r = qs[0].l;
    cnt[a[l]]++; res = a[l];
    for(Query q : qs) {
        while(q.l < l) add(--l);
        while(l < q.l) remove(l++);
        while(r < q.r) add(++r);
        while(q.r < r) remove(r--);
        ans[q.idx] = res;
    }
    for(ll x : ans)  cout << x << '\n';

    return 0;
}