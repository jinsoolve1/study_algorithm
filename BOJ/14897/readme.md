## [백준 14897 - 서로 다른 수와 쿼리 1](https://www.acmicpc.net/problem/14897)

### 알고리즘
- mo's algorithm
- 오프라인 쿼리
- 좌표압축

### 풀이
변경이 없고 쿼리만 존재하므로 오프라인 쿼리 사용이 가능하다. 따라서 mo's algorithm을 사용한다.  
이때, 값의 크기가 $10^9$까지 이므로 좌표압축을 해서 cnt를 계산해 준다.

### 후기
처음에 unordered_map을 사용해서 해보았는데 좌표압축을 하든 안 하든 시간초과가 났다.  
hash map이라 O(1)인데 worst case가 계속 발생하는지 시간초과가 나서 그냥 좌표압축 후 벡터에서 갯수를 셌다.

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

int sqrt_N;
struct Query {
    int idx, l, r;

    bool operator<(Query other) const {
        if(l/sqrt_N == other.l/sqrt_N) return r < other.r;
        return l < other.l;
    }
};

int N, Q;
int res;
vector<int> ans, cnt;
vector<int> v, values;
vector<Query> qs;

void add(int s, int e) {
    for(int i=s; i<=e; i++) {
        if(cnt[v[i]]++ == 0) res++;
    }
}
void remove(int s, int e) {
    for(int i=s; i<=e; i++) {
        if(--cnt[v[i]] == 0) res--;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    sqrt_N = sqrt(N); v.resize(N+1);
    for(int i=1; i<=N; i++) {
        cin >> v[i];
        values.emplace_back(v[i]);
    }
    sort(all(values));
    values.erase(unique(all(values)), values.end());
    for(int i=1; i<=N; i++) {
        v[i] = lower_bound(all(values), v[i]) - values.begin();
    }
    cnt.resize(values.size());
    cin >> Q;
    ans.resize(Q);
    for(int i=0; i<Q; i++) {
        int l, r; cin >> l >> r;
        qs.emplace_back(Query{i,l,r});
    }
    sort(all(qs));
    int l = qs[0].l, r = qs[0].l;
    cnt[v[l]]++; res = 1;
    for(Query q : qs) {
        if(q.l < l) add(q.l, l-1);
        if(l < q.l) remove(l, q.l-1);
        if(q.r < r) remove(q.r+1, r);
        if(r < q.r) add(r+1, q.r);
        l = q.l, r = q.r;
        ans[q.idx] = res;
    }
    for(int x : ans) cout << x << '\n';

    return 0;
}
```