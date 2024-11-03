## [코드포스 D - Slimes](https://codeforces.com/contest/1923/problem/D)

### 알고리즘
- 이분탐색

### 풀이
1. 현재 idx를 기준으로,  
   1. 1 ~ idx-1 을 이분탐색하여 psum[x ~ idx-1] 값이 a[idx]보다 커지면서도 가장 오른쪽 x를 찾는다.
   2. idx+1 ~ n 을 이분탐색하여 psum[idx+1 ~ x] 값이 a[idx]보다 커지면서도 가장 왼쪽 x를 찾는다.
2. 하지만 찾은 값의 범위가 모두 같은 수라면 안 된다.  
   - lloc[x] = y  
     a[y] != (a[y+1] == a[y+2] == ... == a[x]) 인 수를 의미한다.  
   - rloc[x] = y   
     (a[x] == a[x+1] == ... == a[y-1]) != a[y] 인 수를 의미한다.
3. lloc과 rloc을 이용해서 1,2번 조건 모두를 만족하는 위치를 반환한다.

### 배운 점
구현하는데 시간이 오래 걸렸다.  
이분탐색의 l, r의 등호 여부 등이 조금 헷갈렸다.  
lloc과 rloc을 이분탐색이 끝나고 적용해야 하는데 이분탐색을 하기 전에 하려 한 것이 문제인 듯 하다.

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

int n;
vector<ll> a, psum;
vector<int> lloc, rloc;

int binary_search_left(int idx) {
    if(idx == 1) return INF;
    int l = 1, r = idx-1;

    while(l<r) {
        int m = (l+r)/2 + (l+r)%2;
        ll sum = psum[idx-1] - psum[m-1];
        if(sum > a[idx]) l = m;
        else r = m-1;
    }
    if(l < idx-1 &&l > lloc[idx-1]) {
        l = lloc[idx-1];
        if(l == 0) return INF;
    }
    return (psum[idx-1] - psum[l-1] > a[idx] ? idx-l : INF);
}
int binary_search_right(int idx) {
    if(idx == n) return INF;
    if(a[idx] < a[idx+1]) return 1;
    int l = rloc[idx+1], r = n;
    if(l == n+1) return INF;

    while(l<r) {
        int m = (l+r)/2;
        ll sum = psum[m] - psum[idx];
        if(sum > a[idx]) r = m;
        else l = m+1;
    }
    if(r > idx+1 && r < rloc[idx+1]) {
        r = rloc[idx+1];
        if(r == n+1) return INF;
    }
    return (psum[r] - psum[idx] > a[idx] ? r-idx : INF);
}
int solve(int idx) {
    ll left_res = binary_search_left(idx);
    ll right_res = binary_search_right(idx);
    ll ret = min(left_res, right_res);
    return (ret == INF ? -1 : ret);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc; cin >> tc;
    while(tc--) {
        cin >> n;
        a = vector<ll>(n+1);
        psum = vector<ll>(n+1,0);
        lloc = vector<int>(n+1, 0);
        rloc = vector<int>(n+1, 0);
        for(int i=1; i<=n; i++) {
            cin >> a[i];
            psum[i] = psum[i-1] + a[i];
        }

        lloc[1] = 0;
        for(int i=2; i<=n; i++) {
            if(a[i] == a[i-1]) lloc[i] = lloc[i-1];
            else lloc[i] = i-1;
        }

        rloc[n] = n+1;
        for(int i=n-1; i>=1; i--) {
            if(a[i] == a[i+1]) rloc[i] = rloc[i+1];
            else rloc[i] = i+1;
        }

        for(int i=1; i<=n; i++) {
            cout << solve(i) << ' ';
        }
        cout << endl;
    }


    return 0;
}
```