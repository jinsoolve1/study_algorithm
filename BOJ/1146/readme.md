## [백준 1146 - 지그재그 서기](https://www.acmicpc.net/problem/1146)

### 알고리즘
- 다이나믹 프로그래밍
- 수학, 조합론

### 풀이
1. here를 기준으로 here보다 작은 수의 개수를 left, 큰 수의 개수를 right라 하자.  
   here보다 작은 수와 큰 수의 종류는 중요하지 않다. 1,2,3이 있든 50,55,60이 있든 결과는 같다.
2. there = here+i 라 하자. 즉, 남은 수 중에 here보다 i번째 만큼 큰 수를 택했다고 하자.  
   there의 left = left + i-1, there의 right = right - i 가 된다.
3. 따라서 dp[left][right][inc]로 점화식을 세울 수 있다. inc = true이면 더 큰 수를 택해야 한다.  
   left == 0 and right == 0 이면 무사히 지그재그 서기를 완성했으므로 1을 반환한다.

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

const int mod = 1e6;
int N;
int dp[100][100][2];
int ans = 0;

int solve(int left, int right, bool inc) {
    if(left == 0 && right == 0) return 1;
    int &ret = dp[left][right][inc];
    if(ret != -1) return ret;
    ret = 0;
    if(inc) for(int i=1; i<=right; i++)
        ret = (ret + solve(left+i-1,right-i,!inc)) % mod;
    else for(int i=1; i<=left; i++)
        ret = (ret + solve(left-i,right+i-1,!inc)) % mod;
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);
    cin >> N;
    if(N == 1) {
        cout << "1\n";
        return 0;
    }
    for(int l=0, r=N-1; r>=0; l++, r--) {
        ans = (ans + solve(l,r,true)) % mod;
        ans = (ans + solve(l,r,false)) % mod;
    }
    cout << ans << '\n';

    return 0;
}
```

### 참고
https://m.blog.naver.com/pasdfq/221317287900