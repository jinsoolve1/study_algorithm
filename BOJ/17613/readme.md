## [백준 17613 - 점프](https://www.acmicpc.net/problem/17613)

### 알고리즘
- 다이나믹 프로그래밍

### 풀이
1. 2^k-1 <= N 을 만족하는 가장 큰 자연수 k에 대하여 J(N) = J(N-(2^k-1)) + k 가 성립한다.  
   2^k-1 만큼 이동하는 데 최소 점프가 k이기 때문이다.
2. 이를 반대로 생각해서 k를 고정시켜 보자.  
   2^i-1 <= x 를 만족하는 가장 큰 자연수 i가 k인 x는 [2^k-1, 2^(k+1)-2] 이다.  
   k=1, 2, .. 구간들로 나누면 총 logN 개의 구간으로 나눌 수 있다.  
   N <= 10^9이므로 최대 약 30이 된다.
3. dp 테이블에서 실제 사용하는 구간은 매우 희소하므로 map을 이용해 메모라이제이션을 해준다.

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

map<pll, int> dp;

int solve(ll l, ll r) {
    if(l == 0 && r == 0) return 0;
    if(dp.count({l,r})) return dp[{l,r}];

    int ret = 0;
    for(int i=1; i<=30; i++) {
        ll s = (1ll << i) - 1; // 2^i - 1
        ll e = (1ll << (i+1)) - 2; // 2^(i+1) - 2
        s = max(s,l), e = min(e,r);

        // 2^i - 1 만큼 점프하고 남은 길이
        ll ss = s - (1ll << i) + 1;
        ll ee = e - (1ll << i) + 1;

        if(s <= e) ret = max(ret, solve(ss, ee) + i);
    }

    return dp[{l,r}] = ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        ll x, y; cin >> x >> y;
        cout << solve(x,y) << endl;
    }

    return 0;
}
```

### 참고
https://justicehui.github.io/koi/2019/06/30/BOJ17613/