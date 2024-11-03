## [백준 11869 - 님블](https://www.acmicpc.net/problem/11869)

### 알고리즘
- 필승 전략 게임

### 풀이
님 게임과 같은 원리다.  
결국 동전을 한 칸씩 옮기는 행위는 돌더미에서 돌 한 개 이상을 제거하는 것과 같다.  
따라서 정사각형 칸의 번호를 하나의 돌더미의 돌 개수로 생각하면 된다.  
마지막 동전을 0으로 옮긴 사람 즉, 마지막 돌을 제거하는 사람이 승리이다.  
즉, nim 합이 0이 아니면 선공 필승, 0이라면 후공 필승이다.  

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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int M, res=0;
    cin >> M;
    while(M--) { int x; cin >> x; res ^= x; }
    if(res != 0) cout << "koosaga\n";
    else cout << "cubelover\n";

    return 0;
}
```