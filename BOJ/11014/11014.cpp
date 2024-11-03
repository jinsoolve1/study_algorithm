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

const int MXN = 80*80;
int N, M, ans;
char classroom[80][80];
int dx[] = {-1,-1,0,0};
int dy[] = {-1,1,-1,1};
bool visited[MXN];
int parent[MXN];
vector<vector<int>> g;

inline bool out_of_bound(int x, int y) { return x<0 || x>=N || y<0 || y>=M; }
inline int nodeNum(int x, int y) { return x*M + y; }
void makeBigraph() {
    for(int x=0; x<N; x++) {
        for(int y=0; y<M; y++) {
            if(classroom[x][y] == 'x') continue;
            for(int d=0; d<4; d++) {
                int nx = x+dx[d], ny = y+dy[d];
                if(out_of_bound(nx,ny) || classroom[nx][ny] == 'x') continue;
                int u = nodeNum(x,y), v = nodeNum(nx,ny);
                g[u].emplace_back(v);
                g[v].emplace_back(u);
            }
        }
    }
}
bool dfs(int here) {
    for(int there : g[here]) {
        if(visited[there]) continue;
        visited[there] = true;
        if(parent[there] == -1 || dfs(parent[there])) {
            parent[there] = here;
            return true;
        }
    }
    return false;
}
int bipartite() {
    memset(parent, -1, sizeof parent);
    int ret = 0;
    for(int here=0; here<N*M; here++) {
        if((here%M)%2 == 1) continue;
        memset(visited, 0, sizeof visited);
        ret += dfs(here);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        cin >> N >> M;

        // init
        ans = 0;
        g = vector<vector<int>>(N*M);

        for(int i=0; i<N; i++) {
            string s; cin >> s;
            for(int j=0; j<M; j++) {
                classroom[i][j] = s[j];
                ans += (classroom[i][j] == '.');
            }
        }
        makeBigraph();
        cout << ans - bipartite() << '\n';
    }



    return 0;
}