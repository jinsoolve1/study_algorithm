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

const int mxn = 1e5+1;
int n, m;
int parent[mxn], in[mxn], out[mxn];
int idx = 1;
vector<int> g[mxn];

void dfs(int u) {
    in[u] = idx++;
    for(int v : g[u]) dfs(v);
    out[u] = idx-1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        cin >> parent[i];
        if(parent[i] != -1) g[parent[i]].emplace_back(i);
    }
    dfs(1);

    segment tree(n);
    while(m--) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            int i, w; cin >> i >> w;
            tree.update(1,1,n,in[i],w);
        }
        else {
            int i; cin >> i;
            cout << tree.sum(1,1,n,in[i],out[i]) << endl;
        }
    }
    return 0;
}