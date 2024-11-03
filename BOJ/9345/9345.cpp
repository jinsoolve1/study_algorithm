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
using pll = pair<ll, ll>;

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
    ll initMin(int node, int start, int end) {
        if(start == end) return tree[node].first = start;
        else return tree[node].first = min(initMin(2 * node, start, (start + end) / 2),
                                           initMin(2 * node + 1, (start + end) / 2 + 1, end));
    }
    ll initMax(int node, int start, int end) {
        if(start == end) return tree[node].second = start;
        else return tree[node].second = max(initMax(2 * node, start, (start + end) / 2),
                                           initMax(2 * node + 1, (start + end) / 2 + 1, end));
    }
    void init(int node, int start, int end) {
        initMin(node, start, end);
        initMax(node, start, end);
    }
    ll updateMin(int node, int start, int end, int index, ll value) {
        if(index < start || end < index) return tree[node].first;
        if(start == end) return tree[node].first = value;
        return tree[node].first = min(updateMin(node * 2, start, (start + end) / 2, index, value),
                                      updateMin(node * 2 + 1, (start + end) / 2 + 1, end, index, value));
    }
    ll updateMax(int node, int start, int end, int index, ll value) {
        if(index < start || end < index) return tree[node].second;
        if(start == end) return tree[node].second = value;
        return tree[node].second = max(updateMax(node * 2, start, (start + end) / 2, index, value),
                                      updateMax(node * 2 + 1, (start + end) / 2 + 1, end, index, value));
    }
    void update(int node, int start, int end, int index, ll value) {
        updateMin(node, start, end, index, value);
        updateMax(node, start, end, index, value);
    }
    ll minValue(int node, int start, int end, int left, int right) {
        if(right < start || end < left) return INF;
        if(left <= start && end <= right) return tree[node].first;
        return min(minValue(2*node, start, (start+end)/2, left, right),
                   minValue(2*node+1, (start+end)/2+1, end, left, right));
    }
    ll maxValue(int node, int start, int end, int left, int right) {
        if(right < start || end < left) return -1;
        if(left <= start && end <= right) return tree[node].second;
        return max(maxValue(2*node, start, (start+end)/2, left, right),
                   maxValue(2*node+1, (start+end)/2+1, end, left, right));
    }
    bool query(int node, int start, int end, int left, int right) {
        return (minValue(node, start, end, left, right) == left) && (maxValue(node, start, end, left, right) == right);
    }
};

vector<ll> v; // v[선반번호]= dvd번호
int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        int N, K; cin >> N >> K;
        segment root(N);
        root.init(1,0,N-1);
        v.resize(N);
        for(ll i=0; i<N; i++) v[i] = i;
        while(K--) {
            int Q, A, B; cin >> Q >> A >> B;
            if(Q == 0) {
                root.update(1,0,N-1,A,v[B]);
                root.update(1,0,N-1,B,v[A]);
                swap(v[A], v[B]);
            }
            else {
                if(root.query(1,0,N-1,A,B)) cout << "YES\n";
                else cout << "NO\n";
            }
        }
    }


    return 0;
}