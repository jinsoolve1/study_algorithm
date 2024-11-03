## [백준 2820 - 자동차 공장](https://www.acmicpc.net/problem/2820)

### 알고리즘
- lazy segment tree
- 오일러 경로 테크닉

### 풀이
p a x 쿼리는 생각해보면 구간 변경이라 할 수 있다.  
구간 변경이 필요한 온라인 쿼리이니 lazy segment tree를 사용해야 한다는 생각이 들었다.  

하지만 배열이 아닌 트리이므로 이를 오일러 경로 테크닉(즉, dfs를 해서 방문하는 노드의 순서대로 노드의 번호를 매기는 것)을 이용하여 노드의 번호 idx를 매겨준다.  
위 테크닉을 사용하면 자신의 자식 노드들은 연속적인 수가 된다. 또한 idx번 노드의 자식 노드들 중 가장 큰 번호의 값 nxt를 저장한다.  
idx번 노드의 부하들의 월급을 변경한다면, idx+1 ~ nxt 까지의 구간변경을 수행하면 모든 부하들의 월급을 변경시킬 수 있다.

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
const int mxn = 5e5 + 1;
int N, M;
int val[mxn], idx[mxn], nxt[mxn];
vector<int> g[mxn];
int _idx = 1;
void dfs(int here) {
    idx[here] = _idx++;
    for(int there : g[here])
        dfs(there);
    nxt[here] = _idx-1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    cin >> val[1];
    for(int i=2; i<=N; i++) {
        int parent;
        cin >> val[i] >> parent;
        g[parent].emplace_back(i);
    }
    dfs(1);
    segment root(N);
    vector<ll> v; v.resize(N+1);
    for(int i=1; i<=N; i++) v[idx[i]] = val[i];
    root.init(v, 1, 1, N);

    while(M--) {
        char cmd; cin >> cmd;
        if(cmd == 'p') {
            int a, x; cin >> a >> x;
            root.update(1,1,N,idx[a]+1,nxt[a],x);
        }
        else {
            int a; cin >> a;
            cout << root.sum(1,1,N,idx[a]) << '\n';
        }
    }

    return 0;
}
```