## [atcoder abc218_f - Blocked Roads](https://atcoder.jp/contests/abc218/tasks/abc218_f)

### 알고리즘
- BFS
- 그래프 탐색

### 풀이
1. 최단거리를 찾는다. 이때, 최단 거리에 가기까지의 path를 기록한다.
2. 최단거리는 최대 N-1개의 edge로 이루어져 있다. 최단거리로 갈 때 사용하지 않는 edge들의 정답은 이 최단거리가 된다. -> O(N+M)
3. 최단거리로 사용된 edge들에 대한 정답은 최단거리로 계산한다. -> O(N*(N+M))이 된다.
4. 따라서 최종시칸 복잡도는 O(N(N+M))이 된다. 대충 400^3 = 약 6e7 정도이다. 따라서 시간 안에 솔브를 받을 수 있다.

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
vector<vector<int>> G;
vector<pii> E, path;
vector<int> dist;

int bfs(int src=1, int sink=N, int notToUse=-1) {
    queue<int> q;
    dist = vector<int>(N+1, -1); // dist[u] := src -> u dist
    dist[src] = 0;
    q.emplace(src);

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v=1; v<=N; v++) {
            if(G[u][v] == -1 || dist[v] != -1) continue;
            if(G[u][v] == notToUse) continue;
            dist[v] = dist[u] + 1;
            path[v] = {u,G[u][v]};
            q.emplace(v);
        }
    }
    return dist[sink];
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    G = vector<vector<int>>(N+1, vector<int>(N+1, -1));
    E = vector<pii>(M+1);
    for(int i=1; i<=M; i++) {
        int a, b; cin >> a >> b;
        G[a][b] = i;
        E[i] = {a,b};
    }

    path = vector<pii>(N+1); // path[v] = (u, e) := u -(e)-> v
    dist = vector<int>(N+1, -1); // dist[u] := src -> u dist
    if(bfs() == -1) {
        for(int i=1; i<=M; i++) cout << "-1\n";
        return 0;
    }

    vector<int> shortest_path;
    for(int u=N; u!=1; u=path[u].first) {
        shortest_path.emplace_back(path[u].second);
    }

    vector<int> ans(M+1, dist[N]);
    for(int e : shortest_path) {
        ans[e] = bfs(1,N,e);
    }

    for(int i=1; i<=M; i++) cout << ans[i] << endl;

    return 0;
}
```