## [백준 2934 - LRH 식물](https://www.acmicpc.net/problem/2934)

### 알고리즘
- lazy segment tree

### 풀이
1. l과 r의 식물이 주어지면, 세그먼트 트리에 l+1 ~ r-1 인덱스의 값을 1씩 높여준다.
2. 인덱스가 l과 r인 지점의 합이 얼마인지 출력하고 해당 값은 이미 꽃이 피었으므로 지워준다.

구간합과 구간변경이 필요하므로 lazy segment tree를 사용하여 해결할 수 있다.

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

const int mxn = 1e5;
ll N;


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    segment root(mxn);
    for(ll h=1; h<=N; h++) {
        int l, r; cin >> l >> r;
        ll L = root.sum(1,1,mxn,l), R = root.sum(1,1,mxn,r);
        cout << L + R << '\n';
        root.update(1,1,mxn,l,l,-L); root.update(1,1,mxn,r,r,-R);
        if(l+1 <= r-1) root.update(1,1,mxn, l+1, r-1, 1);
    }

    return 0;
}
```