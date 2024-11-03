## [백준 15967 - 에바쿰](https://www.acmicpc.net/problem/15967)

### 알고리즘
- 느리게 갱신되는 세그먼트 트리 (lazy segment tree)

### 풀이
문제 설명이 조금 난해(?)하지만 결국 구간변경과 구간쿼리가 요구되는 문제임을 알 수 있다.  
따라서 lazy segment tree를 사용하여 해결한다.

- lazy를 update시킬 때 구간합이므로 lazy 값 x (end-start+1) 을 더해주면 해결된다.

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
        tree[node].sum += tree[node].lazy*(end-start+1);
        if(start != end) {
            tree[2*node].lazy += tree[node].lazy;
            tree[2*node+1].lazy += tree[node].lazy;
        }
        tree[node].lazy = 0;
    }
    ll sum(int node, int start, int end, int left, int right) {
        update_lazy(node, start, end);
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node].sum;
        return sum(node * 2, start, (start + end) / 2, left, right) +
               sum(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q1, Q2; cin >> N >> Q1 >> Q2;
    vector<ll> a; a.resize(N+1);
    for(int i=1; i<=N; i++) cin >> a[i];
    segment tree(N); tree.init(a,1,1,N);
    while(Q1+Q2) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            Q2--;
            int n, m; cin >> n >> m;
            cout << tree.sum(1,1,N,n,m) << '\n';
        }
        else {
            Q1--;
            int s, e, l; cin >> s >> e >> l;
            tree.update(1,1,N,s,e,l);
        }
    }

    return 0;
}
```