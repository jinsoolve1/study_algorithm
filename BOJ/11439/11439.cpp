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

const int mxn = 4e6+1;
bool sieve[mxn]; // true: not prime, false: prime
ll cntOfPrime[mxn];

void eratosthenes(ll N) {
    memset(sieve, 0, sizeof sieve);
    for(ll i=2; i*i<=N; i++) {
        if(sieve[i]) continue;
        for(ll j=i*i; j<=N; j+=i)
            sieve[j] = true;
    }
}
void calculatePrime(ll N, ll K) {
    memset(cntOfPrime, 0, sizeof cntOfPrime);
    for(ll i=2; i<=N; i++) {
        if(sieve[i]) continue;
        for(ll j=i; j<=N; j*=i) { // j = i^1, i^2,i^3, ...
            cntOfPrime[i] += (N/j) - (K/j) - ((N-K)/j);
        }
    }
}
// a^b % mod
ll pow(ll a, ll b, ll mod) {
    ll ret = 1;
    a %= mod;
    while(b) {
        if(b&1) ret = ret*a % mod;
        a = a*a % mod;
        b >>= 1;
    }
    return ret;
}
ll solve(ll N, ll K, ll M) {
    eratosthenes(N);
    calculatePrime(N,K);
    ll ret = 1;
    for(ll i=2; i<=N; i++)
        ret = (ret * pow(i,cntOfPrime[i],M)) % M;
    return ret;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll N, K, M; cin >> N >> K >> M;
    cout << solve(N, K, M) << endl;

    return 0;
}