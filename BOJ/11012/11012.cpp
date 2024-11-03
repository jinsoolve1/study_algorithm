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

class mergeTree {
public:
    vector<vector<int>> tree; //tree[node] := a[start ~ end] 의 합
    int sz;

    mergeTree() {}
    mergeTree(int size) {
        this->resize(size);
    }
    void resize(int size) {
        sz = (int) floor(log2(size)) + 2;
        sz = pow(2, sz);
        tree.resize(sz);
    }
    void clear() {
        for(int i=0; i<sz; i++) tree[i].clear();
    }

    void update(int node, int start, int end, int index, int value) {
        if(index < start || end < index) return;
        tree[node].emplace_back(value);
        if(start != end) {
            update(node * 2, start, (start + end) / 2, index, value);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, value);
        }
    }
    ll query(int node, int start, int end, int left, int right, int lv, int rv) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return upper_bound(all(tree[node]), rv) - lower_bound(all(tree[node]), lv);
        return query(node * 2, start, (start + end) / 2, left, right, lv, rv) +
               query(node * 2 + 1, (start + end) / 2 + 1, end, left, right, lv, rv);
    }
};

const int mxn = 1e5;
int n, m;
ll ans;
vector<pii> folks;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    mergeTree root(mxn+1);
    int T; cin >> T;
    while(T--) {
        cin >> n >> m;
        folks.resize(n);
        for(int i=0; i<n; i++) cin >> folks[i].first >> folks[i].second;
        auto cmp = [&](pii a, pii b) { return a.second < b.second; };
        sort(all(folks), cmp);
        for(pii folk : folks) root.update(1,0,mxn,folk.first,folk.second);

        ans = 0;
        while(m--) {
            int l, r, b, t; cin >> l >> r >> b >> t;
            ans += root.query(1,0,mxn,l,r,b,t);
        }
        cout << ans << '\n';
        root.clear();
    }


    return 0;
}