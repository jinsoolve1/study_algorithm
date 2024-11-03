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

const int mxn = 50*50;

struct Edge {
    int to, cap, rev;

    Edge() {}
    Edge(int _to, int _rev, int _cap) : to(_to), rev(_rev), cap(_cap) {}
};

int n, m, src, sink, ans;

int pv[2 * mxn + 2], pe[2 * mxn + 2];
vector<vector<Edge>> g;

int dx[] = {-1,1,0,0};
int dy[] = {0,0,1,-1};

inline bool out_of_bound(int x, int y) { return x<1 || x>n || y<1 || y>m; }
void addEdge(int u, int v, int cap) {
    int u_idx = (int)g[u].size(), v_idx = (int)g[v].size();
    if(u == v) v_idx++;
    g[u].emplace_back(v,v_idx, cap);
    g[v].emplace_back(u,u_idx,0);
}
int maxFlow(int start, int end) {
    int ret = 0;
    while(true) {
        memset(pv, -1, sizeof pv);
        memset(pe, -1, sizeof pe);
        queue<int> q;
        q.push(start);
        while(!q.empty()) {
            int here = q.front(); q.pop();
            for(int i=0; i<g[here].size(); i++) {
                Edge edge = g[here][i];
                int there = edge.to;
                if(edge.cap && pv[there] == -1) {
                    pv[there] = here;
                    pe[there] = i;
                    q.push(there);
                    if(there == end) break;
                }
            }
        }
        if(pv[end] == -1) break;
        int flow = INF;
        for(int there=end, here; there!=start; there=here) {
            here = pv[there];
            flow = min(flow, g[here][pe[there]].cap);
        }
        ret += flow;
        for(int there=end, here; there!=start; there=here) {
            here = pv[there];
            int rev = g[here][pe[there]].rev;
            g[here][pe[there]].cap -= flow;
            g[there][rev].cap += flow;
        }
    }
    return ret;
}
int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        g = vector<vector<Edge>>(2*mxn+2);

        cin >> n >> m;
        src = 0, sink = n * m + mxn + 1;
        ans = 0;
        for(int x=1; x <= n; x++) {
            for(int y=1; y <= m; y++) {
                int val; cin >> val; ans += val;
                int u = (x-1)*m+y;
                if((x+y)%2) addEdge(src, u, INF);
                else addEdge(u+mxn, sink, INF);
                addEdge(u,u+mxn,val);
                for(int d=0; d<4; d++) {
                    int nx = x+dx[d], ny = y+dy[d];
                    if(out_of_bound(nx,ny)) continue;
                    int v = (nx-1)*m+ny;
                    addEdge(u+mxn,v,INF);
                }
            }
        }
        cout << ans - maxFlow(src, sink) << '\n';
    }


    return 0;
}
