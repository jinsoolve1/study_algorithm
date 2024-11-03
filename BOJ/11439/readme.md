## [백준 11439 - 아헝 계수 5](https://www.acmicpc.net/problem/11439)

### 알고리즘
- 정수론
- 소수 판정 (에라토스테네스의 체)
- 분할 정복을 이용한 거듭제곱 (소인수분해)

### 풀이
nCk의 값을 2로 소인수분해 한다고 하면 2의 개수는 $\sum_{i=1}(\frac{N}{2^i} - \frac{K}{2^i} - \frac{N-K}{2^i})$가 된다.  
다음과 같이 n보다 작거나 같은 소수들에 대해서 소인수분해 한 결과를 구해서 이를 다 곱하면 nCk의 값을 구할 수 있다.  

소수는 에라토스테네스의 체를 이용하여 구한다.  
cntOfPrime[i] := 소수 i에 대하여 nCk를 소인수분해 했을 때 소수 i의 개수를 저장하고 있다.  
i = 1 ~ N 을 탐색하면서 $i^{cntOfPrime[i]}$ 값을 곱해주면 정답을 구할 수 있다.

```c++
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
```