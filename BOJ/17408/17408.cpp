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

class segment {
public:
    vector<pll> tree; //tree[node] := a[start ~ end] 의 합

    segment() {}
    segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size);
    }
    pll init(vector<ll> &a, int node, int start, int end) {
        if(start == end) return tree[node] = {a[start], start};
        else return tree[node] = max(init(a, 2 * node, start, (start + end) / 2),
                                     init(a, 2 * node + 1, (start + end) / 2 + 1, end));
    }
    pll query(int node, int start, int end, int left, int right) {
        if(left > right) return {0,0};
        if(right < start || end < left) return {0,0};
        if(left <= start && end <= right) return tree[node];
        return max(query(node * 2, start, (start + end) / 2, left, right),
                   query(node * 2 + 1, (start + end) / 2 + 1, end, left, right));
    }
    void update(int node, int start, int end, int index, ll value) {
        if(index < start || end < index) return;
        if(start == end) tree[node].first = value;
        else {
            update(node * 2, start, (start + end) / 2, index, value);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, value);
            tree[node] = max(tree[2*node], tree[2*node+1]);
        }
    }
};


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<ll> a; a.resize(N+1);
    for(int i=1; i<=N; i++) cin >> a[i];
    segment tree(N); tree.init(a,1,1,N);
    int M; cin >> M;
    while(M--) {
        int q; cin >> q;
        if(q == 1) {
            int i, v; cin >> i >> v;
            tree.update(1,1,N,i,v);
        }
        else {
            int l, r; cin >> l >> r;
            pii res1 = tree.query(1,1,N,l,r);
            pii res2 = max(tree.query(1,1,N,l,res1.second-1), tree.query(1,1,N,res1.second+1,r));
            cout << res1.first + res2.first << '\n';
        }
    }


    return 0;
}