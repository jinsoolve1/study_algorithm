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
    ll init(int node, int start, int end) {
        if(start == end) return tree[node] = 1;
        else return tree[node] = init(2 * node, start, (start + end) / 2) +
                                 init(2 * node + 1, (start + end) / 2 + 1, end);
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

int N;
vector<ll> a, ans;
vector<pll> qs;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    a = vector<ll>(N+1); ans = vector<ll>(N+1);
    for(int i=1; i<=N; i++) {
        cin >> a[i];
        qs.emplace_back(a[i],i);
    }

    segment root(N);
    root.init(1,1,N);

    sort(all(qs));
    ll tm = 0;
    for(pll q : qs) {
        ans[q.second] = root.sum(1,1,N,1,q.second) * q.first + root.sum(1,1,N,q.second+1,N) * (q.first-1) + tm;
        tm += q.first;
        root.update(1,1,N,q.second,-1);
    }
    for(int i=1; i<=N; i++) cout << ans[i] << endl;

    return 0;
}