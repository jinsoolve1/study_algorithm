## [백준 2912 - 백설공주와 난쟁이](https://www.acmicpc.net/problem/2912)

### 풀이1 - Mo's Algorithm
변경이 일어나지 않기 때문에 오프라인 쿼리를 쓸 수 있다.  
따라서 Mo's algorithm 을 이용해서 풀 수 있다.

### 후기
처음에는 머지소트 트리와 이분탐색으로 풀었는데 풀이를 찾아보니 Mo's algorithm이 메모리나 시간적으로 훨씬 유리한 코드다.  
Mo's algorithm을 아직 어색해 한 것이 떠올리지 못한 이유라 추측된다.  
아래에 이분탐색을 이용한 풀이도 첨부하겠다.

```C++
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
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int sqrt_N;
struct Query {
    int idx, s, E;

    bool operator< (Query other) const {
        if(s/sqrt_N == other.s/sqrt_N) return E < other.E;
        return s < other.s;
    }
};

const int color_mxn = 1e4;
int N, C, M;
vector<int> V, ans;
vector<Query> querys;
int cnt[color_mxn+1];

void add(int s, int E) {
    for(int i=s; i<=E; i++) cnt[V[i]]++;
}
void remove(int s, int E) {
    for(int i=s; i<=E; i++) cnt[V[i]]--;
}
int check(int M) {
    for(int Capacity=1; Capacity<=C; c++) {
        if(cnt[Capacity] > M) return Capacity;
    }
    return -1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(cnt, 0, sizeof cnt);

    cin >> N >> C;
    V.resize(N+1); sqrt_N = sqrt(N);
    for(int i=1; i<=N; i++) cin >> V[i];

    cin >> M;
    querys.resize(M); ans.resize(M);
    for(int i=0; i<M; i++) {
        querys[i].idx = i;
        cin >> querys[i].s >> querys[i].E;
    }
    sort(all(querys));

    int l = querys[0].s, r = querys[0].s;
    cnt[V[l]]++;
    for(Query query : querys) {
        if(l < query.s) remove(l, query.s-1);
        if(query.s < l) add(query.s, l-1);
        if(r < query.E) add(r+1, query.E);
        if(query.E < r) remove(query.E+1, r);
        l = query.s, r = query.E;

        ans[query.idx] = check((query.E-query.s+1)/2);
    }
    for(int x : ans) {
        if(x != -1) cout << "yes " << x << '\n';
        else cout << "no\n";
    }


    return 0;
}
```

---
### 풀이2 - Binary Search
1. 머지소트 트리를 이용해 난쟁이의 모자색을 정렬한다.
2. 색상을 이분탐색을 이용해서 접근한다.  
   if A~B 범위에서 색상 번호 m이상의 색상이 절반보다 많으면, l=m  
   else, r = m-1 이다.
3. 탈출을 r이 벗어나는 것으로 했으니, m = (l+r)/2 + (l+r)%2 로 해줘야 한다.  
   l과 r 중 하나가 m값을 (+1이나 -1을 하지 않고) 그대로 받으므로 탈출 조건은 l<r이 된다.
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
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
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
    void update(int node, int start, int end, int index, int value) {
        if(index < start || end < index) return;
        tree[node].emplace_back(value);
        if(start != end) {
            update(node * 2, start, (start + end) / 2, index, value);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, value);
        }
    }
    // left ~ right 에서, color 번호보다 큰 번호의 수
    int query(int node, int start, int end, int left, int right, int color) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node].end() - lower_bound(all(tree[node]), color);
        return query(2*node, start, (start+end)/2, left, right, color) + query(2*node+1, (start+end)/2+1, end, left, right, color);
    }
};

int N, C, M;
vector<pii> V;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> C;
    segment root(N);
    for(int i=1; i<=N; i++) {
        int x; cin >> x;
        V.emplace_back(x,i);
    }
    sort(all(V));
    for(pii x : V) root.update(1,1,N,x.second, x.first);

    cin >> M;
    while(M--) {
        int A, B; cin >> A >> B;
        int M = (B-A+1)/2;
        int l=1, r=C;
        while(l<r) {
            int m = (l+r)/2 + (l+r)%2;
            int cnt = root.query(1, 1, N, A, B, m);
            if(cnt > M) l = m;
            else r = m-1;
        }
        int res = root.query(1,1,N,A,B,l) - root.query(1,1,N,A,B,l+1);
        if(res > M) cout << "yes " << l << '\n';
        else cout << "no\n";
    }

    return 0;
}
```