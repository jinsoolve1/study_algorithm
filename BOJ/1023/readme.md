## [백준 1023 - 괄호 문자열](https://www.acmicpc.net/problem/1023)

### 알고리즘
- 다이나믹 프로그래밍

### 풀이
'(' = +1, ')' = -1 의 점수라고 하자.  
dp[i][j] := (현재까지의 prefix 점수가 j인 상황에서 (앞으로 채울) suffix의 길이가 i일 때, 만들 수 있는 '괄호ㄴㄴ 문자열'의 개수)  

음수가 발생하지 않기 위해 초기 prefix 점수 = 50 으로 설정한다.  
j가 50보다 크거나 같을 때는 dp[i][j] = dp[i-1][j+1] + dp[i-1][j-1] 로 해결할 수 있다.    
j가 50보다 작을 때는 이미 '괄호ㄴㄴ 문자열'이므로 dp[i][j] = $2^i$ 가 된다.  
dp의 초기값은 dp[0] 배열은 1로, dp[1] 배열은 2로 초기화하는데, dp[0][50]과 dp[1][51]은 올바른 괄호 문자열이 하나씩 포함되어 있으므로 1을 빼준 각각 0과 1로 초기화해준다.  

문자열을 찾을 때를 살펴보자.  
alright := (현재까지 올바른 괄호 문자열의 규칙을 지키고 있었는 지의 여부)  
val := 현재 자리를 '('로 채웠을 때 가능한 괄호ㄴㄴ 문자열의 개수를 체크한다.  
1. val >= K,  
   현재 자리를 '('를 채울 수 있다는 의미이므로 ans += '('를 해주고, prefix++를 해준다.  
2. val < K,   
   현재 자리를 ')'로 채운다는 의미이므로 ans += ')'를 해주고, K -= val을 해주고, prefix--를 해준다.

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

int N; ll K;
ll dp[51][101];
string ans = "";

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, 0, sizeof dp);
    for(int p=0; p<=100; p++)
        dp[0][p] = 1, dp[1][p] = 2;
    dp[0][50] = 0, dp[1][51] = 1;

    for(int n=2; n<=50; n++) {
        for(int p=0; p<50; p++) dp[n][p] = (1LL << n);
        for(int p=50; p<=100; p++) dp[n][p] = dp[n-1][p+1] + dp[n-1][p-1];
    }

    int prefix = 50;
    cin >> N >> K; K++;
    if(K > dp[N][50]) {
        cout << "-1\n";
        return 0;
    }
    bool alright = true; // 올바른 괄호인가
    for(int n=N; n>=1; n--) {
        ll val = dp[n-1][prefix+1]; // '('를 배치했을 때 가능한 괄호ㄴㄴ 문자열 개수
        if(!alright) val = 1LL << (n-1);
        if(val >= K) ans += '(', prefix++;
        else ans += ')', K -= val, prefix--;
        if(prefix < 50) alright = false;
    }
    cout << ans << '\n';

    return 0;
}
```



### 참고
https://blog.encrypted.gg/264