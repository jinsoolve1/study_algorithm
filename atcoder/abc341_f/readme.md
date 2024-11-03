## [atcoder abc341_f Breakdown](https://atcoder.jp/contests/abc341/tasks/abc341_f)

### 알고리즘
- knapsack 알고리즘 (DP)

### 풀이
u에서 v1, v2, .., vx 로 갈 수 있다고 가정하자.  
dp[v1]에는 `v1의 A에 1을 하나 추가하면 이 1이 사라지기 위한 최대 operation 수`가 저장되어 있다고 하자.  

그렇다면 dp[u]는 v1 ~ vx 까지 중에서 최대 W[u]만큼 담으면서 최대의 value(dp[v]의 합들)을 계산해야 한다.  
위 문제는 0-1 knapsack 문제임을 알 수 있다.

각 u마다 지식 수를 $M_u$개라 가장하면 각 u의 시간복잡도는 $O(M_u \times W_u)$이다. $W_u$는 최대 5000다.  
모든 u에 대해서 해야 하므로 $5000 \times (M_1 + M_2 + ... + M_N)$가 되고 모든 M의 합은 5000인데 양방향이므로 10,000이 된다.  
따라서 5e7 정도의 연산에 해결할 수 있다.

하자민 여기서 문제가 생기는데, dp[u]를 계산할 때 dp[v]들이 모두 계산되어 있어야 한다는 점이다.  
하지만 잘 생각해보면 u가 dp[v]를 필요로 할 때는 W[u] > W[v]인 v들에 대해서만이다. 따라서 우리는 W[u]가 작은 순서대로 dp[u]를 계산하면 된다.

### 코드
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

const int mxn = 5001;
int N, M;
vector<int> g[mxn];
vector<int> W(mxn), A(mxn);
ll bag[mxn][mxn];
ll dp[mxn];
vector<int> order;

bool cmp(int a, int b) {
    return W[a] < W[b];
}
ll knapsack(int u) {
    ll &ret = dp[u];
    for(int i=1; i<=g[u].size(); i++) {
        int v = g[u][i-1];
        for(int w=1; w<=W[u]; w++) {
            if(w <= W[v]) bag[i][w] = bag[i-1][w];
            else bag[i][w] = max(bag[i-1][w], dp[v] + bag[i-1][w-W[v]]);
        }
    }
    return ret = bag[g[u].size()][W[u]] + 1;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int u, v; cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for(int i=1; i<=N; i++) cin >> W[i];
    for(int i=1; i<=N; i++) cin >> A[i];

    for(int i=1; i<=N; i++) order.emplace_back(i);
    sort(all(order), cmp);
    for(int &u : order) {
        knapsack(u);
    }

    ll ans = 0;
    for(int i=1; i<=N; i++) {
        ans += A[i] * dp[i];
    }
    cout << ans << endl;

    return 0;
}
```