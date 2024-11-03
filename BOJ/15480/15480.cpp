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
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

const int N_MXN = 1e5;
const int LOG_MXN = 20;
int N, M;
vector<int> g[N_MXN+1];
int depth[N_MXN+1];
int parent[N_MXN+1][LOG_MXN+1];

void makeTree(int here, int level) {
    depth[here] = level;
    for(int there : g[here]) {
        if(depth[there] != -1) continue;
        parent[there][0] = here;
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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(depth, -1, sizeof depth);

    cin >> N;
    for(int i=0; i<N-1; i++) {
        int u, v; cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    // make tree by root 1
    parent[1][0] = 1;
    makeTree(1,0);
    linkAncestor();

    cin >> M;
    while(M--) {
        int r, u, v; cin >> r >> u >> v;

        // LCA1: LCA of r-u, LCA2: LCA of r-v, LCA3: LCA of u-v
        // find deepest LCA in 3 of them
        int LCA1 = LCA(r,u), LCA2 = LCA(r,v), LCA3 = LCA(u,v);

        int ans = LCA1;
        if(depth[ans] < depth[LCA2]) ans = LCA2;
        if(depth[ans] < depth[LCA3]) ans = LCA3;
        cout << ans << '\n';
    }


    return 0;
}