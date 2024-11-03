## [백준 11406 - 책 구매하기 2](https://www.acmicpc.net/problem/11406)

### 알고리즘
- 유량 알고리즘
- 이분 매칭

### 풀이
단순한 이분매칭 문제다.  
사람과 서점을 정점분할해서 책의 개수로 capability를 설정하고 사람과 서점을 잇는 간선의 용량을 C로 설정하면 풀리는 문제다.

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

int Src=0, Sink=401;
int N, M;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    MinCost_MaxFlow<int> flo(402);
    cin >> N >> M;
    for(int i=1; i<=N; i++) {
        int A; cin >> A;
        flo.add_edge(Src,i,INF,0);
        flo.add_edge(i,100+i,A,0);
    }
    for(int j=1; j<=M; j++) {
        int B; cin >> B;
        flo.add_edge(200+j, 300+j, B, 0);
        flo.add_edge(300+j, Sink, INF, 0);
    }

    for(int j=1; j<=M; j++) {
        for(int i=1; i<=N; i++) {
            int C; cin >> C;
            flo.add_edge(100+i, 200+j, C, 0);
        }
    }
    cout << flo.MCMF(Src, Sink).second << '\n';

    return 0;
}
```