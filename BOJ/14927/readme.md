## [백준 14927 - 전구 끄기](https://www.acmicpc.net/problem/14927)

### 알고리즘
- 비트마스킹
- 브루트포스
- 그리디

### 풀이
1. 비트마스킹을 이용해서 전구의 on/off 상태를 확인한다.
2. (x,y)를 기준으로 (x-1,y)의 상태를 바꿀 수 있는 마지막 기회는 지금밖에 없다.  
   이를 이용해서 (x-1,y) 전구가 켜져있으면 off, 꺼져있으면 그대로 놔둔다.
3. 얼핏 보았을 때 dp를 사용해야지만 시간초과가 나지 않을 것처럼 보이나, 2번 조건으로 인해 첫번째 줄을 제외하고는 상태가 제약된다.  
   따라서 브루트포스 알고리즘을 사용하여 해결한다.

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

int N;
bool bulb[18][18];
int dx[] = {0,-1,1,0,0};
int dy[] = {0,0,0,-1,1};

bool out_of_bound(int x, int y) { return x<0 || x>=N || y<0 || y>=N; }
void turn(int x, int y) {
    for(int d=0; d<5; d++) {
        int nx = x+dx[d], ny = y+dy[d];
        if(out_of_bound(nx,ny)) continue;
        bulb[nx][ny] = !bulb[nx][ny];
    }
}
int solve(int x, int y, int bit) {
    if(y == N) return solve(x+1, 0, bit);
    if(x == N) return (bit == 0 ? 0 : INF);
    int ret = INF;
    bit = (2*bit + bulb[x][y]) % (1<<N);
    if(x==0 || bulb[x-1][y] == 0)
        ret = min(ret, solve(x,y+1,bit));
    if(x==0 || bulb[x-1][y] == 1) {
        turn(x,y);
        ret = min(ret, solve(x,y+1,bit^3) + 1);
        turn(x,y);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            cin >> bulb[i][j];

    int res = solve(0,0,0);
    if(res == INF) res = -1;
    cout << res << '\n';

    return 0;
}
```

### 후기
재귀함수 말고도 반복문을 이용해서 해결하는 방법이 있는 듯하다.  
추후에 공부할 예정이다.