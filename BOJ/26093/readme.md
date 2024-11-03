## [백준 26093 - 고양이 목에 리본 달기](https://www.acmicpc.net/problem/26093)

### 풀이 
결국 고양이가 영향을 받을 수 있는 고양이 수는 최대 2마리다.(좌,우)  
따라서 각 고양이마다 가장 만족감을 주는 리본 3개만 저장하면 된다.  
어떤 고양이의 첫번째로 만족감을 주는 리본과 두번째로 만족감을 주는 리본을 양 옆에서 모두 쓰고 있다고 가정할 때, 그 고양이는 3번째로 만족감을 주는 리본을 고르면 되기 때문이다.

### 후기
처음엔 고양이를 차례대로 보고 있다고 가정할 때 앞의 고양이 리본만 신경쓰면 된다고 생각해서 2개의 리본만 저장했다.  
하지만 이 방법은 만약 최적의 해가 양 옆의 고양이로 인해 3번째로 만족감을 주는 리본을 필요로 할 경우를 간과했다.

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
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int N, K;
pii ribbon[100][3]; //ribbon[cat] = (ribbon's idx, satisfy)
int dp[100][4];

int solve(int cat, int used) {
    if(cat == N) return 0;
    int color;
    for(color=0; color<3; color++) {
        if(used == ribbon[cat][color].first) break;
    }
    int &ret = dp[cat][color];
    if(ret != -1) return ret;
    if(color != 0) ret = max(ret, solve(cat+1, ribbon[cat][0].first) + ribbon[cat][0].second);
    if(color != 1) ret = max(ret, solve(cat+1, ribbon[cat][1].first) + ribbon[cat][1].second);
    if(color != 2) ret = max(ret, solve(cat+1, ribbon[cat][2].first) + ribbon[cat][2].second);
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);

    cin >> N >> K;
    for(int i=0; i<N; i++) {
        ribbon[i][0] = ribbon[i][1] = ribbon[i][2] = pii(-1,0);
        for(int j=0; j<K; j++) {
            int x; cin >> x;
            if(ribbon[i][0].second < x) {
                ribbon[i][2] = ribbon[i][1];
                ribbon[i][1] = ribbon[i][0];
                ribbon[i][0] = pii(j,x);
            }
            else if(ribbon[i][1].second < x) {
                ribbon[i][2] = ribbon[i][1];
                ribbon[i][1] = pii(j,x);
            }
            else if(ribbon[i][2].second < x) ribbon[i][2] = pii(j,x);
        }
    }
    cout << solve(0,-1) << '\n';


    return 0;
}
```