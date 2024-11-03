## [백준 14268 - 회사 문화 2](https://www.acmicpc.net/problem/14268)

### 알고리즘
- 오일러 경로 테크닉
- 느리게 갱신되는 세그먼트 트리 (lazy segment tree)

### 풀이
직장 관계도는 트리 모양이다.   
여기서 구간 변경이 쿼리로 들어오므로 오일러 경로 테크닉으로 노드에 번호를 매기고 lazy segment tree로 쿼리르를 처리한다.

- idx[x] := x번 노드(직원)가 오일러 경로 테크닉으로는 몇 번 째인지를 저장
- nxt[x] := x번 노드(직원)의 자식 노드(부하 직원)들 중 가장 큰 idx를 저장  

1 i w가 쿼리로 들어오면 idx[x] ~ nxt[x] 의 노드들에 대해서 구간 변경을 하면 된다.

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

struct lazy {
        ll sum, lazy;
};

class segment {
public:
    vector<lazy> tree; //tree[node] := a[start ~ end] 의 합

    segment() {}
    segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size, {0,0});
    }
    ll init(vector<ll> &a, int node, int start, int end) {
        if(start == end) return tree[node].sum = a[start];
        return tree[node].sum = init(a, 2*node, start, (start+end)/2) + init(a, 2*node+1, (start+end)/2+1, end);
    }
    void update_lazy(int node, int start, int end) {
        if(tree[node].lazy == 0) return;
        tree[node].sum += tree[node].lazy;
        if(start != end) {
            tree[2*node].lazy += tree[node].lazy;
            tree[2*node+1].lazy += tree[node].lazy;
        }
        tree[node].lazy = 0;
    }
    ll sum(int node, int start, int end, int idx) {
        update_lazy(node, start, end);
        if(idx < start || end < idx) return 0;
        if(start == end) return tree[node].sum;
        return sum(node * 2, start, (start + end) / 2, idx) +
               sum(node * 2 + 1, (start + end) / 2 + 1, end, idx);
    }
    void update(int node, int start, int end, int left, int right, ll value) {
        update_lazy(node, start, end);
        if(right < start || end < left) return;
        if(left <= start && end <= right) {
            tree[node].lazy += value;
            update_lazy(node, start, end);
            return;
        }
        update(node * 2, start, (start + end) / 2, left, right, value);
        update(node * 2 + 1, (start + end) / 2 + 1, end, left, right, value);
        tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
    }
};

const int mxn = 1e5+1;
int n, m;
int _idx = 1, root;
int idx[mxn], nxt[mxn];
vector<int> g[mxn];

void dfs(int here) {
    idx[here] = _idx++;
    for(int there : g[here]) dfs(there);
    nxt[here] = _idx-1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for(int v=1; v<=n; v++) {
        int u; cin >> u;
        if(u == -1) root = v;
        else g[u].emplace_back(v);
    }
    dfs(root);

    segment tree(n);
    while(m--) {
        int q, i, w; cin >> q;
        if(q == 1) {
            cin >> i >> w;
            tree.update(1,1,n,idx[i],nxt[i],w);
        }
        else {
            cin >> i;
            cout << tree.sum(1,1,n,idx[i]) << '\n';
        }
    }

    return 0;
}
```