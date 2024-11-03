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
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

// a^b % mod
ull pow(ull a, ull b, ull mod) {
    ull ret = 1;
    a %= mod;
    while(b) {
        if(b&1) ret = ret*a % mod;
        a = a*a % mod;
        b >>= 1;
    }
    return ret;
}
bool miller_rabin_test(ull n, ull a) {
    if(n%a == 0) return false;
    int cnt = -1;
    ull d = n-1;
    while(!(d&1))
        d >>= 1, cnt++;
    ull p = pow(a,d,n);
    if(p==1 || p==n-1) return true;
    while(cnt--) {
        p = p*p % n;
        if(p == n-1) return true;
    }
    return false;
}
bool isPrime(ull n) {
    for(ull p : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if(n == p) return true;
        if(n>40 && !miller_rabin_test(n,p)) return false;
    }
    if(n <= 40) return false;
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ull t; cin >> t;
    ull ans = 0;
    while(t--) {
        ull n; cin >> n;
        ans += isPrime(2*n+1);
    }
    cout << ans << endl;

    return 0;
}