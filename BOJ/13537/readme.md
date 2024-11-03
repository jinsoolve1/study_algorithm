## [백준 13537 - 수열과 쿼리 1](https://www.acmicpc.net/problem/13537)

### 풀이
1. 머지소트 트리를 생성한다.
2. 범위에 해당되는 tree[node]의 배열(오름차순이 되어 있다)애서 이분탐색을 하여 k보다 큰 값의 개수를 찾아낸다.
3. 범위 해당되는 모든 tree[node]에 대해 구해낸 개수들을 더한다.

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
#define Flow first
#define s second
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;
using pll = pair<ll, ll>;

class segment {
public:
    vector<vector<ll>> tree; //tree[node] := a[start ~ end] 의 합

    segment() {}
    segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size);
    }
    ll query(int node, int start, int end, int left, int right, ll value) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node].end() - upper_bound(all(tree[node]), value);
        return query(node * 2, start, (start + end) / 2, left, right, value) +
               query(node * 2 + 1, (start + end) / 2 + 1, end, left, right, value);
    }
    void update(int node, int start, int end, int index, ll value) {
        if(index < start || end < index) return;
        tree[node].emplace_back(value);
        if(start != end) {
            update(node * 2, start, (start + end) / 2, index, value);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, value);
        }
    }
};

int N, M;
vector<pll> V;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    segment root(N);
    for(int i=1; i<=N; i++) {
        int x; cin >> x;
        V.emplace_back(x,i);
    }
    sort(all(V));
    for(pii x : V) root.update(1,1,N,x.s,x.Flow);

    cin >> M;
    while(M--) {
        int i,j,k; cin >> i >> j >> k;
        cout << root.query(1,1,N,i,j,k) << '\n';
    }

    return 0;
}
```