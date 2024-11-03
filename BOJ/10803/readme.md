## [백준 10803 - 정사각형 만들기](https://www.acmicpc.net/problem/10803)

### 알고리즘
- (최적화된) 다이나믹 프로그래밍
- 그리디 알고리즘

### 풀이
f(n,m) := (nxm 직사각형을 채우는 정사각형의 최소 개수) 라 하자.  
원래라면 i = 1 ~ n/2 동안 f(i,m) + f(n-i, m)과, j = 1 ~ m/2 동안 f(n,j) + f(n,m-j)를 해봐야 한다.  
그러나 이는 $10^{10}$으로 시간초과가 나온다. 

이를 최적화시킨 것이 n >= 3m 이라면 f(n,m) = f(n,n-m) + 1 을 이용하는 것이다.  
(이 부분의 정확한 이유는 모르겠다. 테크닉 정도로 알고 있자. n>=2m은 불가능했으므로 해당 식이 가장 최적화된 식인 듯 하다.)  
위 최적화 공식을 이용해서 문제를 푼다.

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

int dp[10001][101];
int solve(int n, int m) {
    if(n%m == 0) return n/m;
    if(n == m) return 1;

    int &ret = dp[n][m];
    if(ret != -1) return ret;

    ret = n*m;
    if(n >= 3*m) return ret = min(ret, solve(n-m,m) + 1);
    for(int i=1; i<=n/2; i++) ret = min(ret, solve(n-i, m) + solve(i,m));
    for(int j=1; j<=m/2; j++) ret = min(ret, solve(n, m-j) + solve(n,j));
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);
    int n, m; cin >> n >> m;
    cout << solve(n,m) << '\n';

    return 0;
}
```

### 후기
n >= 3m은 정확한 증명을 모르겠으나, 3n >= m^2 일 떄의 f(n,m) = f(n-m,m) + 1을 증명한 블로그가 있어서 링크를 첨부해두겠다.  
https://ilikechicken.tistory.com/52