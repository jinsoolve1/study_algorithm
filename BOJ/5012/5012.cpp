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

class mergeTree {
public:
    vector<vector<ll>> tree; //tree[node] := a[start ~ end] 의 합

    mergeTree() {}
    mergeTree(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size);
    }
    void update(int node, int start, int end, int index, ll value) {
        if(index < start || end < index) return;
        tree[node].emplace_back(value);
        if(start != end) {
            update(node * 2, start, (start + end) / 2, index, value);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, value);
        }
    }
    ll upper_query(int node, int start, int end, int left, int right, ll value) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node].end() - upper_bound(all(tree[node]), value);
        return upper_query(node * 2, start, (start + end) / 2, left, right, value) +
               upper_query(node * 2 + 1, (start + end) / 2 + 1, end, left, right, value);
    }
    ll lower_query(int node, int start, int end, int left, int right, ll value) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return lower_bound(all(tree[node]), value) - tree[node].begin();
        return lower_query(node * 2, start, (start + end) / 2, left, right, value) +
               lower_query(node * 2 + 1, (start + end) / 2 + 1, end, left, right, value);
    }
};


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    vector<ll> a(n+1);
    vector<pll> v;
    for(int i=1; i<=n; i++) {
        cin >> a[i];
        v.emplace_back(a[i],i);
    }
    mergeTree root(n);
    sort(all(v));
    for(auto x : v)
        root.update(1,1,n,x.second,x.first);

    ll ans = 0;
    for(int i=2; i<n; i++) {
        ans += root.upper_query(1,1,n,1,i-1,a[i]) * root.lower_query(1,1,n,i+1,n,a[i]);
    }
    cout << ans << endl;

    return 0;
}