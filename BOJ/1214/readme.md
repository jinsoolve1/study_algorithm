## [백준 1214 - 쿨한 물건 구매](https://www.acmicpc.net/problem/1214)

### 알고리즘
- 수학(정수론)
- 브루트포스

### 풀이
d <= px + qy라 하자.  

1. x는 q보다 크거나 같을 필요가 없다. => x < q  
   x = qz + x'(0 <= x' < q)일 때,  
   px + qy = px' + q(pz+y)이므로 x는 q이상일 필요가 없다. (y의 개수를 늘리는 것으로 대체 가능하므로)
2. px가 d+p보다 크거나 같을 필요가 없다. => px < d+p  
   [d, d+p) 구간에 p의 배수가 최소한 하나 존재하므로 px < d+p 까지만 탐색하면 된다.
3. p가 클수록 탐색 반복 횟수가 줄어든다. 따라서 항상 p > q가 되도록 값을 바꿔준다.

해당 x들에 대하여, d-px <= qy를 성립시키는 가장 작은 y를 찾는다.  
ans = min(ans, px + qy)로 ans를 업데이트 시켜준다.

시간복잡도에 대해서 살펴보자.  
결국 x는 min((d+p)/p, q)번 만큼 반복한다.  
하지만 p > q이므로 최악의 경우, O(sqrt(N))이 된다.

p가 sqrt(N)보다 클 경우, (d+p)/p가 sqrt(N)보다 작아진다.  
반면 p가 sqrt(N)보다 작을 경우, (d+p)/p는 sqrt(N)보다 커지지만 q가 p보다 항상 작으므로 q는 sqrt(N)보다 작아진다.  
따라서 O(sqrt(N))가 된다.

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

ll d, p, q;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> d >> p >> q;
    if(p < q) swap(p,q);

    ll ans = numeric_limits<ll>::max();
    // d <= px + qy, x = 0 ~ q-1
    for(ll x=0; x<q && p*x<d+p; x++) {
        ll y = (d - p*x + q-1) / q;
        ans = min(ans, p*x + q*y);
    }
    cout << ans << endl;

    return 0;
}
```

### 참고
https://blog.encrypted.gg/417