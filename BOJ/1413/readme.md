## [백준 1413 - 박스 안의 열쇠](https://www.acmicpc.net/problem/1413)

### 알고리즘
- DP
- 수학(조합론)

### 풀이
박스가 노드, 열쇠가 엣지라고 할 때 그래프에는 한 개 이상의 사이클들이 그려진다.  
이때 폭탄 수가 최소 사이클 개수만큼 있어야 박스를 모두 열 수 있다.
1. solve(n,k) := (랜덤하게 열쇠가 들어있는) n개의 박스를 k개의 폭탄으로 모두 열 수 있는 경우의 수 이라 하자.
2. solve(n,k) = solve(n-1, k-1) + (n-1)*solve(n-1,k)이다.
   1. solve(n-1,k-1)  
      현재 박스를 마지막으로 사이클을 구성하는 경우의 수
   2. (n-1)*solve(n-1,k)  
      현재 박스를 n-1개의 박스 중 어떤 박스와 연결할 지를 정해서 그래프를 이을 때의 경우의 수
   3. n == 0이라면, 모든 박스를 열었다는 의미이므로 1을 반환한다.
   4. k == 0이라면, 모든 박스를 열기 전에 폭탄을 다 사용했다는 의미이므로 0을 반환한다.

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

int N, M;
ll dp[21][21];

ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(b, a%b);
}

ll solve(int n, int k) {
    if(n == 0) return 1;
    if(k == 0) return 0;
    ll &ret = dp[n][k];
    if(ret != -1) return ret;
    return ret = solve(n-1,k-1) + (n-1)*solve(n-1,k);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);
    cin >> N >> M;
    ll num = solve(N,M), deno = solve(N,N);
    ll div = gcd(num, deno);
    num /= div, deno /= div;
    cout << num << "/" << deno << endl;

    return 0;
}
```