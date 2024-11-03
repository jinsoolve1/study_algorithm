## [백준 2367 - 파티](https://www.acmicpc.net/problem/2367)

### 알고리즘 
- 네트워크 플로우
- 정점 분할

### 풀이
1. 사람 노드와 음식 노드를 만들고 이를 정점분할 한다.
2. 사람 in -> out의 capacity=K가 된다.
3. 음식 in -> out의 capacity는 주어진 각 음식의 양의 제한이 된다.
4. 사람 out -> 음식 in의 capacity=1이 된다. (한 사람당 같은 음식의 종류는 1개만 가져올 수 있기 때문)
5. [Src -> 사람 in] 과 [음식 out -> Sink]를 capacity=INF으로 연결해준다.
6. 최대 유량값을 구한다.

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

template<class T> struct MaxFlow {
    int N;
    struct Edge {
        int to, rev;
        T cap;
    };
    vector<vector<Edge>> g;
    vector<int> pv, pe;

    MaxFlow() {}
    MaxFlow(int _N) : N(_N), g(_N), pv(_N), pe(_N) {}
    ~MaxFlow() { this->clear(); }
    void clear() {
        for(int i=0; i<N; i++) g[i].clear();
    }
    void addEdge(int u, int v, T cap) {
        int u_idx = g[u].size();
        int v_idx = g[v].size();
        if(u == v) v_idx++;
        g[u].emplace_back(Edge{v,v_idx,cap});
        g[v].emplace_back(Edge{u,u_idx,(T)0});
    }
    bool BFS(int src, int sink) {
        fill(all(pv), -1); fill(all(pe), -1);
        queue<int> q;
        q.push(src);
        while(!q.empty()) {
            int here = q.front(); q.pop();
            for(int i=0; i<g[here].size(); i++) {
                Edge edge = g[here][i];
                int there = edge.to;
                if(edge.cap && pv[there] == -1) {
                    pv[there] = here; pe[there] = i;
                    q.push(there);
                    if(there == sink) break;
                }
            }
        }
        return pv[sink] != -1;
    }
    T Edmonds_Karp(int src, int sink) {
        T max_flow = 0;
        while(BFS(src,sink)) {
            T flow = numeric_limits<T>::max();
            for(int pos=sink; pos!=src; pos=pv[pos]) flow = min(flow, g[pv[pos]][pe[pos]].cap);
            for(int pos=sink; pos!=src; pos=pv[pos]) {
                int rev = g[pv[pos]][pe[pos]].rev;
                g[pv[pos]][pe[pos]].cap -= flow;
                g[pos][rev].cap += flow;
            }
            max_flow += flow;
        }
        return max_flow;
    }
};

int N, K, D;
int Src=0, Sink=601;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // human 1~200(in) 201~400(out)
    // food  401~500(in) 501~600(out)
    // Src=0, Sink=601
    MaxFlow<int> flo(602);

    cin >> N >> K >> D;
    for(int i=1; i<=N; i++) {
        flo.addEdge(Src,i,INF2);
        flo.addEdge(i,200+i,K);
    }
    for(int i=1; i<=D; i++) {
        int x; cin >> x;
        flo.addEdge(400+i,500+i,x);
        flo.addEdge(500+i,Sink,INF2);
    }
    for(int i=1; i<=N; i++) {
        int Z; cin >> Z;
        while(Z--) {
            int x; cin >> x;
            flo.addEdge(200+i,400+x,1);
        }
    }
    cout << flo.Edmonds_Karp(Src, Sink) << '\n';

    return 0;
}
```