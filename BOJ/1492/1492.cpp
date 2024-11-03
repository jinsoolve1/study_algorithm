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

const ll mod = 1e9+7;
ll N, K;
ll dp_sum[51], f[52];

ll pow(ll a, ll b, ll c) {
    ll res = 1;
    while(b) {
        if(b%2) res = (res * a) % c;
        a = (a * a) % c;
        b >>= 1;
    }
    return res;
}
void set_factorial() {
    f[0] = 1;
    for(ll i=1; i<=51; i++) f[i] = (i*f[i-1]) % mod;
}
ll C(ll n, ll k) {
    if(k == 0 || k == n) return 1;
    return f[n] * pow(f[k]*f[n-k]%mod, mod-2, mod) % mod;
}
ll sum(ll n, ll k) {
    if(k == 0) return n;
    ll &ret = dp_sum[k];
    if(ret != -1) return ret;
    ret = pow(n+1,k+1,mod) - 1;
    for(int i=0; i<k; i++)
        ret = (ret - C(k+1,i) * sum(n,i)) % mod;
    ret = (ret + mod) % mod;
    ret = (ret * pow(C(k+1,k),mod-2,mod)) % mod;
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp_sum, -1, sizeof dp_sum);
    set_factorial();

    cin >> N >> K;
    cout << sum(N,K) << '\n';

    return 0;
}
