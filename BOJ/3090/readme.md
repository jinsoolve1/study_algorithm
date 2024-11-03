## [백준 3090 - 차이를 최소로](https://www.acmicpc.net/problem/3090)

### 알고리즘
- 이분탐색

### 풀이
1. 배열의 인접한 수의 차이의 최댓값을 S라 하자.    
   이 S를 이분탐색으로 찾는다.
2. possible(m) 을 했을 때, 배열의 S가 m이하가 될 수 있는 지를 확인한다.  
   먼저 인접한 오른쪽을 체크하고, 그 다음으로 인접한 왼쪽을 체크한다.
3. 주의해야 할 점은 possible 함수에서 cnt가 int 범위를 초과할 수 있으므로 long long으로 해줘야 한다.

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

int N, T;
vector<int> A, a, ans;

bool possible(int s) {
    ll cnt = 0;
    a.assign(all(A));
    for(int i=0; i<N-1; i++) {
        if(a[i + 1] - a[i] > s) {
            cnt += a[i + 1] - a[i] - s;
            a[i + 1] = a[i] + s;
        }
    }
    for(int i=N-1; i>0; i--) {
        if(a[i - 1] - a[i] > s) {
            cnt += a[i - 1] - a[i] - s;
            a[i - 1] = a[i] + s;
        }
    }
    return cnt <= T;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> T;
    A = vector<int>(N);
    for(int i=0; i<N; i++) cin >> A[i];

    int l=0, r=1e9, m;
    while(l<=r) {
        m = (l+r)/2;
        if(possible(m)) ans.assign(all(a)), r= m - 1;
        else l=m+1;
    }
    for(int x : ans) cout << x << ' ';
    cout << endl;

    return 0;
}
```

### 참고
https://jaimemin.tistory.com/987