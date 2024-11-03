## [백준 11407 - 책 구매하기 3](https://www.acmicpc.net/problem/11407)

### 알고리즘
- 최대 유량 최소 비용
- 정점 분할

### 풀이
1. i번째 사람의 [사람in -> 사람out] 의 cap = Ai 라 한다.
2. j번째 서점의 [서점in -> 서점out] 의 cap = Bj 라 한다.
3. [i번째 사람out -> j번째 서점in] 의 cap = Cij, cost = Dij 가 된다.
4. Src(=0) -> Sink(=401)로 가는 MCMF(MinCost MaxFlow)를 구한다.  
   사람in = 1 ~ 100, 사람out = 101 ~ 200  
   서점in = 201 ~ 300, 서점out = 301 ~ 400

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

const int Src=0, Sink=401;
int N, M;
int C[101][101];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    MinCost_MaxFlow<int> flo(402);
    cin >> N >> M;
    for(int i=1; i<=N; i++) {
        flo.add_edge(Src, i, INF, 0);
        int A; cin >> A;
        flo.add_edge(i, 100+i, A, 0);
    }
    for(int i=1; i<=M; i++) {
        int B; cin >> B;
        flo.add_edge(200+i, 300+i, B, 0);
        flo.add_edge(300+i, Sink, INF, 0);
    }
    for(int j=1; j<=M; j++) {
        for(int i=1; i<=N; i++) {
            cin >> C[j][i];
        }
    }
    for(int j=1; j<=M; j++) {
        for(int i=1; i<=N; i++) {
            int D; cin >> D;
            flo.add_edge(100+i, 200+j, C[j][i], D);
        }
    }
    pii ans = flo.MCMF(Src, Sink);
    cout << ans.second << '\n' << ans.first << '\n';

    return 0;
}
```