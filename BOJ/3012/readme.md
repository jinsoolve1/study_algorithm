## [백준 3012 - 올바른 괄호 문자열](https://www.acmicpc.net/problem/3012)

### 알고리즘
- 다이나믹 프로그래밍
- 분할 정복

### 풀이
1. solve(s,e) := (s~e 가능한 괄호문자열의 경우의 수) 이라 하자.
2. i = s+1, s+3, s+5 , ...  e보다 작거나 같을 동안  
   (i+=2 를 하는 이유는 s+1 ~ i-1이 괄호쌍이 되야 하기 때문에, 짝수이어야 하기 때문이다.)  
   S[s] + S[i]가 가능한 괄호라면,  
   solve(s+1,i-1) * solve(i+1,e)를 더하면 된다. 
3. 문제에서 10^5보다 값이 커진 경우에만 5자리로 꽉 채워서 출력해야 하는데,  
   값을 저장할 때 mod(=10^5)보다 크거나 같으면 res = res%mod + mod로 저장한다.  
   만약 solve(0,N-1) >= mod라면, 5자리로 꽉 채워서 출력하면 되고, 아니라면 그냥 원래 값을 출력하면 된다.

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

const ll mod = 1e5;
int N;
string S;
char open[] = {'(', '{', '['};
char close[] = {')', '}', ']'};
ll dp[200][200];

ll solve(int s, int e) {
    if(s>e) return 1;
    ll &ret = dp[s][e];
    if(ret != -1) return ret;
    ret = 0;
    for(int i=s+1; i<=e; i+=2) {
        for(int j=0; j<3; j++) {
            if((S[s] == open[j] || S[s] == '?') && (S[i] == close[j] || S[i] == '?')) {
                ret += solve(s+1,i-1) * solve(i+1,e);
                if(ret >= mod) ret = ret%mod + mod;
            }
        }
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);
    cin >> N >> S;
    ll ans = solve(0,N-1);
    if(ans >= mod) {
        cout.width(5); cout.fill('0');
        cout << ans % mod << endl;
    }
    else cout << ans;

    return 0;
}
```

### 참고
https://jaimemin.tistory.com/1135