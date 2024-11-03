## [백준 13896 - Sky Tax](https://www.acmicpc.net/problem/13896)

### 알고리즘
- 최소 공통 조상(LCA)
- 트리

### 풀이
1. 도시 1을 기준으로 tree를 만들고 parent를 연결한다.
2. 현재 수도를 R, 임의 도시를 U라고 하자.  
   1. R == U이면, N을 출력한다.
   2. U의 서브트리 안에 R이 있을때, U의 직속 자식들 중 R의 조상에 해당되는 노드를 V라 하자.  
      N - treeSize[V]를 출력한다.
   3. U의 서브트리 안에 R이 없을때, treeSize[U]를 출력한다.
3. 서브트리 안에 있는지 없는지 여부는 LCA 알고리즘으로 해결한다.  
   LCA(R,U) == U이면, U의 서브트리 안에 R이 있는 것이다.

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

const int mxn = 1e5+1, LOG_MXN = 19;
int N, Q, R;
int depth[mxn], treeSize[mxn];
int parent[mxn][LOG_MXN+1];
vector<vector<int>> g;

int makeTree(int here, int level) {
    depth[here] = level;
    treeSize[here] = 1;
    for(int there : g[here]) {
        if(depth[there] != -1) continue;
        parent[there][0] = here;
        treeSize[here] += makeTree(there, level+1);
    }
    return treeSize[here];
}
void linkAncestor() {
    for(int i=1; i<=LOG_MXN; i++) {
        for(int here=1; here<=N; here++) {
            parent[here][i] = parent[parent[here][i-1]][i-1];
        }
    }
}
int LCA(int a, int b) {
    if(depth[a] > depth[b]) swap(a,b);

    for(int i=LOG_MXN; i>=0; i--) {
        if(depth[parent[b][i]] < depth[a]) continue;
        b = parent[b][i];
    }
    if(a == b) return a;

    for(int i=LOG_MXN; i>=0; i--) {
        if(parent[a][i] == parent[b][i]) continue;
        a = parent[a][i], b = parent[b][i];
    }
    return parent[a][0];
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    for(int tc=1; tc<=T; tc++) {
        memset(depth, -1, sizeof depth);

        cin >> N >> Q >> R;
        g = vector<vector<int>>(N+1);
        for(int i=0; i<N-1; i++) {
            int u, v; cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        makeTree(1,1);
        linkAncestor();

        cout << "Case #" << tc << ":\n";
        while(Q--) {
            int S, U; cin >> S >> U;
            if(S == 0) R = U;
            else {
                if(R == U) cout << N << endl;
                else if(LCA(R,U) == U) {
                    int here = R;
                    for(int i=LOG_MXN; i>=0; i--) {
                        if(depth[parent[here][i]] < depth[U]+1) continue;
                        here = parent[here][i];
                    }
                    cout << N - treeSize[here] << endl;
                }
                else {
                    cout << treeSize[U] << endl;
                }
            }
        }
    }

    return 0;
}
```