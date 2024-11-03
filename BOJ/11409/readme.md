## [백준 11409 - 열혈강호 6](https://www.acmicpc.net/problem/11409)

### 알고리즘
- 최소 비용 최대 유량 알고리즘

### 풀이
1. min cost max flow 알고리즘을 사용한다.
2. dist를 계산할 때 max cost로 바꿔야 하므로 반대로 계산하면 된다.   
   dist를 numeric_limits<int>::min()로 초기화한다.  
   dist[there] < dist[here] + edge.cost 일 때 값을 바꿔주고 queue에 넣어준다.

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

template <class T> struct MaxCost_MaxFlow {
    int N;
    struct Edge {
        int to, rev;
        T cap, cost;
    };
    vector<vector<Edge>> g; // adjacent list
    vector<T> dist; // min dist(cost) from source
    vector<int> pv, pe; // prev's vertex and edge number
    vector<bool> inQ; // is it in queue?

    MaxCost_MaxFlow(int _N) : N(_N), g(_N), dist(_N, 0), pv(_N), pe(_N), inQ(_N, false) {}

    void clear() {
        for(int i=0; i<N; i++) g[i].clear();
    }

    void add_edge(int u, int v, T cap, T cost) {
        int u_idx = g[u].size();
        int v_idx = g[v].size();
        if(u == v) v_idx++;
        g[u].emplace_back(Edge{v, v_idx, cap, cost});
        g[v].emplace_back(Edge{u, u_idx, (T)0, -cost});
    }
    bool SPFA(int src, int sink) {
        dist = vector<T>(N, numeric_limits<int>::min());
        inQ = vector<bool>(N, false);
        queue<int> q;

        dist[src] = 0; inQ[src] = true;
        q.push(src);
        while(!q.empty()) {
            int here = q.front(); q.pop();
            inQ[here] = false;
            for(int i=0; i<g[here].size(); i++) {
                Edge edge = g[here][i];
                int there = edge.to;
                if(edge.cap>0 && dist[there] < dist[here] + edge.cost) {
                    dist[there] = dist[here] + edge.cost;
                    pv[there] = here; pe[there] = i;
                    if(!inQ[there]) inQ[there] = true, q.push(there);
                }
            }
        }

        return dist[sink] != numeric_limits<int>::min();
    }

    pair<T,T> MCMF(int src, int sink) {
        T max_cost = 0, max_flow = 0;
        while(SPFA(src, sink)) {
            T flow = numeric_limits<T>::max();
            for(int pos=sink; pos!=src; pos=pv[pos])
                flow = min(flow, g[pv[pos]][pe[pos]].cap);
            max_cost += dist[sink] * flow;
            max_flow += flow;
            for(int pos=sink; pos!=src; pos=pv[pos]) {
                int rev = g[pv[pos]][pe[pos]].rev;
                g[pv[pos]][pe[pos]].cap -= flow;
                g[pos][rev].cap += flow;
            }
        }
        return {max_cost, max_flow};
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int Src=0, Sink=1601;
    // 직원in = 1~400, 직원out = 401~800
    // 일in = 801~1200, 일out = 1201~1600
    MaxCost_MaxFlow<int> flo(1602);
    int N, M; cin >> N >> M;
    for(int i=1; i<=N; i++) {
        flo.add_edge(Src, i, INF, 0);
        flo.add_edge(i, 400+i, 1, 0);
    }
    for(int j=1; j<=M; j++) {
        flo.add_edge(800+j, 1200+j, 1, 0);
        flo.add_edge(1200+j, Sink, INF, 0);
    }
    for(int i=1; i<=N; i++) {
        int cnt; cin >> cnt;
        while(cnt--) {
            int j, w; cin >> j >> w;
            flo.add_edge(400+i, 800+j, INF, w);
        }
    }
    pii res = flo.MCMF(Src, Sink);
    cout << res.second << '\n' << res.first << '\n';

    return 0;
}
```