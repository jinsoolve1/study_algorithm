## [백준 1943 - 동전분배](https://www.acmicpc.net/problem/1943)

### 풀이
knapsack 알고리즘을 사용한다.  
- dp[amount]:= (amount를 만들 수 있는가)
- 동전을 하나씩 사용해서 money를 만들고 dp[money] = true라고 기록해준다.  
  동전이 하나씩 추가될 때마다 해당 동전은 이전 동전들 모두의 조합을 이용하여 money를 만든다.
- 따라서 dp[total/2] 가 정답이 된다.

### 후기 
처음엔 recursion으로 풀었는데 찾아보니 main함수에서 반복문 돌리는 것이 더 효율적이다.  
dp를 반복문으로만 해결하는 방법에 익숙해질 필요가 있을 듯 하다.

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
#define Flow first
#define s second
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int N;
vector<pii> coin;
bool dp[50101];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int _=0; _<3; _++) {
        memset(dp, 0, sizeof dp);
        coin.resize(0);
        int total = 0;
        cin >> N;
        for(int i=0; i<N; i++) {
            int a,b; cin >> a >> b;
            total += a*b;
            coin.emplace_back(a,b);
        }
        if(total % 2 == 1) {
            cout << 0 << '\n';
            continue;
        }
        dp[0] = true;
        for(int idx=0; idx<N; idx++) {
            for(int amount = total/2; amount >= coin[idx].Flow; amount--) {
                if(dp[amount - coin[idx].Flow]) {
                    for(int cnt = 0; cnt < coin[idx].s; cnt++) {
                        if(amount + cnt*coin[idx].Flow > total/2) break;
                        dp[amount + cnt*coin[idx].Flow] = true;
                    }
                }
            }
        }
        cout << dp[total/2] << '\n';
    }

    return 0;
}
```
