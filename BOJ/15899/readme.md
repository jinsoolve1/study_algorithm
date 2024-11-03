## [백준 15899 - 트리와 색깔](https://www.acmicpc.net/problem/15899)

### 알고리즘
- 오일러 경로 테크닉
- 머지소트 트리

### 풀이
1. 오일러 경로 테크닉으로 해당 노드의 in과 out값을 찾는다.   
   in은 dfs탐색을하면서 처음 방문하는 순서이고,  
   out은 해당 노드를 루트로하는 서브트리의 자식노드들 중 가장 마지막 방문 순서를 저장한다.
2. 오일러 경로 순서를 기준으로 색상을 저장하여 자료구조를 구성한다.
3. f(v,c) = merge tree에서 in[v] ~ out[v] 구간에서 c이하인 정점의 개수를 이분탐색으로 찾아서 반환하면 된다.

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

const int mxn = 2e5+1, mod = 1e9+7;

class mergeTree {
public:
    vector<vector<ll>> tree; //tree[node] := a[start ~ end] 의 합

    mergeTree() {}
    mergeTree(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size);
    }

    void update(int node, int start, int end, int index, ll value) {
        if(index < start || end < index) return;
        tree[node].emplace_back(value);
        if(start != end) {
            update(node * 2, start, (start + end) / 2, index, value);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, value);
        }
    }
    ll query(int node, int start, int end, int left, int right, ll value) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return upper_bound(all(tree[node]), value) - tree[node].begin();
        return query(node * 2, start, (start + end) / 2, left, right, value) +
               query(node * 2 + 1, (start + end) / 2 + 1, end, left, right, value);
    }
};

int N, M, C;
int color[mxn], in[mxn], out[mxn];
vector<int> g[mxn];
int _idx = 1;

void dfs(int u) {
    in[u] = _idx++;
    for(int v : g[u])
        if(in[v] == 0) dfs(v);
    out[u] = _idx-1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(in, 0, sizeof in);

    cin >> N >> M >> C;
    for(int i=1; i<=N; i++) cin >> color[i];
    for(int i=0; i<N-1; i++) {
        int u, v; cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1);
    vector<pii> vec;
    for(int i=1; i<=N; i++) vec.emplace_back(color[i], in[i]);
    sort(all(vec));
    mergeTree tree(N);
    for(pii x : vec) tree.update(1,1,N,x.second,x.first);

    ll ans = 0;
    while(M--) {
        int v, c; cin >> v >> c;
        ans = (ans + tree.query(1,1,N,in[v],out[v],c)) % mod;
    }
    cout << ans << endl;

    return 0;
}
```