## [백준 18227 - 성대나라의 물탱크](https://www.acmicpc.net/problem/18227)

### 알고리즘
- 오일러 경로 테크닉
- 세그먼트 트리

### 풀이
1. C를 루트로 하는 트리를 만든다.
2. 오일러 경로 테크닉을 이용해서 각 노드의 in과 out의 값을 구한다.
3. 도시 A의 물을 채운다면 세그먼트 트리의 in[A] 인덱스를 1 증가시킨다.
4. 도시 A의 물의 양을 물어보면, in[A] ~ out[A]의 합을 구한다.  
   즉, 도시 A를 루트로 하는 서브트리 노드들의 합을 구하는 것이다.  
   구한 값에 도시 A의 depth를 곱하면 정답이다.

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

const int mxn = 2e5+1;

class segment {
public:
    vector<ll> tree; //tree[node] := a[start ~ end] 의 합

    segment() {}
    segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size, 0);
    }
    ll init(vector<ll> &a, int node, int start, int end) {
        if(start == end) return tree[node] = a[start];
        else return tree[node] = init(a, 2 * node, start, (start + end) / 2) +
                                 init(a, 2 * node + 1, (start + end) / 2 + 1, end);
    }
    ll sum(int node, int start, int end, int left, int right) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node];
        return sum(node * 2, start, (start + end) / 2, left, right) +
               sum(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
    }
    void update(int node, int start, int end, int index, ll diff) {
        if(index < start || end < index) return;
        tree[node] += diff;
        if(start != end) {
            update(node * 2, start, (start + end) / 2, index, diff);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, diff);
        }
    }
};

vector<int> g[mxn];
int N, C, Q;
int depth[mxn];
int in[mxn], out[mxn];
int _idx=1;

void dfs(int u, int lv) {
    depth[u] = lv;
    in[u] = _idx++;
    for(int v : g[u])
        if(depth[v] == 0) dfs(v, lv+1);
    out[u] = _idx-1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(depth, 0, sizeof depth);
    cin >> N >> C;
    for(int i=0; i<N-1; i++) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    dfs(C,1);
    segment root(N);
    cin >> Q;
    while(Q--) {
        int cmd, A; cin >> cmd >> A;
        if(cmd == 1) root.update(1,1,N,in[A],1);
        else cout << root.sum(1,1,N,in[A],out[A]) * depth[A] << endl;
    }

    return 0;
}
```