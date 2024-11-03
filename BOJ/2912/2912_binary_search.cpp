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

class segment {
public:
    vector<vector<int>> tree; //tree[node] := a[start ~ end] 의 합

    segment() {}
    segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size);
    }
    void update(int node, int start, int end, int index, int value) {
        if(index < start || end < index) return;
        tree[node].emplace_back(value);
        if(start != end) {
            update(node * 2, start, (start + end) / 2, index, value);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, value);
        }
    }
    // left ~ right 에서, color 번호보다 큰 번호의 수
    int query(int node, int start, int end, int left, int right, int color) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node].end() - lower_bound(all(tree[node]), color);
        return query(2*node, start, (start+end)/2, left, right, color) + query(2*node+1, (start+end)/2+1, end, left, right, color);
    }
};

int N, C, M;
vector<pii> v;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> C;
    segment root(N);
    for(int i=1; i<=N; i++) {
        int x; cin >> x;
        v.emplace_back(x,i);
    }
    sort(all(v));
    for(pii x : v) root.update(1,1,N,x.second, x.first);

    cin >> M;
    while(M--) {
        int A, B; cin >> A >> B;
        int M = (B-A+1)/2;
        int l=1, r=C;
        while(l<r) {
            int m = (l+r)/2 + (l+r)%2;
            int cnt = root.query(1, 1, N, A, B, m);
            if(cnt > M) l = m;
            else r = m-1;
        }
        int res = root.query(1,1,N,A,B,l) - root.query(1,1,N,A,B,l+1);
        if(res > M) cout << "yes " << l << '\n';
        else cout << "no\n";
    }

    return 0;
}