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

const int mxn = 1e3+2;
int N, M, K;
char grid[mxn][mxn];
int sx,sy,ex,ey;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,1,-1};
int visited[mxn][mxn];

int solve() {
    queue<pii> q;
    visited[sx][sy] = 0;
    q.emplace(sx,sy);
    int mov = 0;
    while(!q.empty()) {
        int sz = q.size();
        while (sz--) {
            int x = q.front().first, y = q.front().second;
            q.pop();
            if(x == ex && y == ey) return mov;
            for(int d=0; d<4; d++) {
                for(int nx = x, ny = y, k=0; k<K; k++) {
                    nx += dx[d], ny += dy[d];
                    if(grid[nx][ny] == '#' || visited[nx][ny] < mov) break;
                    if(visited[nx][ny] == mov) continue;
                    visited[nx][ny] = mov;
                    q.emplace(nx, ny);
                }
            }
        }
        mov++;
    }
    return -1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(&grid[0][0], &grid[mxn-1][mxn], '#');
    fill(&visited[0][0], &visited[mxn-1][mxn], INF);

    cin >> N >> M >> K;
    for(int i=1; i<=N; i++) {
        string s; cin >> s;
        for(int j=1; j<=M; j++) {
            grid[i][j] = s[j-1];
        }
    }
    cin >> sx >> sy >> ex >> ey;
    cout << solve() << '\n';

    return 0;
}