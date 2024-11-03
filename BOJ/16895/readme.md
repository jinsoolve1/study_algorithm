## [백준 16895 - 님 게임 3](https://www.acmicpc.net/problem/16895)

### 알고리즘
- 님 게임

### 풀이
1. 구사과가 돌을 제거했을 때 nim_sum(모든 돌의 개수를 xor한 값)이 0이 되면 구사과가 필승한다.
2. 인덱스 i를 제외한 모든 돌의 개수의 nim_sum을 구해놓고 해당 돌의 개수를 한 개씩 줄여보면서 nim_sum 값이 0이 되는 갯수를 구한다.

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

int N;
vector<int> P;

int nim_sum_without_j(int j) {
    int ret = 0;
    for(int i=0; i<N; i++) {
        if(i == j) continue;
        ret ^= P[i];
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    P.resize(N);
    for(int i=0; i<N; i++) cin >> P[i];

    int ans = 0;
    for(int i=0; i<N; i++) {
        int tmp = P[i];
        int nimSum = nim_sum_without_j(i);
        while(P[i]--) {
            ans += ((nimSum ^ P[i]) == 0);
        }
        P[i] = tmp;
    }
    cout << ans << '\n';

    return 0;
}
```

### 후기
님 게임을 알지 못하면 풀지 못하는 문제다. 아래 링크를 참고해서 공부해보면 좋을 듯 하다.  
https://librewiki.net/wiki/필승_전략_게임