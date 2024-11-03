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
        tree.resize(size, {0,-1});
    }
    ll init(int node, int start, int end) {
        if(start == end) return tree[node].sum = 1;
        return tree[node].sum = init(2*node, start, (start+end)/2) + init(2*node+1, (start+end)/2+1, end);
    }
    void update_lazy(int node, int start, int end) {
        if(tree[node].lazy == -1) return;
        tree[node].sum = tree[node].lazy * (end-start+1);
        if(start != end) {
            tree[2*node].lazy = tree[node].lazy;
            tree[2*node+1].lazy = tree[node].lazy;
        }
        tree[node].lazy = -1;
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
            tree[node].lazy = value;
            update_lazy(node, start, end);
            return;
        }
        update(node * 2, start, (start + end) / 2, left, right, value);
        update(node * 2 + 1, (start + end) / 2 + 1, end, left, right, value);
        tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
    }
};

int N, M;

vector<int> in, out;
vector<vector<int>> g;
int _idx = 0;

void dfs(int u) {
    in[u] = ++_idx;
    for(int v : g[u]) dfs(v);
    out[u] = _idx;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    in = vector<int>(N+1); out = vector<int>(N+1);
    g = vector<vector<int>>(N+1);
    for(int v=1; v<=N; v++) {
        int u; cin >> u;
        if(u != 0) g[u].emplace_back(v);
    }
    dfs(1);

    segment root(N);
    root.init(1,1,N);

    cin >> M;
    while(M--) {
        int cmd, i; cin >> cmd >> i;
        if(cmd == 1) root.update(1, 1, N, in[i]+1, out[i], 1);
        else if(cmd == 2) root.update(1, 1, N, in[i]+1, out[i], 0);
        else cout << root.sum(1,1,N,in[i]+1, out[i]) << endl;
    }

    return 0;
}