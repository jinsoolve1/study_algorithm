## [백준 29199 - 활쏘기 대결](https://www.acmicpc.net/problem/29199)

### 알고리즘
- 게임 이론

### 풀이
psum[i] := 1 ~ i 까지의 표적의 점수의 합  
sol(i) := 1 ~ i 표적만 고려할 때, 해당 플레이어가 얻을 수 있는 최고 점수  
위와 같이 정의했다고 하자.

sol(1) = max(0, psum[1]) 이라 할 수 있다.

sol(i) = max(sol(i-1), psum[i] - sol(i-1)) 이 된다.

i번 표적을 맞추지 않는다면, sol(i-1)과 같을 것이다.  
i번 표적을 맞춘다면, 상대방에게 sol(i-1) 점수를 주고 나머지 점수를 얻는다. 따라서 psum[i] - sol(i-1)의 점수가 sol(i)의 점수가 된다.

위와 같이 코드를 작성하면 O(n) 시간 안에 해결 가능하다.

### 후기
핵심 아이디어는 sol(i)의 경우 i번 표적을 맞춘다면 상대방은 sol(i-1)의 점수를 얻게 될 것이다. (최적의 선택을 하기 때문)  
그렇다면 sol(i)의 점수는 1~i의 합에서 상대방의 점수를 뺀 만큼이 될 것이다.


```c++
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

int n;
vector<ll> a, psum, dp;

ll sol(int i) {
    if(i == 1) return max(0LL, psum[i]);
    ll &ret = dp[i];
    if(ret != -1) return ret;
    return ret = max(sol(i-1), psum[i] - sol(i-1));
}

void solve() {
    int n; cin >> n;
    a.resize(n+1, 0); psum.resize(n+1, 0);
    For1(i,n) {
        cin >> a[i];
        psum[i] = psum[i-1] + a[i];
    }

    dp.resize(n+1, -1);
    cout << sol(n);
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