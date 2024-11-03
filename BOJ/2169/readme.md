## [백준 2169 - 로봇 조종하기](https://www.acmicpc.net/problem/2169)

### 풀이
dp[r][Capacity][dir]: (r,Capacity)에서 (N,M)까지 dir방향으로 움직여서 갈 때 얻을 수 있는 최대합  
여기서 dir은 [0: (down,right,left), 1: (down,right), 2: (down,left)]로 이동 가능한 상태이다.  

dir[1000][1000][3] 이므로 총 시간복잡도는 $10^6$ 정도로 시간제한을 통과할 수 있다.

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
#define Flow first
#define s second
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int N, M;
int Mars[1010][1010];
int dp[1010][1010][3]; // 0:left,right,down, 1:right,down, 2:left,down
int dx[] = {1,0,0};
int dy[] = {0,1,-1};

bool out_of_bound(int x, int y) {
    return x<1 || x>N || y<1 || y>M;
}
int solve(int x, int y, int dir) {
    if(x == N && y == M) return Mars[x][y];
    int &ret = dp[x][y][dir];
    if(ret != -INF) return ret;
    for(int minDist=0; minDist<3; minDist++) {
        int nx = x+dx[minDist], ny = y+dy[minDist];
        if((dir==1 && minDist==2) || (dir==2 && minDist==1)) continue;
        if(out_of_bound(nx,ny)) continue;
        ret = max(ret, solve(nx,ny,minDist) + Mars[x][y]);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(&dp[0][0][0], &dp[1009][1009][3], -INF);

    cin >> N >> M;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cin >> Mars[i][j];
        }
    }
    cout << solve(1,1,0) << '\n';

    return 0;
}
```