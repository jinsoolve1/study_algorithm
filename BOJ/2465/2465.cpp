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
    ll init(int initVal, int node, int start, int end) {
        if(start == end) return tree[node] = initVal;
        else return tree[node] = init(initVal, 2 * node, start, (start + end) / 2) +
                                 init(initVal, 2 * node + 1, (start + end) / 2 + 1, end);
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
    int query(int node, int start, int end, ll target) {
        if(start == end) return start;
        if(target <= tree[2*node]) return query(2*node, start, (start+end)/2, target);
        return query(2*node+1, (start+end)/2+1, end, target-tree[2*node]);
    }
};

int N;
vector<int> heights;
stack<int> S, ans;
segment tree;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    heights.resize(N);
    tree.resize(N); tree.init(1,1,0,N-1);
    for(int i=0; i<N; i++) cin >> heights[i];
    sort(all(heights));
    for(int i=0; i<N; i++) { int x; cin >> x; S.push(x); }
    while(!S.empty()) {
        int target = S.top(); S.pop();
        int idx = tree.query(1,0,N-1,target+1);
        ans.push(heights[idx]);
        tree.update(1,0,N-1,idx,-1);
    }
    while(!ans.empty()) {
        cout << ans.top() << endl;
        ans.pop();
    }

    return 0;
}