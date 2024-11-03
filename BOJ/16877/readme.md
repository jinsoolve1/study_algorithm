## [백준 16877 - 핌버](https://www.acmicpc.net/problem/16877)

### 알고리즘
- 필승 전략 게임
- 스프라그-그런디

### 풀이
스프라그 그런디 알고리즘을 이용해서 해결한다.
1. dp[k] := k개 돌더미를 제거할 때 선공이 이기는지 여부 라고 하자.
2. 기존 님게임과 다르게 피보나치 수열의 수들만 제거가 가능하므로, dp[i] = mex{ dp[i-fibo] | fibo는 가능한 피보나치 수들 } 이 된다.
3. mex를 구할 때, 결국 돌더미 당 최대 돌 개수가 3e6이므로 피보나치 수열 상 33까지만 해도 된다.  
   따라서, bool 배열을 이용하여 찾으면 해결할 수 있다.

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

const int mxn = 3e6+1;
vector<ll> dp(mxn,0), fibo(34);

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fibo[0]=0, fibo[1]=1;
    for(int i=2; i<34; i++) fibo[i] = fibo[i-1] + fibo[i-2];

    bool used[34];
    for(int i=1; i<mxn; i++) {
        memset(used, 0, sizeof used);
        for(int j=1; i>=fibo[j]; j++) used[dp[i-fibo[j]]] = true;
        while(used[dp[i]]) dp[i]++;
    }

    int n, p, r=0; cin >> n;
    while(n--) cin >> p, r ^= dp[p];
    cout << (r ? "koosaga" : "cubelover") << endl;

    return 0;
}
```

### 참고
https://m.blog.naver.com/PostView.naver?blogId=jinhan814&logNo=222850028124&categoryNo=56&proxyReferer=