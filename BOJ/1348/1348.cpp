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

struct type {
    int x, y, dist;
    type() {}
    type(int _x, int _y, int _dist) : x(_x), y(_y), dist(_dist) {}
};

int R, C, carNum = 1, parkNum = 101;
int grid[51][51];
bool visited[51][51];
vector<pii> cars, parks;
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
vector<pii> g[201];
bool capacity[201];
int parent[201];

inline bool out_of_bound(int x, int y) {return x<1 || x>R || y<1 || y>C;}
void bfs(int i, int car_number) {
    memset(visited, 0, sizeof visited);
    int u = car_number;
    queue<type> q;
    visited[cars[i].first][cars[i].second] = true;
    q.emplace(cars[i].first, cars[i].second, 0);
    while(!q.empty()) {
        int x = q.front().x, y = q.front().y, dist = q.front().dist;
        q.pop();
        if(grid[x][y] > 0) g[u].emplace_back(grid[x][y], dist);
        for(int d=0; d<4; d++) {
            int nx = x+dx[d], ny = y+dy[d];
            if(out_of_bound(nx,ny) || visited[nx][ny] || grid[nx][ny] == -1) continue;
            visited[nx][ny] = true;
            q.emplace(nx,ny,dist+1);
        }
    }
}
bool dfs(int here, int time) {
    for(int i=0; i<g[here].size(); i++) {
        pii edge = g[here][i];
        int there = edge.first, cost = edge.second;
        if(capacity[there] || cost > time) continue;
        capacity[there] = true;
        if(parent[there] == -1 || dfs(parent[there], time)) {
            parent[there] = here;
            return true;
        }
    }
    return false;
}
bool bipartite(int time) {
    memset(parent, -1, sizeof parent);
    for(int i=1; i<carNum; i++) {
        memset(capacity, 0, sizeof capacity);
        if(!dfs(i, time)) return false;
    }
    return true;
}
int solve() {
    int l=0, r=2501;
    while(l<r) {
        int m = (l+r)/2;
        if(bipartite(m)) r = m;
        else l = m+1;
    }
    return bipartite(r) ? r : -1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> R >> C;
    for(int i=1; i<=R; i++) {
        for(int j=1; j<=C; j++) {
            char c; cin >> c;
            if(c == 'X') grid[i][j] = -1;
            else if(c == 'P') {
                parks.emplace_back(i,j);
                grid[i][j] = parkNum++;
            }
            else {
                grid[i][j] = 0;
                if(c == 'C') {
                    cars.emplace_back(i,j);
                    carNum++;
                }
            }
        }
    }
    for(int i=0, car_number=1; i<cars.size(); i++, car_number++)
        bfs(i, car_number);
    cout << solve() << '\n';
    return 0;
}