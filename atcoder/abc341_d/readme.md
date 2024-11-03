## [atcoder abc341_g Only one of two](https://atcoder.jp/contests/abc341/tasks/abc341_d)

### 알고리즘
- 수학, 최소공배수

### 풀이
(N의 배수 개수) + (M의 배수 개수) - 2x(NM의 최소공배수의 배수 개수) == K 가 되면 된다.

어떤 숫자 X가 정답이 되려면,  
cnt = X/N + X/M - 2*(X / (NM 최소공배수))이라 하자.  
이 cnt가 K가 되는 최소의 X를 구하면 된다.  

( 필자는 여기서 NM의 최소공배수를 구하지 않고 그냥 N*M을 해버려서 헤맸다 )

최소공배수는 N * M / gcd(N,M)으로 구하면 된다.  
X는 이분탐색으로 찾으면 된다.  
그럼 최종 시간복잡도는 $O(log(10^{18}))$이 된다.

### 코드
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
using ll = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

ll N, M, K;

ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(b, a%b);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;
    ll NM = N * M / gcd(N,M);
    ll lo=1, hi=numeric_limits<ll>::max();
    while(lo < hi) {
        ll mid = lo + (hi-lo)/2;
        ll cnt = mid/N + mid/M - 2*(mid/NM);
        if(K <= cnt) hi = mid;
        else lo = mid+1;
    }
    cout << hi << endl;

    return 0;
}
```