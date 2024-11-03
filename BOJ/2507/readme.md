## [백준 2507 - 공주 구하기](https://www.acmicpc.net/problem/2507)

### 알고리즘
- 다이나믹 프로그래밍
- 바이토닉 투어(bitonic tour)

### 풀이
바이토닉 투어란, "시작점에서부터 끝점을 방문하고 다시 시작점을 방문하는데, 시작점을 제외하고 모두 한 번만 방문하는 싸이클"이다.  
시작점에서 도착점까지 처음부터 2개의 경로를 관리하며 도착점에 둘 다 도달시키면 해결가능하다.

1. adj[i][j] := i->j 이동이 가능한지 여부
2. dp[a][b] := 갈 때 a번 정점을, 올 때 b번 정점을 밟을 때의 경로의 개수  
   u = max(a,b)+1 ~ N 까지 탐색하며,  
   1. 가는 길에 u를 추가하자  
      adj[a][u]가 true라면, solve(u,b)를 더한다.
   2. 오는 길에 u를 추가하자  
      adj[u][b]가 true이고 carry[u]가 true이면, solve(a,u)를 더한다.

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

const int mod = 1e3, mxn = 501;
int N;
int loc[mxn], spring[mxn];
bool carry[mxn], adj[mxn][mxn];;
int dp[mxn][mxn];

int solve(int org, int dst) {
    int &ret = dp[org][dst];
    if(ret != -1) return ret;
    ret = adj[org][N] && adj[N][dst];
    for(int u = max(org,dst)+1; u <= N; u++) {
        if(adj[org][u]) ret = (ret + solve(u,dst)) % mod;
        if(adj[u][dst] && carry[u]) ret = (ret + solve(org,u)) % mod;
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);
    memset(adj, 0, sizeof adj);
    cin >> N;
    for(int i=1; i<=N; i++) cin >> loc[i] >> spring[i] >> carry[i];
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            if(i == j) continue;
            if(abs(loc[i]-loc[j]) <= spring[i]) adj[i][j] = true;
        }
    }
    cout << solve(1,1) << endl;

    return 0;
}
```

### 침고
https://jason9319.tistory.com/291