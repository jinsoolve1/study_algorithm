## [백준 2152 - 여행 계획 세우기](https://www.acmicpc.net/problem/2152)

### 알고리즘
- 강한 연결 요소(SCC)

### 풀이
1. 도시들의 SCC를 찾는다.
2. 기존 도시의 edge를 참고해서 SCC들 끼리를 연결한다.
3. bfs로 S -> T 의 최대 도시 개수를 출력한다.

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
#include <climits>

#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

class SCC {
private:
    int N, _id, _scc;
    vector<int> id, scc, cnt, dp; //scc[x] := x번 노드의 scc 번호, cnt[scc_x] := scc_x번의 scc의 집합 크기, dp[x] := src->x 의 최대 개수(bfs)
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
                cnt[_scc]++;
                if(t == u) break;
            }
            _scc++;
        }

        return parent;
    }
    int bfs(int src, int sink) {
        dp = vector<int>(_scc, 0);
        queue<int> q;

        q.push(src); dp[src] = cnt[src];
        while(!q.empty()) {
            int here = q.front(); q.pop();
            for(int there : scc_g[here]) {
                if(dp[there] >= dp[here] + cnt[there]) continue;
                dp[there] = dp[here] + cnt[there];
                q.push(there);
            }
        }
        return dp[sink];
    }

public:
    SCC(int _N) : N(_N), _id(1), _scc(1), id(N+1, -1), scc(N+1, -1), cnt(N+1,0), g(N+1) {}

    void add_edge(int u, int v) { g[u].emplace_back(v); }
    void find_scc() {
        for(int i=1; i<=N; i++)
            if(id[i] == -1) dfs(i);
        scc_g.resize(_scc);
        for(int u=1; u<=N; u++) {
            for(int v : g[u]) {
                if(scc[u] != scc[v]) scc_g[scc[u]].emplace_back(scc[v]);
            }
        }
    }
    int solve(int S, int T) {
        return bfs(scc[S], scc[T]);
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, S, T; cin >> N >> M >> S >> T;
    SCC scc(N);
    while(M--) {
        int u, v; cin >> u >> v;
        scc.add_edge(u,v);
    }
    scc.find_scc();
    cout << scc.solve(S,T) << '\n';


    return 0;
}
```