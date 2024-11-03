## [Atcoder_ABC345_D - Tiling](https://atcoder.jp/contests/abc345/tasks/abc345_d)

### 알고리즘
- 백트래킹, 브루트포스
- dfs
- 비트마스킹

### 풀이
H, W인 직사각형에 타일링한다.
1. (sx, sy)에서 부터 색칠한다고 가정할 때, (0,0) ~ (sx-1,W)와 (sx,0) ~ (sx,sy-1)까지는 모두 타일링되었다고 가정하자.
2. 비트마스킹을 이용해서 안 사용한 타일들을 해당 지점에 넣을 수 있는지를 확인한다.
3. 이때 타일은 AxB와 BxA 방식으로 붙일 수 있다.
4. 가능하다면 true, 아니라면 false를 반환한다.

### 배운 점
(sx,sy)를 고정시켜놓고 하는게 핵심이다.  
그냥 모든 지점을 매번 확인하면 시간이 매우 오래걸린다. 그러나 타일링할 때 빈공간이 있으면 안되므로 그점을 이용해서 시간을 단축시킬 수 있다.

### 코드
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

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int N, H, W;
int a[7], b[7];
bool c[10][10];


bool check(int x, int y, int h, int w) {
    if(x+h > H || y+w > W) return false;
    for(int nx=x; nx<x+h; nx++) {
        for(int ny=y; ny<y+w; ny++) {
            if(c[nx][ny]) return false;
        }
    }
    return true;
}
void color(int x, int y, int h, int w, bool val) {
    for(int nx=x; nx<x+h; nx++) {
        for(int ny=y; ny<y+w; ny++) {
            c[nx][ny] = val;
        }
    }
}

bool dfs(int tile, int sx, int sy) {
    while(sx<H && c[sx][sy]) {
        if(++sy == W) ++sx, sy=0;
    }
    if(sx == H) return true;

    for(int i=0; i<N; i++) {
        if(((1<<i) & tile) == 0) continue;
        // axb
        if(check(sx,sy,a[i],b[i])) {
            color(sx,sy,a[i],b[i],true);
            if(dfs(tile-(1<<i),sx,sy)) return true;
            color(sx,sy,a[i],b[i],false);
        }

        // bxa
        if(a[i] != b[i] && check(sx,sy,b[i],a[i])) {
            color(sx,sy,b[i],a[i],true);
            if(dfs(tile-(1<<i),sx,sy)) return true;
            color(sx,sy,b[i],a[i],false);
        }
    }

    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> H >> W;
    for(int i=0; i<N; i++)
        cin >> a[i] >> b[i];
    memset(c, 0, sizeof c);
    cout << (dfs((1<<N)-1, 0, 0) ? "Yes" : "No") << endl;

    return 0;
}
```