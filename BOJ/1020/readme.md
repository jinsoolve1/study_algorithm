## [백준 1020 - 디지털 카운터](https://www.acmicpc.net/problem/1020)

### 알고리즘
- 다이나믹 프로그래밍

### 풀이
- dp[i][j] := (선분 j개로 만들 수 있는 i자리 수들 중 최솟값)  
- line[0~9] := (각 수의 선분 갯수)

$$dp[i][j+line[n]] = n*pow10[i] + dp[i-1][j]$$ 재귀식으로 dp 값을 구할 수 있다.  
ex) dp[2][6] = 14 (선분 6개로 만들 수 있는 수들 중 가장 작은 수는 14이다.)  

다음과 같은 방식으로 dp를 이용하여 문제를 해결한다.  
ex) 입력 7788
1. ans = 10^4 으로 초기화한다.  
    한 바퀴를 돌고나서 다음 7788이면 당연히 같을 수 밖에 없기 때문이다.

2. res = 778n  
    n = 0 ~ 9 동안, line[n] == line[8] 을 찾는다.  
    ans = (res + pow_10[4] - stoll(num)) % pow_10[4] 으로 업데이트 해준다. (pow_10[4] = 10^4, stoll(num)은 num을 longlong으로 바꾼 결과)  
    위 공식이 가능한 이유는   
    if res > num, ans = res - num   
    else, ans = res + pow_10[4] - num 이기 때문이다.  

3. res = 77nX  
    n = 0 ~ 9 동안, X = dp[1][14 - line[n]] 이 된다.  
    위 공식이 성립하는 이유를 살펴보자.  
    7788의 lineCnt = 3+3+7+7 = 20이다.  
    77은 고정이니, 20-3-3 = 14가 된다. 여기서 nX의 선분 수가 14개 이어야지만 20개로 만들어줄 수 있다.  
    그렇다면 X의 값은 선분이 14-line[n]개 이면서 자릿수가 1인 수 중 가장 작은 값이 된다는 의미다.  
    ans를 업데이트 시켜준다.

4. res = 7nXX  
    XX = dp[2][17 - line[n]] 이 된다.
    그 이유는 마찬가지로 nXX 부분의 선분 개수가 17개가 되어야 하고,  
    그렇다면 XX의 선분의 개수는 17 - line[n]개가 되어야 한다.   
    ans를 업데이트 시켜준다.

5. res = nXXX  
    XXX = dp[3][20 - line[n]] 이 된다. 
    이유는 nXXX의 선분개수가 20개가 되어야 하고,  
    그렇다면 XXX의 선분 개수는 20 - line[n]개가 되어야 한다.  
    ans를 업데이트 시켜준다.

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

ll pow_10[] = { 1,10,100,1000,10000,100000,1000000, 10000000, 100000000, 1000000000, 10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000 };
int line[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};
ll dp[16][106];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(&dp[0][0], &dp[15][106], numeric_limits<ll>::max());

    for(int a=0; a<10; a++)
        dp[1][line[a]] = min(dp[1][line[a]], (ll)a);
    for(int i=2; i<=15; i++) {
        for(int num=0; num<10; num++) {
            for(int j=0; j<=105; j++) {
                if(dp[i-1][j] == numeric_limits<ll>::max()) continue;
                dp[i][j+line[num]] = min(dp[i][j+line[num]], pow_10[i-1]*num + dp[i-1][j]);
            }
        }
    }

    string num; cin >> num;
    int numLen = (int)num.length(), lines = 0;
    ll val, res, ans = pow_10[numLen];
    for(int i=numLen-1, ri=0; i>=0; i--, ri++) {
        lines += line[num[i]-'0'];
        if(i>0) val = stoll(num.substr(0,i));
        else val = 0;
        for(int n=0; n<10; n++) {
            if(ri == 0) {
                if(line[n] != line[num[i]-'0']) continue;
                res = val*pow_10[ri+1] + n;
                if(res == stoll(num)) continue;
                ans = min(ans, (res + pow_10[numLen] - stoll(num)) % pow_10[numLen]);
            }
            else {
                res = dp[ri][lines - line[n]];
                if(res == numeric_limits<ll>::max()) continue;
                res = val*pow_10[ri+1] + n*pow_10[ri] + res;
                if(res == stoll(num)) continue;
                ans = min(ans, (res + pow_10[numLen] - stoll(num)) % pow_10[numLen]);
            }
        }
    }
    cout << ans << '\n';

    return 0;
}
```

### 후기
최근 접해본 dp문제 중에서 가장 난해했던 문제였던 것 같다. 생각하기도 어렵고 구현도 생각보다 까다로웠던 것 같다.

### 참고
https://blog.encrypted.gg/263