## [코드포스 B - Monsters Attack!](https://codeforces.com/contest/1923/problem/B)

### 풀이
1. 거리를 절댓값으로 바꾸고 (거리, 체력)을 넣어서 오름차순 정렬한다.
2. 매 거리마다 현재 남은 총알 + 이전시간에서부터 얻을 수 있는 총알이 죽여야할 체력보다 큰지를 확인한다.
3. 만약 작다면 불가능이고, 계속 그렇지 않다면 가능을 반환하면 된다.

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

ll n, k;
vector<ll> a, x;
vector<pll> v;

string solve() {
    ll tm = 0, bullet = 0;
    for(auto &val : v) {
        bullet += (val.first - tm) * k; tm = val.first;
        bullet -= val.second;
        if(bullet < 0) return "NO";
    }
    return "YES";
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc; cin >> tc;
    while(tc--) {
        cin >> n >> k;
        a.resize(n+1); x.resize(n+1); v.resize(0);
        for(int i=1; i<=n; i++) cin >> a[i];
        for(int i=1; i<=n; i++) cin >> x[i];
        for(int i=1; i<=n; i++) v.emplace_back(abs(x[i]), a[i]);
        sort(all(v));

        cout << solve() << endl;
    }


    return 0;
}

```