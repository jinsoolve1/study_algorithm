## [백준 3295 - 단방향 링크 네트워크](https://www.acmicpc.net/problem/3295)

### 알고리즘
- 이분매칭

### 풀이
문제를 잘 이해해보면, 네트워크의 최대 가치는 결국 '노드가 중복되지 않으면서 선택된 간선의 개수'와 같다.    
이는 이분매칭으로 해결할 수 있다.  
왼쪽 집합에 0 ~ n-1, 오른쪽 집합에 0 ~ n-1 노드들을 넣어놓고 문제에서 주어진 그래프가 주어졌을 때, 가장 많은 매칭의 결과가 결국 네트워크의 최대 가치가 된다.

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

const int mxn = 1e3;
int n, m;
vector<vector<int>> g;
bool capacity[mxn];
int parent[mxn];

bool dfs(int here) {
    // 연결된 모든 노드에 대해서 들어갈 수 있는지 시도
    for(int there : g[here]) {
        // 이미 처리한 노드는 더 이상 볼 필요가 없음
        if(capacity[there]) continue;
        capacity[there] = true;
        if(parent[there] == -1 || dfs(parent[there])) {
            parent[there] = here;
            return true;
        }
    }
    return false;
}
int bipartite() {
    memset(parent, -1, sizeof parent);
    int ret = 0;
    for(int i=0; i<n; i++) {
        memset(capacity, 0, sizeof capacity);
        ret += dfs(i);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        cin >> n >> m;
        g = vector<vector<int>>(n);
        while(m--) {
            int u, v; cin >> u >> v;
            g[u].emplace_back(v);
        }
        cout << bipartite() << '\n';
    }


    return 0;
}
```