## [백준 15480 - LCA와 쿼리](https://www.acmicpc.net/problem/15480)

### 풀이
1. 1번 정점을 루트로 사용해서 트리를 만든다.
2. r-u, r-V, u-v의 LCA 중에서 가장 deepest한 LCA가 정답이다.

2번이 성립하는 이유는  
1이 루트인 트리를 그렸을 때,  
r에서 출발해서 u와 v로 가는 중에 만나는 노드 중 u, v에 가장 가까운 노드가 LCA가 되기 때문이다.

좀 더 자세히 설명하자면,  
LCA of u-v가 가장 깊은 경우 r에서 출발해서 결국 해당 노드에서 갈라지기 때문이다.  
나머지의 경우 u-v가 아무리 먼저 만나더라도 r에서 출발한 것이 아니면 의미가 없기 때문에 r까지 거슬럭 가야 한다.  
이 경우들은 LCA of r-u, r-V 중 깊은 LCA가 답이 된다.

```C++
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
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

const int N_MXN = 1e5;
const int LOG_MXN = 20;
int N, M;
vector<int> g[N_MXN+1];
int depth[N_MXN+1];
int Prev[N_MXN+1][LOG_MXN+1];

void makeTree(int here, int level) {
    depth[here] = level;
    for(int there : g[here]) {
        if(depth[there] != -1) continue;
        Prev[there][0] = here;
        makeTree(there, level+1);
    }
}
void linkAncestor() {
    for(int i=1; i<=LOG_MXN; i++) {
        for(int here=1; here<=N; here++) {
            Prev[here][i] = Prev[Prev[here][i-1]][i-1];
        }
    }
}
int LCA(int a, int b) {
    if(depth[a] > depth[b]) swap(a,b);

    for(int i=LOG_MXN; i>=0; i--) {
        if(depth[Prev[b][i]] < depth[a]) continue;
        b = Prev[b][i];
    }
    if(a == b) return a;

    for(int i=LOG_MXN; i>=0; i--) {
        if(Prev[a][i] == Prev[b][i]) continue;
        a = Prev[a][i], b = Prev[b][i];
    }
    return Prev[a][0];
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(depth, -1, sizeof depth);

    cin >> N;
    for(int i=0; i<N-1; i++) {
        int u, V; cin >> u >> V;
        g[u].emplace_back(V);
        g[V].emplace_back(u);
    }

    // make tree by root 1
    Prev[1][0] = 1;
    makeTree(1,0);
    linkAncestor();

    cin >> M;
    while(M--) {
        int r, u, V; cin >> r >> u >> V;

        // LCA1: LCA of r-u, LCA2: LCA of r-V, LCA3: LCA of u-V
        // find deepest LCA in 3 of them
        int LCA1 = LCA(r,u), LCA2 = LCA(r,V), LCA3 = LCA(u,V);

        int ans = LCA1;
        if(depth[ans] < depth[LCA2]) ans = LCA2;
        if(depth[ans] < depth[LCA3]) ans = LCA3;
        cout << ans << '\n';
    }


    return 0;
}
```