## [백준 26113 - Two Choreographies](https://www.acmicpc.net/problem/26113)

### 알고리즘
- 그래프 탐색
- 트리
- 최소 공통 조상
- 비둘기집 원리

### 풀이
1. 2n-3개의 edge 중 n-1개 만을 이용하여 트리를 만든다.
2. 사용하지 않은 n-2개의 edge를 탐색하면서 해당 edge의 노드를 u, v라 할 때, u->lca->v의 길이를 구해서 저장한다.
3. 같은 길이이면서 2개 이상의 쌍의 u,v가 있다면 2개의 u->lca->v의 path를 출력한다.

### 증명
트리에 사용되지 않는 n-2개의 edge 중 하나의 edge를 e라고 하자.  
이때 e의 각 끝 정점을 u, v라 하자.  
u와 v는 각각 트리의 한 정점이므로 u -> v 로의 이동경로는 무조건 존재한다.  
따라서 u - ... -> lca - ... -> v 를 가고 v -> u로 가는 사용되지 않는 정점을 생각하면 사이클이 완성된다.  
이러한 사이클의 길이가 같은 것이 2개 이상 발견되면 해당 사이클들이 정답이 된다.

### 후기
n개의 노드라면 총 nC2개의 edge가 있을 수 있다. 하지만 여기서는 2n-3개의 edge만 주어진다.  
따라서, 여러개의 트리가 있을 수 있다. 그렇기 때문에 모든 노드 별로 루트를 시도해봐야 한다.  
이 부분을 간과해서 많은 시간을 낭비했다.

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

class Tree {
public:
    int N, LOG_MXN; // node: 1 ~ N
    vector<vector<int>> adj, parent;
    vector<int> depth;

    Tree() {}
    Tree(int _N) : N(_N), adj(N+1), depth(N+1, -1) {
        LOG_MXN = ceil(log(N)) + 1;
        parent = vector<vector<int>>(N+1, vector<int>(LOG_MXN+1));
    }
    void add_edge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    void set_tree(int root, int lv=1) {
        queue<int> q;
        depth[root] = lv;
        parent[root][0] = root;
        q.emplace(root);
        while(!q.empty()) {
            int sz = q.size();
            lv++;
            while(sz--) {
                int u = q.front(); q.pop();
                for(int v : adj[u]) {
                    if(depth[v] != -1) continue;
                    depth[v] = lv;
                    parent[v][0] = u;
                    q.emplace(v);
                }
            }
        }
    }
    void link_ancestor() {
        for(int i=1; i<=LOG_MXN; i++) {
            for(int u=1; u<=N; u++) {
                parent[u][i] = parent[parent[u][i-1]][i-1];
            }
        }
    }
    int find_lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int d = depth[a] - depth[b];
        for (int i = 0; d; i++) {
            if (d & 1) a = parent[a][i];
            d >>= 1;
        }
        if (a == b) return a;
        for (int i = LOG_MXN; i >= 0; i--)
            if (parent[a][i] != parent[b][i]) a = parent[a][i], b = parent[b][i];
        return parent[a][0];
    }
    void print_route(int u, int v) {
        int lca = find_lca(u,v);
        while(u != lca) {
            cout << u << ' ';
            u = parent[u][0];
        }
        cout << lca << ' ';
        vector<int> path;
        while(v != lca) {
            path.emplace_back(v);
            v = parent[v][0];
        }
        reverse(all(path));
        for(int x : path) cout << x << ' ';
        cout << endl;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    Tree tree(n);
    vector<pii> edges;
    vector<vector<pii>> route(n+1);
    for(int i=0; i<2*n-3; i++) {
        int u, v; cin >> u >> v;
        edges.emplace_back(u,v);
        tree.add_edge(u,v);
    }
    for(int i=1; i<=n; i++) {
        if(tree.depth[i] != -1) continue;
        tree.set_tree(i);
    }
//    tree.set_tree(1);
    tree.link_ancestor();
    for(pii e : edges) {
        int u = e.first, v = e.second;
        int lca = tree.find_lca(u,v);
        int len = tree.depth[u] + tree.depth[v] - 2*tree.depth[lca] + 1;
        if(len >= 3) route[len].emplace_back(u,v);
    }
    for(int i=3; i<=n; i++) {
        if(route[i].size() < 2) continue;
        cout << i << endl;
        for(int j=0; j<2; j++) {
            pii e = route[i][j];
            tree.print_route(e.first, e.second);
        }
        return 0;
    }
    cout << -1;
    return 0;
}
```