## [백준 2673 - 교차하지 않는 원의 현들의 최대집합](https://www.acmicpc.net/problem/2673)

### 알고리즘
- dynamic programming

### 풀이
1. dp[s][e]: s~e의 점을 끝점으로 하면서 교차하지 않는 현들의 집합의 최대크기 라 하자.
2. dp[s][e] = max(dp[s][e], dp[s][k] + dp[k][e] + ln[s][e]) 가 된다.  
   ln[s][e]: s와 e를 끝점으로 하는 현의 존재여부

### 후기
반복문을 사용할 때 for문의 순서가 헷갈렸다.  
dp[s][k]와 dp[k][e]는 이미 계산된 값이어야 하므로, e를 먼저 정하고 -> s를 1과 e사이로 정하고 -> k를 s와 e사이로 정해야 한다.  
이때, k는 s ~ e-1혹은 s+1 ~ e이어야 한다.   
ln[s][e]를 최소한 한번은 해야 하므로 s+1 ~ e-1은 안된다.  
그렇다고 s ~ e가 되면 ln[s][e]값이 2번 적용되므로 안된다.

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
int dp[101][101];
bool ln[101][101];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, 0, sizeof dp);
    memset(ln, 0, sizeof ln);

    cin >> N;
    for(int i=0; i<N; i++) {
        int a, b; cin >> a >> b;
        ln[a][b] = ln[b][a] = true;
    }
    for(int e=1; e<=100; e++) {
        for(int s=e; s>=1; s--) {
            for(int k=s; k<e; k++) {
                dp[s][e] = max(dp[s][e], dp[s][k] + dp[k][e] + ln[s][e]);
            }
        }
    }
    cout << dp[1][100] << '\n';

    return 0;
}
```