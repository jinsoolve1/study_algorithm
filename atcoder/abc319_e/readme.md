## [atcoder abc319 - E : Bus Stops](https://atcoder.jp/contests/abc319/tasks/abc319_e)

### 알고리즘
- 최소공배수
- dp

### 풀이
$x_i$를 i 버스 정류장에 도달한 시간이라 하자.  

$$
x_{i+1} = \lceil \frac{x_i}{P_i} \rceil \times P_i + T_I 
$$

위와 같은 공식에 의해 우리는 도착시간을 구할 수 있다. 하지만 O(NQ)는 시간초과가 된다.  

그러나, 생각해보면 $P_i$는 1 ~ 8 이고 결국 lcm(1,2,...,8) = 840 마다 걸리는 시간이 반복된다는 것을 알 수 있다.  

$$
(x + 840 \times n)\ mod\ P_i = x\ mod\ P_i
$$

그 이유는 버스정류장마다 버려지는 시간들은 mod $P_i$되고 모든 i들에 대해서 합치면 mod $lcm(P_1, .. P_N)$ 이 된다는 것을 알 수 있다.  
따라서 mod 840이 되고 총 걸리는 시간은 840마다 반복된다는 것을 알 수 있다.

이를 이용하면 각 쿼리를 O(1)마다 해결할 수 있다. 즉 시간복잡도는 O(840*N + Q)가 된다.

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

const int LCM = 840;
ll dp[LCM];

ll N, X, Y;
vector<ll> P, T;
int Q;

ll solve(ll q) {
    ll &ret = dp[q];
    if(ret != -1) return ret;
    ret = q + X;
    for(int i=1; i<N; i++) {
        ret = ((ret-1)/P[i]+1)*P[i] + T[i];
    }
    return ret += Y - q;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> X >> Y;
    P = vector<ll>(N);
    T = vector<ll>(N);
    for(int i=1; i<N; i++)
        cin >> P[i] >> T[i];

    memset(dp, -1, sizeof dp);
    cin >> Q;
    while(Q--) {
        ll q; cin >> q;
        cout << q + solve(q%LCM) << endl;
    }

    return 0;
}
```