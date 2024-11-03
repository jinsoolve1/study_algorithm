## [백준 26106 - Forbidden Turns](https://www.acmicpc.net/problem/26106)

### 알고리즘
- 다익스트라 
- map
- set

### 풀이
1. src -> dst 로의 다익스트라 알고리즘을 이용하여 최단 거리를 찾는다.
2. 이때 prv -> cur -> nxt 순으로 진행한다고 가정했을 때, forbidden turns 중에서 (prv, cur, nxt)가 있는지를 set을 이용해 확인한다.
3. dp를 저장할때 2차원 배열로 하면 메모리 용량 때문인지 컴파일에러가 나오므로 map을 이용하여 dp를 구현한다.

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

const int mxn = 3e4;
//int dp[mxn][mxn]; //dp[prv][cur] := src -> ... -> prv -> cur 왔을 때 거리
map<pii, int> dp;
vector<pii> g[mxn];
set<ti3> s;

int solve(int src, int dst) {
    priority_queue<ti3, vector<ti3>, greater<>> pq;
    dp[{src, src}] = 0;
    pq.emplace(0, src, src); // (dist, cur, prv)
    while(!pq.empty()) {
        int dist = get<0>(pq.top()), cur = get<1>(pq.top()), prv = get<2>(pq.top());
        pq.pop();
        if(cur == dst) return dist;
        if(dp[{prv, cur}] < dist) continue;
        for(pii e : g[cur]) {
            int nxt = e.first, cost = dist + e.second;
            if(s.count({prv,cur,nxt})) continue;
            if(dp.count({cur,nxt}) && dp[{cur, nxt}] <= cost) continue;
            dp[{cur, nxt}] = cost;
            pq.emplace(cost, nxt, cur);
        }
    }
    return -1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m, n, k; cin >> m >> n >> k;
    int src, dst; cin >> src >> dst;
    while(m--) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v,w);
    }
    while(k--) {
        int x, y, z; cin >> x >> y >> z;
        s.insert({x,y,z});
    }
    cout << solve(src, dst) << endl;

    return 0;
}
```