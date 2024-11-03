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
            max_flow += flow;
            for(int pos=sink; pos!=src; pos=pv[pos]) {
                int rev = g[pv[pos]][pe[pos]].rev;
                g[pv[pos]][pe[pos]].cap -= flow;
                g[pos][rev].cap += flow;
                max_cost += g[pv[pos]][pe[pos]].cost * flow;
            }
        }
        return {max_cost, max_flow};
    }
};

int score[5][5] = {
        {10,8,7,5,1},
        {8,6,4,3,1},
        {7,4,3,2,1},
        {5,3,2,2,1},
        {1,1,1,1,0}
};

const int Src=0, Sink = 2501;
int N, M;
int grid[50][50];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
inline bool out_of_bound(int x, int y) {return x<0 || x>=N || y<0 || y>=M;}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    for(int i=0; i<N; i++) {
        string s; cin >> s;
        for(int j=0; j<M; j++) {
            grid[i][j] = s[j] - 'A';
            if(grid[i][j] == 5) grid[i][j]--;
        }
    }
    MaxCost_MaxFlow<int> flo(2502);
    for(int x=0; x < N; x++) {
        for(int y=0; y < M; y++) {
            int u = x*50 + y + 1;
            flo.add_edge(u,Sink,1,0);
            if((x + y) % 2) continue;
            flo.add_edge(Src,u,1,0);
            for(int d=0; d<4; d++) {
                int nx = x+dx[d], ny = y+dy[d];
                if(out_of_bound(nx,ny)) continue;
                int v = nx*50 + ny + 1;
                flo.add_edge(u,v,1,score[grid[x][y]][grid[nx][ny]]);
            }
        }
    }
    cout << flo.MCMF(Src,Sink).first << '\n';

    return 0;
}