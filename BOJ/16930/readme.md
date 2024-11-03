## [백준 16930 - 달리기](https://www.acmicpc.net/problem/16930)

### 알고리즘
- BFS

### 풀이
visited[x][y] := (sx,sy) -> (x,y)에 처음 도달한 시간
1. (sx,sy)에서 출발하는 BFS를 한다.
2. (x,y)에서 움직인 위치를 (nx,ny)라 하자. 현재 움직인 시간이 mov라 하자.
3. visited[nx][ny] < mov 라면 break,
   visited[nx][ny] == mov라면 continue를 한다.

visited[nx][ny] < mov일 때는 이미 이전 mov에서 해당 위치에서의 탐색을 끝낸 것이기 때문에 어차피 그 다음 위치도 끝났을 것이라는 점을 알 수 있다.  
visited[nx][ny] == mov일 때는 queue에 한 번 더 추가해 줄 필요는 없지만 그 다음 위치가 이미 탐색이 끝맞춘 경우가 아닐 수 있기 때문에 계속해서 탐색해 준다.


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
```
### 후기
P3 문제 치고는 꽤 쉬운 문제였던 것 같은데, 괜히 겁먹어서 오히려 헤맸던 것 같다.