## [백준 3640 - 제독](https://www.acmicpc.net/problem/3640)

### 풀이 
- 최소 비용 최대 유량(Minimum Cost Maximum Flow, MCMF)
- 정정 분리

MCMF를 모르면 풀지 못하는 문제다.  
MCMF에서 최소비용 갱신은 SPFA(Shortest Path Fastest Algorithm, bellman-ford의 최적화 버전)을 사용한다.  

1. 정점분리를 사용한다.
    - source, sink의 in->out은 capacity = 2로 설정
    - 나머지 정점의 in->out은 capacity = 1로 설정
   이때, in->out의 edge들의 cost = 0이다.
2. 주어진 모든 edge의 capacity = 1로 설정한다.  
   이때, reverse edge의 cost는 -w가 된다.
3. source에서 sink의 MCMF를 찾아서 출력한다.

### 후기
깔끔하게 구현해보고 싶어 다른 분들의 코드들을 참고해서 여러가지를 시도해보았는데,  
해당 코드가 가장 깔끔하고 메모리 사용도 적었다.
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
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

const int mxn = 2002;

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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int V, E;
    while(cin >> V >> E) {
        MinCost_MaxFlow<int> flo(2*V+2);

        flo.add_edge(0,1,2,0); // set source
        // split vertices
        for(int u=1; u<=V; u++) {
            if(u == 1 || u == V) flo.add_edge(u, u+V, 2, 0);
            else flo.add_edge(u, u+V, 1, 0);
        }
        flo.add_edge(2*V, 2*V+1, 2, 0); // set sink

        // edges
        while(E--) {
            int u, v, w; cin >> u >> v >> w;
            flo.add_edge(u+V, v, 1, w);
        }

        cout << flo.MCMF(0, 2*V+1).first << '\n';
    }


    return 0;
}
```