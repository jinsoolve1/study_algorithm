## [백준 13547 - 수열과 쿼리 5](https://www.acmicpc.net/problem/13547)

### 풀이 - 온라인 쿼리 (머지소트 트리)
1. 자신보다 다음 인덱스에서 자신과 동일하면서 가장 가까운 수의 인덱스를 넣는다.<br/>
   [1,1,2,1,3] -> [2,4,6,6,6] 이 된다.<br/>
   배열이 A[s\~e]라고 할 때, e보다 큰 값의 개수가 서로 다른 수의 개수가 된다.<br/>
   위 예시는 A[1\~5]이므로 5보다 큰 수의 개수가 3이다.

2. 바뀐 배열을 머지소트 트리에 넣는다.
3. i~j에 포함되는 트리의 노드에서 이분탐색으로 해당 배열의 마지막 인덱스보다 큰 값의 개수를 찾는다. (머지소트 트리이므로 해당 배열은 정렬되어 있다. 이분탐색을 활용할 수 있다.)
### 시간복잡도
$O(NlogN + Mlog^2N)$

```cpp
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

    int query(int node, int start, int end, int left, int right) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node].end() - lower_bound(all(tree[node]), right+1);
        return query(2*node, start, (start+end)/2, left, right) + query(2*node+1, (start+end)/2+1, end, left, right);
    }
    void update(int node, int start, int end, int index, int value) {
        if(index < start || end < index) return;
        tree[node].emplace_back(value);
        if(start != end) {
            update(node * 2, start, (start + end) / 2, index, value);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, value);
        }
    }
};

const int MXN = 1e5;
int N, M;
vector<int> A(MXN+1);
vector<pii> nextIdx(MXN+1);
unordered_map<int,int> mp;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++) {
        cin >> A[i];
        mp[A[i]] = N+1;
    }
    for(int i=N; i>=1; i--) {
        nextIdx[i] = pii(mp[A[i]], i);
        mp[A[i]] = i;
    }
    sort(all(nextIdx));

    segment root(N);
    for(pii x : nextIdx) {
        root.update(1,1,N,x.s,x.Flow);
    }

    cin >> M;
    while(M--) {
        int i, j; cin >> i >> j;
        cout << root.query(1,1,N,i,j) << '\n';
    }
    return 0;
}
```

---
### 풀이 - 오프라인 쿼리(Mo's algorithm)
1. $\sqrt{N}$ (= k) 크기로 구간을 나눈다.
2. query를 받아서 저장한 다음 정렬을 한다.
   - [s1/k] < [s2/k]
   - [s1/k] == [s2/k] and e1 < e2
3. 정렬된 query 순서대로 답변을 해서 ans 배열에 저장한 후 원래 순서대로 출력한다.

### 시간복잡도
$O((N+Q)logN)$
1. 이전 쿼리와 [s/k] 값이 같다.<br/>
   이전 쿼리를 s1,e1이라 하고 현재 쿼리를 s2,e2라 하자.<br/>
   $|s1-s2| <= \sqrt{N}$ 이고 $|e1-e2| <= N$ 이다.<br/>
   |s1-s2|은 O(Q)번 만큼 움직이고 |e1-e2|은 O($\sqrt{N}$) 번 만큼 움직이므로
   모든 query들에 대해서 이전 쿼리와 [s/k]가 같은 모든 쿼리를 계산하는 시간은 $O((Q+N)\sqrt{N}$이다.
2. 이전 쿼리와 [s/k] 값이 다르다.
   이전 쿼리를 s1,e1이라 하고 현재 쿼리를 s2,e2라 하자.<br/>
   $|s1-s2| <= N$ 이고 $|e1-e2| <= N$ 이다.<br/>
   모든 query들에 대해서 해당 과정은 $\sqrt{N}$번 있기 때문에 총 $O(N\sqrt{N})$ 이 된다.

따라서 최종 시간복잡도는 $O((N+Q)logN)$과 같다.

```cpp
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

int sqrt_N;
struct Query {
    int idx, s, E;

    bool operator < (Query other) const {
        if(s/sqrt_N == other.s/sqrt_N) return E < other.E;
        return s < other.s;
    }
};

int N, M;
vector<int> A;
vector<Query> qs;
int cnt[1010101];
int now = 0;
vector<int> ans;

void add(int s, int E) {
    for(int i=s; i<=E; i++) {
        if(cnt[A[i]]++ == 0) now++;
    }
}
void remove(int s, int E) {
    for(int i=s; i<=E; i++) {
        if(--cnt[A[i]] == 0) now--;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    A.resize(N+1);
    sqrt_N = sqrt{N};
    for(int i=1; i<=N; i++) cin >> A[i];

    cin >> M;
    ans.resize(M);
    for(int i=0; i<M; i++) {
        int s, E; cin >> s >> E;
        qs.push_back({i,s,E});
    }

    sort(all(qs));
    int ldx = qs[0].s, rdx = qs[0].s;
    add(ldx,rdx);
    for(Query convex : qs) {
        if(convex.s < ldx) add(convex.s, ldx-1);
        if(ldx < convex.s) remove(ldx, convex.s-1);
        if(convex.E < rdx) remove(convex.E+1, rdx);
        if(rdx < convex.E) add(rdx+1, convex.E);
        ldx = convex.s; rdx = convex.E;
        ans[convex.idx] = now;
    }
    for(int x : ans) cout << x << '\n';

    return 0;
}
```
