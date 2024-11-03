## [코드포스 C - Find B](https://codeforces.com/contest/1923/problem/C)

### 알고리즘
- 수학

### 풀이
1. 주어진 부분 배열에서 모든 1들은 2로, 나머지 숫자들은 1로 바꾼다.
2. 변경된 부분 배열의 합을 minVal이라 하자.
3. 만약 원래의 부분 배열의 합이 minVal보다 작다면 무슨 짓을 해도 불가능하다.
4. 아니라면 가능하다.  
   만약 값이 minVal과 같다면, 변경된 부분 배열이 정답이 될 것이고,  
   만약 다르다면 몇 개의 값을 기존 부분배열과 다르게 값을 변경하면 해결되기 때문이다.

### 배운 점
너무 세세하게 생각하기보다는 좀 크게 생각할 필요가 있는 것 같다.  
반례가 생길 것 같다고 너무 신경쓰기 보다는 논리를 우선 생각해보자.

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

int n, q;
vector<int> cnt;
vector<ll> psum;

string solve(int l, int r) {
    if(l == r) return "NO";
    ll minVal = 2ll*(cnt[r]-cnt[l-1]) + ( r-l+1 - (cnt[r]-cnt[l-1]) ); // all 1s -> 2, other numbers -> 1
    if(psum[r]-psum[l-1] < minVal) return "NO";
    else return "YES";
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc; cin >> tc;
    while(tc--) {
        cin >> n >> q;

        cnt = vector<int>(n+1,0);
        psum = vector<ll>(n+1, 0);
        for(int i=1; i<=n; i++) {
            ll x; cin >> x;
            psum[i] = psum[i-1] + x;
            cnt[i] = cnt[i-1] + (x==1);
        }

        while(q--) {
            int l, r; cin >> l >> r;
            cout << solve(l,r) << endl;
        }
    }


    return 0;
}
```