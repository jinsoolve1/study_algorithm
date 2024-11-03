## [atcoder 344-F : Earn to Advance](https://atcoder.jp/contests/abc344/tasks/abc344_f)

### 알고리즘
- dp

### 풀이
dp를 아래와 같이 정의하자.  
dp[x][y] := `(1,1) -> (x,y) 로 움직이고, 그 떄의 <최소 이동 횟수, 최대 남은 돈>`

그렇다면 dp[nx][ny]를 구하고 싶다면 어떻게 해야 할까? (1 <= x <= nx and 1 <= y <= ny)  
만약 (1,1) -> (x,y) -> (nx,ny) 이런 식으로 움직였다고 가정하자.  
이때 (x,y) -> (nx,ny) 이동할 때 (x,y)에서 필요한 모든 돈을 모아서 이동했다고 하자.  

그렇다면 dp[nx][ny]는 (1 <= x <= nx and 1 <= y <= ny) 위 범위를 만족하는 모든 (x,y)에 대해서 업데이트를 해주고,  
그 중에서 <최소 이동 횟수, 최대 남은 돈>을 저장할 수 있게 된다.  

시간복잡도는 (nx,ny)에 대해 가능한 모든 (x,y)를 탐색해야 하므로 $O(N^4)$이 된다. N = 80이므로 대충 4e7 정도에서 해결할 수 있다.


### 코드
코드에서 dp를 저장할 때 <이동, -돈> 이런 식으로 저장해서 min() 함수를 바로 사용할 수 있도록 구현했다.

반복문 dp는 for문의 순서를 항상 유의해야 하는데,  
dp[nx][ny]를 구하기 위해 사용하는 dp값들은 모두 이전에 구해놓은 값들임을 항상 유의해야 한다.  

여기서는 (nx,ny)의 왼쪽 위 부분들은 모두 구하도록 해야 하므로 아래 코드와 같이 반복문 순서가 정해진다.  
즉, dp[x][y]는 구해놓은 상태이고 (x,y)에 대해서 갈 수 있는 모든 (nx,ny)에 값들을 (x,y)의 값을 이용해서 업데이트해 주면 된다.

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

#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

const int mxn = 81;
const ll INF = numeric_limits<ll>::max();
int N;
ll P[mxn][mxn], R[mxn][mxn], D[mxn][mxn];

pll dp[mxn][mxn]; // dp[x][y] := (1,1) -> (x,y) 일 때의 <최소 횟수, 최대 비용>
ll cost[mxn][mxn];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++)
        for(int j=1; j<=N; j++)
            cin >> P[i][j];
    for(int i=1; i<=N; i++)
        for(int j=1; j<=N-1; j++)
            cin >> R[i][j];
    for(int i=1; i<=N-1; i++)
        for(int j=1; j<=N; j++)
            cin >> D[i][j];

    for(int i=1; i<=N; i++)
        for(int j=1; j<=N; j++)
            dp[i][j] = {INF, INF};

    dp[1][1] = {0,0};
    for(int x=1; x<=N; x++) {
        for(int y=1; y<=N; y++) {
            auto &[turn, money] = dp[x][y];
            money *= -1;
            cost[x][y] = 0;
            for(int nx=x; nx<=N; nx++) {
                for(int ny=y; ny<=N; ny++) {
                    if(x==nx && y==ny) continue;
                    // (x,y) -> (nx,ny), P[x][y]를 이용해서 돈을 벌 때에 대해 계산
                    cost[nx][ny] = INF;
                    if(x < nx) cost[nx][ny] = min(cost[nx][ny], cost[nx-1][ny] + D[nx-1][ny]);
                    if(y < ny) cost[nx][ny] = min(cost[nx][ny], cost[nx][ny-1] + R[nx][ny-1]);

                    if(money >= cost[nx][ny])
                        dp[nx][ny] = min(dp[nx][ny], {turn, -(money - cost[nx][ny])});
                    else {
                        auto add = (cost[nx][ny] - money + P[x][y]-1) / P[x][y];
                        dp[nx][ny] = min(dp[nx][ny], {turn+add, -(money + add*P[x][y] - cost[nx][ny])});
                    }
                }
            }
        }
    }

    cout << dp[N][N].first + 2*N - 2 << endl;

    return 0;
}
```