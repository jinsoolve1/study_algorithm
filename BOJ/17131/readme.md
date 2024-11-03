## [백준 17131 - 여우가 정보섬에 올라온 이유](https://www.acmicpc.net/problem/17131)

### 알고리즘
- 머지소트 트리

### 풀이
별의 x좌표를 트리의 인덱스로, y좌표를 값으로 하는 머지소트 트리를 생성한다.  
v형 별자리는 [s.x < t.x < u.x]이며 [s.y > t.y < u.y] 인 (s,t,u)이다.  
한 별을 t라고 할 때, 머지소트 트리에서 t.x보다 작은 인덱스에서 t.y보다 큰 값의 개수와 t.x보다 큰 인덱스에서 t.y보다 큰 값의 개수를 구한다.  
두 값의 곱이 t를 v형 별자리의 꼭짓점으로 하며 만들 수 있는 v형 별자리의 개수다.

```c++
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

const ll mod = 1e9+7;
const int mxn = 4e5+1;

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
    ll query(int node, int start, int end, int left, int right, ll value) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node].end() - upper_bound(all(tree[node]), value);
        return query(node * 2, start, (start + end) / 2, left, right, value) +
        query(node * 2 + 1, (start + end) / 2 + 1, end, left, right, value);
    }
};

ll N, ans = 0;
vector<pll> v;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    mergeTree root(mxn);
    v.resize(N);
    for(int i=0; i<N; i++) {
        cin >> v[i].second >> v[i].first;
        v[i].second += 2e5+1;
    }
    sort(all(v)); // first: y, second: x
    for(pll t : v) root.update(1, 1, mxn, t.second, t.first);
    for(pll t : v) {
        ll s_cnt =  root.query(1, 1, mxn, 1, t.second - 1, t.first);
        ll u_cnt = root.query(1, 1, mxn, t.second + 1, mxn, t.first);
        ans = (ans + s_cnt * u_cnt) % mod;
    }
    cout << ans << '\n';
    return 0;
}
```