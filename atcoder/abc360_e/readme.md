## [atcoder 360-E : Random Swaps of Balls](https://atcoder.jp/contests/abc360/tasks/abc360_e)

### 알고리즘

- 수학

### 풀이

초기에 검정색 공은 첫번째 위치에 있다.

$f^k(i)$를 k번의 operation 후, 검정색 공이 i 위치에 위치할 확률이라고 하자.

operation을 1~2번 해보면, f(2\~n)은 같다는 것을 알 수 있다.\
여기서 우리는 $f^k(1)$ 을 구하고 나면 $f(2 \sim n)$은 $1-f^k(1)$을 n-1로 나눈 값들이 될 것이다.  
따라서 우리는 $f^k(1)$를 구하기만 하면 $E[x]$ 를 구할 수 있을 것이다.  

$f^k(1)$를 구해보자.  

$$
f^k(1) = pf^{k-1}(1) + q(f^{k-1}(2) + f^{k-1}(3) + ... + f^{k-1}(n))
$$

이때, $p = 1 - (n-1)\frac{2}{n^2}$이고 $q = \frac{2}{n^2}$가 된다.  

$f^{k-1}(2) + f^{k-1}(3) + ... + f^{k-1}(n) = 1 - f^{k-1}(1)$와 같다.  
따라서 이를 정리하면 아래와 같다.

$$
f^k(1) = pf^{k-1}(1) + q(1 - f^{k-1}(1)) \\
= (p-q)f^{k-1}(1) + q \\
= (1-\frac{2}{n})f^{k-1}(1) + \frac{2}{n^2} \\
= af^{k-1}(1) + b 
$$

간단히 하기 위해 $f^1(1) = x_1 = x$, $f^2(1) = x_2 = ax + b$ 꼴로 표현해보자.  

$f^{1}(1) = ax + b$  

$f^2(1) = a^2x + b(1+a)$

...

$f^k(1) = a^kx + b(1+a+a^2+...+a^{k-1})$

따라서 $f^k(1) = a^kx + b\frac{a^k-1}{a-1}$  

$a^k$ 와 $b$를 각각 구해서 $f^k(1)$을 구할 수 있고, 이를 통해 $f^k(2 \sim n)$ 들도 구할 수 있다.  
그 후에 $E[x]$를 구해주면 된다.  


```cpp
#include <bits/stdc++.h>

#define endl "\n"
#define all(v) (v).begin(), (v).end()
#define For(i, n) for(int i=0; i<n; ++i)
#define For1(i, n) for(int i=1; i<=n; ++i)
#define For2(i, a, b) for(int i=(a); i<=(b); ++i)
#define x first
#define y second
#define Get(i, v) get<i>(v)

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;
using tl3 = tuple<ll, ll, ll>;

const int INF = numeric_limits<int>::max();
const ll LNF = numeric_limits<ll>::max();

const ll MOD = 998244353;

// a^b mod c
ll Pow(ll a, ll b, ll c = MOD) {
    a %= c, b %= c;
    ll res = 1;
    while(b) {
        if(b%2) res = (res * a) % c;
        a = (a * a) % c;
        b >>= 1;
    }
    return res;
}

ll Mul(ll a, ll b, ll c = MOD) {
    a %= c, b %= c;
    return (a*b)%c;
}
ll Add(ll a, ll b, ll c = MOD) {
    a %= c, b %= c;
    return (a+b) % c;
}
ll Sub(ll a, ll b, ll c = MOD) {
    a %= c, b %= c;
    ll res = a - b;
    if(res < 0) res += c;
    return res;
}
ll Div(ll a, ll b, ll c = MOD) {
    a %= c; b %= c;
    return Mul(a, Pow(b,c-2));
}

void solve() {
    ll n, k; cin >> n >> k;
    ll a = Div(n-2, n);
    ll b = Div(2, Mul(n,n));
    ll a_k = Pow(a,k);

    ll x1 = 1;
    ll x1_k = Add(Mul(a_k,x1), Mul(b, Div(a_k-1, a-1)));
    ll x2_k = Div(Sub(1, x1_k), n-1);

    ll ans = Add(x1_k, Mul(x2_k, Sub(Div(Mul(n,n+1),2), 1)));
    cout << ans;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc = 1;
//    cin >> tc;
    while(tc--) {
        solve();
//        cout << solve() << endl;
    }


    return 0;
}
```
