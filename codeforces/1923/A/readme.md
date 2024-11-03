## [코드포스 A - Moving Chips](https://codeforces.com/contest/1923/problem/A)

### 알고리즘
- 구현

### 풀이
1. 가장 오른쪽 1의 위치를 i라 하자.
2. i보다 왼쪽에 있는 0 중 가장 오른쪽의 위치를 j라 하자.  
   못 찾았다면, 더 이상 옮길 수 없다.
3. j보다 왼쪽에 1이 없다면 더 이상 옮길 필요가 없다.
4. 2,3 조건을 모두 통과했다면 i,j 값을 swap 해준다.
5. 이를 반복하는 횟수가 정답이 된다.

### 배운 내용
코드포스 A번은 생각보다 쉬우니 naive하게 생각해도 좋다.

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
vector<int> v;

bool solve(vector<int>& cells) {
    int i, j, k;
    for(i=n-1; i>=0; i--)
        if(cells[i] == 1) break;
    for(j=i-1; j>=0; j--)
        if(cells[j] == 0) break;
    if(j == -1) return false;
    for(k=j-1; k>=0; k--)
        if(cells[k] == 1) break;
    if(k == -1) return false;
    swap(cells[i], cells[j]);
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t; cin >> t;
    while(t--) {
        cin >> n;
        v = vector<int>(n);
        for(int i=0; i<n; i++) cin >> v[i];
        int ans = 0;
        while(solve(v)) ans++;
        cout << ans << endl;
    }


    return 0;
}
```