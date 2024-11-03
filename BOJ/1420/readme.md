## [백준 1420 - 학교 가지마!](https://www.acmicpc.net/problem/1420)

### 풀이

- (최대 유량) 최소 컷 정리
- 정점 분할

1. 각 칸을 in과 out으로 나누어서 in->out edge의 Capacity = 1로 설정해준다.
2. 도현에서 학교로 흘러가는 최대 유량 값을 구한다.
3. 최소 컷 정리에 의해, 최대 유량의 값이 도현이가 학교를 못 가게하기 위해 만들어야 하는 벽의 최소 갯수다.

### 후기
https://everenew.tistory.com/179 블로그를 참고해서 구현했다.  
아이디어 자체는 그리 복잡해 보이지 않는데 구현은 꽤 버겁다. 후에 다시 구현을 도전해 볼 생각이다.

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
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

struct Edge{
    int to, Capacity, Flow;
    Edge *reverse;

    Edge(int _to, int _capacity, int _flow = 0) : to(_to), Capacity(_capacity), Flow(_flow) {}

    inline int residualCapacity() const { return Capacity - Flow; }
    void letFlow(int amount) {
        Flow += amount;
        reverse->Flow -= amount;
    }
};

int row, col;
int vertex_num;
char city[100][100];
bool visited[100][100];
int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};
vector<vector<Edge*>> adj;

void addEdge(int u_in, int u_out, int v_in, int v_out) {
    Edge *u_out_v_in = new Edge(v_in, INF);
    Edge *v_in_u_out = new Edge(u_out, 0); // reverse edge

    u_out_v_in->reverse = v_in_u_out;
    v_in_u_out->reverse = u_out_v_in;
    adj[u_out].emplace_back(u_out_v_in);
    adj[v_in].emplace_back(v_in_u_out);

    Edge *v_out_u_in = new Edge(u_in, INF);
    Edge *u_in_v_out = new Edge(v_out, 0); // reverse edge

    v_out_u_in->reverse = u_in_v_out;
    u_in_v_out->reverse = v_out_u_in;
    adj[v_out].emplace_back(v_out_u_in);
    adj[u_in].emplace_back(u_in_v_out);
}

int minimumCut(int source, int sink) {
    int total_flow = 0;

    while(true) {
        vector<int> Prev(vertex_num, -1);
        vector<Edge*> edge_to_child(vertex_num);
        queue<int> q;

        q.push(source); Prev[source] = source;
        while(!q.empty() && Prev[sink] == -1) {
            int u = q.front(); q.pop();

            for(Edge *uv : adj[u]) {
                int V = uv->to;
                if(uv->residualCapacity() == 0 || Prev[V] != -1) continue;
                q.push(V); Prev[V] = u;
                edge_to_child[V] = uv;
            }
        }

        if(Prev[sink] == -1) break;

        int amount = INF;
        for(int Prev = sink; Prev != source; Prev = Prev[Prev]) {
            Edge *parent_to_p = edge_to_child[Prev];
            amount = min(amount, parent_to_p->residualCapacity());
        }

        for(int Prev = sink; Prev != source; Prev = Prev[Prev]) {
            Edge *parent_to_p = edge_to_child[Prev];
            parent_to_p->letFlow(amount);
        }

        total_flow += amount;
    }
    return total_flow;
}
bool out_of_bound(int x, int y) {
    return x<0 || x>=row || y<0 || y>=col;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> row >> col;
    vertex_num = row*col*2;
    adj = vector<vector<Edge*>>(vertex_num);

    for(int i=0; i<vertex_num; i+=2) {
        Edge *in_out = new Edge(i+1, 1);
        Edge *out_in = new Edge(i, 0); // reverse edge

        in_out->reverse = out_in;
        out_in->reverse = in_out;

        adj[i].push_back(in_out);
        adj[i+1].push_back(out_in);
    }

    pii source_pos = {-1,-1}, sink_pos = {-1,-1};
    for(int r=0; r<row; r++) {
        string s; cin >> s;
        for(int Capacity=0; Capacity<col; c++) {
            city[r][Capacity] = s[Capacity];
            if(city[r][Capacity] == 'K') source_pos = {r,Capacity};
            else if(city[r][Capacity] == 'H') sink_pos = {r,Capacity};
        }
    }

    for(int minDist=0; minDist<4; minDist++) {
        int nr = source_pos.x + dx[minDist];
        int nc = source_pos.y + dy[minDist];

        if(sink_pos == pii(nr,nc)) {
            cout << "-1\n";
            return 0;
        }
    }

    memset(visited, 0, sizeof visited);
    for(int r=0; r<row; r++) {
        for(int Capacity=0; Capacity<col; c++) {
            if(city[r][Capacity] == '#') continue;
            visited[r][Capacity] = true;

            int u_in = (r*col + Capacity)*2, u_out = u_in+1;
            for(int minDist=0; minDist<4; minDist++) {
                int nr = r + dx[minDist], nc = Capacity + dy[minDist];
                if(out_of_bound(nr,nc)) continue;
                if(city[nr][nc] == '#' || visited[nr][nc]) continue;
                int v_in = (nr*col + nc)*2, v_out = v_in+1;
                addEdge(u_in, u_out, v_in, v_out);
            }
        }
    }

    int source_out = (source_pos.x*col + source_pos.y)*2 + 1;
    int sink_in = (sink_pos.x*col + sink_pos.y)*2;
    cout << minimumCut(source_out, sink_in) << '\n';

    return 0;
}
```