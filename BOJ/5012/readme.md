## [백준 5012 - 불만 정렬](https://www.acmicpc.net/problem/5012)

### 알고리즘
- 머지소트 트리

### 풀이
a[i] > a[j] > a[k] and i < j < k 를 찾아야 한다. 이때, j를 기준으로 생각해 보자.  
a[j]를 가운데 수로 선택하는 경우의 수 = ([1,j) 구간에서 a[j]보다 큰 수의 갯수) x ((j,N] 구간에서 a[j]보다 작은 수의 갯수) 가 된다.  
머지소트 트리를 이용하여 해당 값들을 구할 수 있다.

다른 풀이로는 수의 크기가 어차피 [1,N] 구간이므로 세그먼트 트리에 tree[a ~ b] := a이상 b이하의 숫자의 갯수를 저정한다.  
매 인덱스마다 해당 인덱스 이전의 인덱스이면서 해당 수보다 큰 수의 갯수를,  
인덱스를 반대로 탐색하면서 해당 수보다 작은 수의 갯수를 저장하면 머지소트 트리와 같은 원리로 해결할 수 있다. 

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
```