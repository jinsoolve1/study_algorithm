## [백준 15683 - 감시](https://www.acmicpc.net/problem/15683)

### 알고리즘
- 구현 (시뮬레이션)
- 브루트포스 (백트래킹)
- 비트마스킹

### 풀이
1. 카메라는 최대 8개이고, 맵의 최대 크기가 8x8 이므로 백트래킹을 해도 4^8 x 8 x 8 = 4e6 이다.
2. 카메라가 N개라고 할 때, 비트마스킹을 이용하여 0 ~ 4^N-1 까지 모두 순환하면서 각 카메라가 해당 방향일 때 사각지대의 너비를 구한다.
3. 주의해야 할 점들이 있다.
   1. 사각지대 면적을 구할 때, 카메라가 있는 공간이나 벽이 있는 공간은 제외하고 카운트해야 한다.
   2. 구현할 때의 문제인데 각 카메라의 방향을 정한 것과 dx, dy 배열의 순서를 잘 조합시켜서 의도대로 구현했는지를 확인해야 한다.  
      예를 들어, 2번 카메라의 방향을 [0,2]라고 하고 dx, dy를 동,서,남,북 방향으로 해버리면 동과 남은 반대방향이 아니다.  
      따라서 dx,dy를 시계방향으로 설정해야 의도대로 구현한 것이다.

### 후기
단순 구현의 문제이다. 방향 설정을 잘 하도록 하자.

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
#define x first
#define y second

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int N, M;
int board[9][9];
vector<pii> camLoc;
bool visited[9][9];
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
vector<int> camera[6];

bool out_of_bound(int x, int y) { return x<1 || x>N || y<1 || y>M; }
int blind_spot(int camDir) {
    memset(visited, 0, sizeof visited);
    for(pii here : camLoc) {
        int d = camDir%4; camDir /= 4;
        for(int nd : camera[board[here.x][here.y]]) {
            nd = (nd + d) % 4;
            int nx = here.x, ny = here.y;
            while(true) {
                if(out_of_bound(nx,ny) || board[nx][ny]==6) break;
                visited[nx][ny] = true;
                nx += dx[nd], ny += dy[nd];
            }
        }
    }
    int ret = N*M;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(board[i][j]) ret--;
            else ret -= visited[i][j];
        }
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    camera[1].emplace_back(0);
    camera[2].emplace_back(0); camera[2].emplace_back(2);
    camera[3].emplace_back(0); camera[3].emplace_back(1);
    camera[4].emplace_back(0); camera[4].emplace_back(1); camera[4].emplace_back(2);
    camera[5].emplace_back(0); camera[5].emplace_back(1); camera[5].emplace_back(2); camera[5].emplace_back(3);

    cin >> N >> M;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cin >> board[i][j];
            if(1 <= board[i][j] && board[i][j] <= 5) camLoc.emplace_back(i,j);
        }
    }
    int ans = INF;
    for(int bit = pow(4,camLoc.size())-1; bit >= 0; bit--) {
        ans = min(ans, blind_spot(bit));
    }
    cout << ans << endl;

    return 0;
}
```