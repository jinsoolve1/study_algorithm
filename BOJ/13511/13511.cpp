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
#include <climits>

#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

const int mxn = 1e5+1, LOG_MXN=20;
int N, M;
ll depth[mxn], cost[mxn];
ll parent[mxn][LOG_MXN+1];
vector<pll> g[mxn];

void makeTree(int here, int level) {
    depth[here] = level;
    for(pii e : g[here]) {
        int there = e.first;
        if(depth[there] != -1) continue;
        parent[there][0] = here;
        cost[there] = cost[here] + e.second;
        makeTree(there, level+1);
    }
}
void linkAncestor() {
    for(int i=1; i<=LOG_MXN; i++) {
        for(int here=1; here<=N; here++) {
            parent[here][i] = parent[parent[here][i-1]][i-1];
        }
    }
}
int LCA(int a, int b) {
    if(depth[a] > depth[b]) swap(a,b);

    for(int i=LOG_MXN; i>=0; i--) {
        if(depth[parent[b][i]] < depth[a]) continue;
        b = parent[b][i];
    }
    if(a == b) return a;

    for(int i=LOG_MXN; i>=0; i--) {
        if(parent[a][i] == parent[b][i]) continue;
        a = parent[a][i], b = parent[b][i];
    }
    return parent[a][0];
}
int kth_node(int a, int b, int k) {
    int lca = LCA(a,b);
    int a_diff = depth[a] - depth[lca], b_diff = depth[b] - depth[lca];
    int u = a; k--;
    if(a_diff < k) u = b, k = b_diff - (k - a_diff);

    int i=0;
    while(k) {
        if(k%2) u = parent[u][i];
        i++; k>>=1;
    }
    return u;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N-1; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }
    memset(depth, -1, sizeof depth);
    memset(cost, 0, sizeof cost);
    parent[1][0] = 1;
    makeTree(1,0);
    linkAncestor();

    cin >> M;
    while(M--) {
        int q, u, v, k; cin >> q;
        if(q == 1) {
            cin >> u >> v;
            int lca = LCA(u,v);
            cout << cost[u] + cost[v] - 2*cost[lca] << '\n';
        }
        else {
            cin >> u >> v >> k;
            cout << kth_node(u,v,k) << '\n';
        }
    }

    return 0;
}