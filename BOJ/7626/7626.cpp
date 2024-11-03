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

struct Query {
    int x, y1, y2, diff;
    bool operator<(Query other) const {
        return x < other.x;
    }
};
vector<ll> val;
class segment {
public:
    vector<ll> tree, cnt; //tree[node] := a[start ~ end] 의 합

    segment() {}
    segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size, 0);
        cnt.resize(size, 0);
    }
    void update(int node, int start, int end, int left, int right, ll diff) {
        if(right < start || end < left) return;
        if(left <= start && end <= right) cnt[node] += diff;
        else {
            update(node * 2, start, (start + end) / 2, left, right, diff);
            update(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
        }
        if(cnt[node]) tree[node] = val[end+1]-val[start];
        else {
            if(start == end) tree[node] = 0;
            else tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
};

int N, mxn;
vector<Query> qs;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N; i++) {
        int x1, x2, y1, y2; cin >> x1 >> x2 >> y1 >> y2;
        qs.push_back({x1, y1, y2, 1});
        qs.push_back({x2, y1, y2, -1});
        val.emplace_back(y1);
        val.emplace_back(y2);
    }
    sort(all(val)); val.erase(unique(all(val)), val.end());
    mxn = val.size()-2;
    segment root(mxn+1);

    sort(all(qs));
    ll ans = 0, prev_x = qs.front().x;
    for(Query q : qs) {
        int y1 = lower_bound(all(val), q.y1) - val.begin();
        int y2 = lower_bound(all(val), q.y2) - val.begin()-1;
        ans += (q.x - prev_x) * root.tree[1];
        root.update(1,0,mxn,y1,y2,q.diff);
        prev_x = q.x;
    }
    cout << ans << endl;

    return 0;
}