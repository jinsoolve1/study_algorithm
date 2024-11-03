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
    int find(int node, int start, int end, ll target) {
        if(start == end) return end;
        if(target <= tree[2*node]) return find(2*node, start, (start+end)/2, target);
        return find(2*node+1, (start+end)/2+1, end, target - tree[2*node]);
    }
};

int N, K;
vector<int> ans;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    int k=1;
    segment root(N);
    root.init(1,1,N);
    while(root.tree[1] != 0) {
        ll s = root.sum(1,1,N,1,k) - root.sum(1,1,N,k,k);
        ll target = (K+s) % root.tree[1];
        if(target == 0) target = root.tree[1];
        k = root.find(1,1,N, target);
        ans.emplace_back(k);
        root.update(1,1,N,k,-1);
    }
    cout << '<';
    for(int x : ans) {
        cout << x;
        if(x == ans.back()) cout << ">\n";
        else cout << ", ";
    }

    return 0;
}