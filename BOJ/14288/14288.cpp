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

struct lazy {
    ll sum, lazy;
};

class LazySegment {
public:
    vector<lazy> tree; //tree[node] := a[start ~ end] 의 합

    LazySegment() {}
    LazySegment(int size) {
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
        tree.resize(size);
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

int n, m;
vector<vector<int>> g;
vector<int> in, out;
int _idx=0;

void dfs(int u) {
    in[u] = ++_idx;
    for(int v : g[u]) dfs(v);
    out[u] = _idx;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    g = vector<vector<int>>(n+1);
    in = vector<int>(n+1);
    out = vector<int>(n+1);

    for(int v=1; v<=n; v++) {
        int u; cin >> u;
        if(u != -1) g[u].emplace_back(v);
    }
    dfs(1);

    LazySegment lazy_seg(n); // 상사 -> 부하
    segment seg(n); // 부하 -> 상사

    bool dir = true;
    while(m--) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            int i, w; cin >> i >> w;
            if(dir) lazy_seg.update(1,1,n,in[i],out[i],w);
            else seg.update(1,1,n,in[i],w);
        }
        else if(cmd == 2) {
            int i; cin >> i;
            cout << lazy_seg.sum(1,1,n,in[i]) + seg.sum(1,1,n,in[i],out[i]) << endl;
        }
        else dir = !dir;
    }

    return 0;
}