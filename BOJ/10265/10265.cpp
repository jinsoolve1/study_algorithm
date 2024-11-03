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

int n, k;

class SCC {
private:
    int N, _id, _scc;
    vector<int> id, scc, scc_sz; //scc[x] := x번 노드의 scc 번호, scc_sz[scc_x] := scc_x번의 scc의 집합 크기, dp[x] := src->x 의 최대 개수(bfs)
    vector<bool> isRoot, knapsack;
    vector<vector<int>> g, scc_g;
    stack<int> st;

    int dfs(int u) {
        id[u] = _id++;
        st.push(u);

        int parent = id[u];
        for(int v : g[u]) {
            if(id[v] == -1) parent = min(parent, dfs(v));
            else if(scc[v] == -1) parent = min(parent, id[v]);
        }

        if(parent == id[u]) {
            while(true) {
                int t = st.top(); st.pop();
                scc[t] = _scc;
                scc_sz[_scc]++;
                if(t == u) break;
            }
            _scc++;
        }

        return parent;
    }
    void find_max_cnt(int here, int prev_cnt) {
        if(prev_cnt + scc_sz[here] > k) return;
        for(int i=k; i>=scc_sz[here]; i--)
            knapsack[i] = knapsack[i] | knapsack[i-scc_sz[here]];
        for(int there : scc_g[here])
            find_max_cnt(there, prev_cnt + scc_sz[here]);
    }

public:
    SCC(int _N) : N(_N), _id(1), _scc(1), id(N+1, -1), scc(N+1, -1), scc_sz(N + 1, 0), g(N + 1) {}

    void add_edge(int u, int v) { g[u].emplace_back(v); }
    void find_scc() {
        for(int i=1; i<=N; i++)
            if(id[i] == -1) dfs(i);
        scc_g.resize(_scc);
        isRoot.resize(_scc, true);
        for(int u=1; u<=N; u++) {
            for(int v : g[u]) {
                if(scc[u] != scc[v]) {
                    scc_g[scc[u]].emplace_back(scc[v]);
                    isRoot[scc[v]] = false;
                }
            }
        }
    }
    int solve() {
        knapsack.resize(k+1, false);
        knapsack[0] = true;
        for(int i=1; i<_scc; i++) {
            if(!isRoot[i]) continue;
            find_max_cnt(i, 0);
        }
        for(int i=k; i>=0; i--)
            if(knapsack[i]) return i;
        return 0;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    SCC scc(n);
    for(int v=1; v<=n; v++) {
        int u; cin >> u;
        scc.add_edge(u,v);
    }
    scc.find_scc();
    cout << scc.solve() << '\n';
    return 0;
}