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

const int mxn = 1e5+1, LOG_MXN = 19;
int N, Q, R;
int depth[mxn], treeSize[mxn];
int parent[mxn][LOG_MXN+1];
vector<vector<int>> g;

int makeTree(int here, int level) {
    depth[here] = level;
    treeSize[here] = 1;
    for(int there : g[here]) {
        if(depth[there] != -1) continue;
        parent[there][0] = here;
        treeSize[here] += makeTree(there, level+1);
    }
    return treeSize[here];
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

    int T; cin >> T;
    for(int tc=1; tc<=T; tc++) {
        memset(depth, -1, sizeof depth);

        cin >> N >> Q >> R;
        g = vector<vector<int>>(N+1);
        for(int i=0; i<N-1; i++) {
            int u, v; cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        makeTree(1,1);
        linkAncestor();

        cout << "Case #" << tc << ":\n";
        while(Q--) {
            int S, U; cin >> S >> U;
            if(S == 0) R = U;
            else {
                if(R == U) cout << N << endl;
                else if(LCA(R,U) == U) {
                    int here = R;
                    for(int i=LOG_MXN; i>=0; i--) {
                        if(depth[parent[here][i]] < depth[U]+1) continue;
                        here = parent[here][i];
                    }
                    cout << N - treeSize[here] << endl;
                }
                else {
                    cout << treeSize[U] << endl;
                }
            }
        }
    }

    return 0;
}