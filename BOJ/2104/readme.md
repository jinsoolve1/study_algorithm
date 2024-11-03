## [백준 2104 - 부분배열 고르기](https://www.acmicpc.net/problem/2104)

### 알고리즘
- 분할 정복

### 풀이
가장 큰 히스토그램 너비 찾는 문제와 동일히다.  
solve(s,e) = solve(s,m), solve(m+1,e) 혹은 m과 m+1을 포함하면서 가장 큰 값 이 3개 중 안에서 있다.  
m과 m+1을 포함하면서 가장 큰 값은 스위핑을하는데, l와 r 중 더 큰 값부터 추가하면서 값을 업데이트시키면 된다.

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

int N;
vector<ll> A;

ll solve(int s, int e) {
    if(s == e) return A[s]*A[s];

    int m = (s+e)/2;
    ll ret = max(solve(s,m), solve(m+1,e));
    int l = m, r = m+1;
    ll sum = A[l] + A[r], minVal = min(A[l],A[r]);
    ret = max(ret, sum*minVal);
    while(s!=l || r!=e) {
        ll lval = (s<l) ? A[l-1] : -1;
        ll rval = (r<e) ? A[r+1] : -1;

        if(lval >= rval) {
            sum += A[--l];
            minVal = min(minVal, A[l]);
        }
        else {
            sum += A[++r];
            minVal = min(minVal, A[r]);
        }
        ret = max(ret, sum*minVal);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    A.resize(N+1);
    for(int i=1; i<=N; i++) cin >> A[i];
    cout << solve(1,N) << endl;

    return 0;
}
```