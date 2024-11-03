## [백준 11408 - 열혈강호 5](https://www.acmicpc.net/problem/11408)

### 알고리즘
- 최소비용 최대유량
- 정점 분할

### 풀이
MinCost_MaxFlow를 알면 쉽게 풀리는 문제다.  
탐색은 SPFA(Shortest Path Fastest Algorithm)을 사용했다.  
1. 직원과 일을 정점 분할한다. cap=1, cost=0  
   직원 in = 1 ~ 400, 직원 out = 401 ~ 800  
   일 in = 801 ~ 1200, 일 out = 1201 ~ 1600
2. 주어진 입력에 따라 직원out -> 일in 을 연결한다. cap=INF, cost=(주어진 입력)
3. Src=0, Sink=1601 으로 해서 최소비용 최대유량 알고리즘을 한다.

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

template <class T> struct MinCost_MaxFlow {
    int N;
    struct Edge {
        int to, rev;
        T cap, cost;
    };
    vector<vector<Edge>> g; // adjacent list
    vector<T> dist; // min dist(cost) from source
    vector<int> pv, pe; // prev's vertex and edge number
    vector<bool> inQ; // is it in queue?

    MinCost_MaxFlow(int _N) : N(_N), g(_N), dist(_N, 0), pv(_N), pe(_N), inQ(_N, false) {}

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
        dist = vector<T>(N, numeric_limits<T>::max());
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
                if(edge.cap>0 && dist[there] > dist[here] + edge.cost) {
                    dist[there] = dist[here] + edge.cost;
                    pv[there] = here; pe[there] = i;
                    if(!inQ[there]) inQ[there] = true, q.push(there);
                }
            }
        }

        return dist[sink] != numeric_limits<T>::max();
    }

    pair<T,T> MCMF(int src, int sink) {
        T min_cost = 0, max_flow = 0;
        while(SPFA(src, sink)) {
            T flow = numeric_limits<T>::max();
            for(int pos=sink; pos!=src; pos=pv[pos])
                flow = min(flow, g[pv[pos]][pe[pos]].cap);
            min_cost += dist[sink] * flow;
            max_flow += flow;
            for(int pos=sink; pos!=src; pos=pv[pos]) {
                int rev = g[pv[pos]][pe[pos]].rev;
                g[pv[pos]][pe[pos]].cap -= flow;
                g[pos][rev].cap += flow;
            }
        }
        return {min_cost, max_flow};
    }
};
int Src=0, Sink=1601;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    MinCost_MaxFlow<int> flo(1602);
    for(int u=1; u<=N; u++) {
        flo.add_edge(Src, u, INF, 0);
        flo.add_edge(u, 400+u, 1, 0);
    }
    for(int v=1; v<=M; v++) {
        flo.add_edge(800+v, 1200+v, 1, 0);
        flo.add_edge(1200+v, Sink, INF, 0);
    }
    for(int u=1; u <= N; u++) {
        int cnt; cin >> cnt;
        while(cnt--) {
            int v, w; cin >> v >> w;
            flo.add_edge(400+u, 800+v, INF, w);
        }
    }
    pii ans = flo.MCMF(Src, Sink);
    cout << ans.second << '\n' << ans.first << '\n';
    return 0;
}
```