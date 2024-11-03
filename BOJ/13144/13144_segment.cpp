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
#define f first
#define s second
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
    ll init(vector<ll> &a, int node, int start, int end) {
        if(start == end) return tree[node] = a[start];
        else return tree[node] = min(init(a, 2 * node, start, (start + end) / 2),
                                     init(a, 2 * node + 1, (start + end) / 2 + 1, end));
    }
    ll Min(int node, int start, int end, int left, int right) {
        if(right < start || end < left) return INF;
        if(left <= start && end <= right) return tree[node];
        return min(Min(node * 2, start, (start + end) / 2, left, right),
                   Min(node * 2 + 1, (start + end) / 2 + 1, end, left, right));
    }
};

int N;
vector<ll> a(101010);
vector<ll> v(101010);
unordered_map<int,int> idx;


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++) {
        cin >> a[i];
        idx[a[i]] = N+1;
    }
    for(int i=N; i>=1; i--) {
        v[i] = idx[a[i]];
        idx[a[i]] = i;
    }
    segment root(N);
    root.init(v,1,1,N);
    ll ans = 0;
    for(int i=1; i<=N; i++) {
        ans += (root.Min(1,1,N,i,(int)v[i]-1) - i);
    }
    cout << ans << '\n';

    return 0;
}