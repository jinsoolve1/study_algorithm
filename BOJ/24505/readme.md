## [백준 24505 - blobhyperthink](https://www.acmicpc.net/problem/24505)

### 알고리즘
- 펜윅트리(구간합)

### 풀이
1. fenwick[i][x] := 현재까지 추가된 숫자들 중 길이가 i이면서 마지막 수가 x보다 작거나 같은 LIS의 갯수이다.
2. 수를 추가할 때마다, 
   1. update(1,x,1)을 먼저 해준다.
   2. i=2~11 동안, update(i,x,sum(i-1,x-1))을 해준다.  
      i-1길이이면서 끝값이 x-1보다 작거나 같은 LIS의 갯수만큼 더 추가 되기 때문이다.
3. sum(11,1e5)가 정답이 된다.

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

const int mxn = 1e5+1;
const int mod = 1e9+7;

int N;
ll ans = 0;
ll fenwick[12][mxn];

void update(int cnt, int idx, int value) {
    while(idx < mxn) {
        fenwick[cnt][idx] = (fenwick[cnt][idx] + value) % mod;
        idx += (idx & -idx);
    }
}
ll sum(int cnt, int idx) {
    ll ret = 0;
    while(idx) {
        ret = (ret + fenwick[cnt][idx]) % mod;
        idx -= (idx & -idx);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(fenwick, 0, sizeof fenwick);

    cin >> N;
    while(N--) {
        int x; cin >> x;
        update(1,x,1);
        for(int i=2; i<12; i++) update(i, x, sum(i-1,x-1));
    }
    cout << sum(11, 1e5) << endl;

    return 0;
}
```