## [백준 25948 - Islands Tour](https://www.acmicpc.net/problem/25948)

### 알고리즘
- dfs
- 스택
- dp

### 풀이
1. dfs 탐색을 하면서 cycle을 찾으면 idx[x] = (x가 포함된 cycle 중 첫번째로 방문한 노드번호) 를 저장한다.
2. dp[x] := (x에서 시작해서 갈 수 있는 노드 path 중 가장 긴 값) 를 저장한다.
3. 모든 노드의 outdegree <= 1 이므로, 모든 path는 path 안에 아예 사이클이 없거나, 맨 마지막에 사이클로 끝나는 경우 밖에 없다.
4. u -> v(사이클에 포함된 노드)일 때, dp[idx[v]]를 구했다면 v가 포함된 사이클의 크기가 되므로 해당 값을 더해주면 된다.
5. 모든 노드를 한번씩만 방문하면서 최대 방문 가능 노드수를 구한다.

### 후기
scc + topological sort 를 이용하면 O(V+E) 안에 해결 가능하다고 생각했는데, 이상하게 시간초과가 발생한다.  
아무래도 시간 제한이 생각보다 하드한듯 하다.  
dfs와 dp로 푸니까 솔브를 받을 수 있었다.


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

const int mxn = 1e6;

int m, n;
vector<int> g, dp, idx;
vector<bool> visited;
stack<int> st;

void init() {
    g = vector<int>(n, -1);
    dp = vector<int>(n, -1);
    idx = vector<int>(n);
    for(int i=0; i<n; i++) idx[i] = i;
    visited = vector<bool>(n, false);
}
int dfs(int u) {
    if(u == -1) return 0;
    int &ret = dp[idx[u]];
    if(ret != -1) return ret;
    if(visited[u]) {
        while(!st.empty() && st.top() != u) {
            idx[st.top()] = u;
            st.pop();
        }
        return 0;
    }
    visited[u] = true;
    st.emplace(u);
    return ret = dfs(g[u]) + 1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> m >> n;
    init();
    while(m--) {
        int u, v; cin >> u >> v;
        g[u] = v;
    }
    int ans = 0;
    for(int i=0; i<n; i++) {
        if(visited[i]) continue;
        while(!st.empty()) st.pop();
        ans = max(ans, dfs(i));
    }
    cout << ans << endl;

    return 0;
}
```