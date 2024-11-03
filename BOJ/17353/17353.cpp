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
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

struct lazy {
    ll sum, sv, d;
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
        tree.resize(size, {0,0,0});
    }
    ll init(vector<ll> &a, int node, int start, int end) {
        if(start == end) return tree[node].sum = a[start];
        return tree[node].sum = init(a, 2*node, start, (start+end)/2) + init(a, 2*node+1, (start+end)/2+1, end);
    }
    void update_lazy(int node, int start, int end) {
        if(tree[node].d == 0) return;
        tree[node].sum += tree[node].sv * (end-start+1) + tree[node].d * (end-start) * (end-start+1) / 2;
        if(start != end) {
            tree[2*node].sv += tree[node].sv; tree[2*node].d += tree[node].d;
            tree[2*node+1].sv += tree[node].sv + ((start+end)/2+1 - start) * tree[node].d; tree[2*node+1].d += tree[node].d;
        }
        tree[node].sv = tree[node].d = 0;
    }
    ll sum(int node, int start, int end, int idx) {
        update_lazy(node, start, end);
        if(idx < start || end < idx) return 0;
        if(start == end) return tree[node].sum;
        return sum(node * 2, start, (start + end) / 2, idx) +
               sum(node * 2 + 1, (start + end) / 2 + 1, end, idx);
    }
    void update(int node, int start, int end, int left, int right) {
        update_lazy(node, start, end);
        if(right < start || end < left) return;
        if(left <= start && end <= right) {
            tree[node].sv += max(start, left) - left + 1;
            tree[node].d++;
            update_lazy(node, start, end);
            return;
        }
        update(node * 2, start, (start + end) / 2, left, right);
        update(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
        tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
    }
};

int N, Q;
vector<ll> v;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    v.resize(N+1);
    for(int i=1; i<=N; i++) cin >> v[i];
    segment root(N);
    root.init(v, 1,1,N);

    cin >> Q;
    while(Q--) {
        int q; cin >> q;
        if(q == 1) {
            int l, r; cin >> l >> r;
            root.update(1,1,N,l,r);
        }
        else {
            int x; cin >> x;
            cout << root.sum(1,1,N,x) << '\n';
        }
    }



    return 0;
}