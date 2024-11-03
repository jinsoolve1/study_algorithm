#include <bits/stdc++.h>

#define endl "\n"
#define all(v) (v).begin(), (v).end()
#define For(i, a, b) for(int i=(a); i<(b); i++)
#define FOR(i, a, b) for(int i=(a); i<=(b); i++)
#define Bor(i, a, b) for(int i=(a)-1; i>=(b); i--)
#define BOR(i, a, b) for(int i=(a); i>=(b); i--)
#define ft first
#define sd second

using namespace std;
using ll = long long;
using lll = __int128_t;
using ulll = __uint128_t;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;
using tl3 = tuple<ll, ll, ll>;

template<typename T> using ve = vector<T>;
template<typename T> using vve = vector<vector<T>>;

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

const int INF = 987654321;
const int INF0 = numeric_limits<int>::max();
const ll LNF = 987654321987654321;
const ll LNF0 = numeric_limits<ll>::max();

int n;
vve<int> g;
ve<pii> edges;
ve<int> p;
map<int, set<int>> dp;

int f(int i) {
    if(i == p[i]) return i;
    return p[i] = f(p[i]);
}
bool uni(int a, int b) {
    a=f(a), b=f(b);
    if(a == b) return false;
    p[b] = a;
    return true;
}

void solve() {
    cin >> n;
    g = vve<int>(n+1);
    p = ve<int>(n+1); iota(all(p),0);
    FOR(i,1,n-1) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        edges.emplace_back(u,v);
    }

    ll ans = 0;
    for(auto [u,v] : edges) {
        if(g[u].size() == 3 and g[v].size() == 3) uni(u,v);
    }
    FOR(u,1,n) {
        if(g[u].size() != 3) continue;
        for(auto v : g[u]) {
            if(g[v].size() == 2) dp[f(u)].insert(v);
        }
    }
    for(auto &[gn, s] : dp) {
        ll x = s.size();
        ans += x*(x-1)/2;
    }
    cout << ans << endl;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int TC=1;
//    cin >> TC;
    FOR(tc, 1, TC) {
//        cout << "Case #" << tc << ": ";
        solve();
    }


    return 0;
}