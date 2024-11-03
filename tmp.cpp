#include <bits/stdc++.h>

#define endl "\n"
#define all(v) (v).begin(), (v).end()
#define For(i, a, b) for(ll i=(a); i<(b); i++)
#define FOR(i, a, b) for(ll i=(a); i<=(b); i++)
#define Bor(i, a, b) for(ll i=(a); i>(b); i--)
#define BOR(i, a, b) for(ll i=(a); i>=(b); i--)
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

template<class T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }

template<class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

const int INF = 987654321;
const int INF0 = numeric_limits<int>::max();
const ll LNF = 987654321987654321;
const ll LNF0 = numeric_limits<ll>::max();

void solve() {

}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int TC = 1;
//    cin >> TC;
    FOR(tc, 1, TC) {
//        cout << "Case #" << tc << ": ";
        solve();
    }

    return 0;
}
