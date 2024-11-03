## [백준 10937 - 두부 모판 자르기](https://www.acmicpc.net/problem/10937)

### 알고리즘
- 최대비용 최대유량 알고리즘

### 풀이
1. 체스판처럼 두부를 검은두부, 흰두부로 나눈다.
2. 검은 두부 -> 흰 두부의 edge를 추가한다.
3. 모든 두부들 -> Sink의 edge를 추가한다.
4. Src -> 검은 두부의 edge를 추가한다.
5. 최대비용 최대유량 알고리즘을 사용한다.

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
        dist = vector<T>(N, numeric_limits<T>::min());
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

        return dist[sink] != numeric_limits<T>::min();
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

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int Src = 0, Sink = 122;
int N;
int cost[4][4] = {
        100, 70, 40, 0,
        70, 50, 30, 0,
        40, 30, 20, 0,
        0, 0, 0, 0
};
int grid[11][11];

bool out_of_bound(int x, int y) { return x<0 || x>=N || y<0 || y>=N; }

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N; i++) {
        string s; cin >> s;
        for(int j=0; j<N; j++) grid[i][j] = min(3, s[j] - 'A');
    }

    MinCost_MaxFlow<int> flo(123);
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            int u = i*N + j + 1;
            flo.add_edge(u, Sink, 1, 0);
            if((i+j)%2) continue;
            flo.add_edge(Src, u, 1, 0);
            for(int d=0; d<4; d++) {
                int ni = i+dx[d], nj = j+dy[d];
                if(out_of_bound(ni,nj)) continue;
                int v = ni*N + nj + 1;
                flo.add_edge(u,v,1,cost[grid[i][j]][grid[ni][nj]]);
            }
        }
    }
    cout << flo.MCMF(Src, Sink).first << endl;

    return 0;
}
```