## [백준 13548 - 수열과 쿼리 6](https://www.acmicpc.net/problem/13548)

### 알고리즘
- mo's algorithm

### 풀이
1. cnt[x] := 숫자 x가 나온 횟수
2. ccnt[cnt[x]] := cnt[x]번 만큼의 횟수가 나온 수들의 개수  
   예를 들어, 555 이면 cnt[5] = 3, ccnt[3] = 1이 된다. 3번 나온 수의 종류가 1개이므로 ccnt[3] = 1이다.
3. 현재까지의 가장 많이 나온 횟수를 now라 하자.  
   1. add 할 때는 cnt[x]에 1을 더하고 가장 큰 값이 now가 된다. ccnt 또한 업데이트 해준다.
   2. remove 할 때는 cnt[x]에 1을 빼고 ccnt를 업데이트 해준다. ccnt[now]가 0이라면 now--를 해주면 된다.
4. 탐색은 mo's algorithm을 이용해 O(N x sqrt(N)) 시간으로 탐색 가능하다.

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

int sqrtN;
struct Query {
    int idx, s, e;
    bool operator<(const Query &other) const {
        if(s/sqrtN == other.s/sqrtN) return e < other.e;
        return s < other.s;
    }
};

const int mxn = 1e5;
int N, M;
vector<int> A, ans;
vector<Query> qs;
int cnt[mxn+1], ccnt[mxn+1];
int now = 0;

void add(int x) {
    ccnt[cnt[A[x]]++]--;
    ccnt[cnt[A[x]]]++;
    now = max(now, cnt[A[x]]);
}
void remove(int x) {
    ccnt[cnt[A[x]]--]--;
    ccnt[cnt[A[x]]]++;
    if(ccnt[now]==0) now--;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(cnt, 0, sizeof cnt); memset(ccnt, 0, sizeof ccnt);

    cin >> N; A.resize(N+1); sqrtN = sqrt(N);
    for(int i=1; i<=N; i++) cin >> A[i];

    cin >> M; qs.resize(M); ans.resize(M);
    for(int i=0; i<M; i++) {
        qs[i].idx = i;
        cin >> qs[i].s >> qs[i].e;
    }
    sort(all(qs));
    int l = qs[0].s, r = qs[0].s;
    add(l);
    for(Query q : qs) {
        while(l < q.s) remove(l++);
        while(l > q.s) add(--l);
        while(r < q.e) add(++r);
        while(r > q.e) remove(r--);
        ans[q.idx] = now;
    }
    for(int x : ans) cout << x << endl;

    return 0;
}
```

### 참고
https://stonejjun.tistory.com/88