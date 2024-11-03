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

const ll mod = 1e9+7;
struct lazy {
    ll val, a, b; // a * val + b
};

class Lazy_Segment {
public:
    vector<lazy> tree; //tree[node] := a[start ~ end] 의 합

    Lazy_Segment() {}
    Lazy_Segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size, {0,1, 0});
    }
    ll init(vector<ll> &a, int node, int start, int end) {
        if(start == end) return tree[node].val = a[start];
        return tree[node].val = (init(a, 2*node, start, (start+end)/2) + init(a, 2*node+1, (start+end)/2+1, end)) % mod;
    }
    void update_lazy(int node, int start, int end) {
        if(tree[node].a == 1 && tree[node].b == 0) return;
        tree[node].val = (tree[node].a*tree[node].val + tree[node].b*(end-start+1)) % mod;
        if(start != end) {
            for(auto i : {2*node, 2*node+1}) {
                tree[i].a = (tree[i].a * tree[node].a) % mod;
                tree[i].b = (tree[node].a*tree[i].b + tree[node].b) % mod;
            }
        }
        tree[node].a = 1, tree[node].b = 0;
    }
    ll sum(int node, int start, int end, int left, int right) {
        update_lazy(node, start, end);
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node].val;
        return (sum(node * 2, start, (start + end) / 2, left, right) +
                sum(node * 2 + 1, (start + end) / 2 + 1, end, left, right)) % mod;
    }
    void update(int node, int start, int end, int left, int right, ll a, ll b) {
        update_lazy(node, start, end);
        if(right < start || end < left) return;
        if(left <= start && end <= right) {
            tree[node].a = (tree[node].a * a) % mod;
            tree[node].b = (tree[node].b + b) % mod;
            update_lazy(node, start, end);
            return;
        }
        update(node * 2, start, (start + end) / 2, left, right, a, b);
        update(node * 2 + 1, (start + end) / 2 + 1, end, left, right, a, b);
        tree[node].val = (tree[2*node].val + tree[2*node+1].val) % mod;
    }
};
int N, M;
vector<ll> A;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N; A = vector<ll>(N+1);
    for(int i=1; i<=N; i++) cin >> A[i];

    Lazy_Segment tree(N);
    tree.init(A,1,1,N);

    cin >> M;
    while(M--) {
        int cmd, x, y; cin >> cmd >> x >> y;
        if(cmd != 4) {
            int v; cin >> v;
            if(cmd == 1) tree.update(1,1,N,x,y,1,v);
            else if(cmd == 2) tree.update(1,1,N,x,y,v,0);
            else tree.update(1,1,N,x,y,0,v);
        }
        else cout << tree.sum(1,1,N,x,y) << endl;
    }

    return 0;
}