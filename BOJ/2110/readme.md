## [백준 2110 - 공유기 설치](https://www.acmicpc.net/problem/2110)

### 풀이
- 가장 인접한 두 공유기 사이의 거리를 이분탐색으로 찾는다.  
- 이분탐색에서 찾고 있던 거리가 l이라고 하자.  
  가장 왼쪽에 있는 집부터 시작해서 거리가 l로 같거나 멀리 있는 집들로 이동하면서 총 C개 이상을 설치할 수 있다면 가능한 것이다.

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

int N, C;
vector<int> V;

bool check(int len) {
    auto it = V.begin();
    int cnt = 0;
    while(it != V.end()) {
        it = lower_bound(it+1,V.end(),*it+len);
        if(++cnt >= C) return true;
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> C;
    for(int i=0; i<N; i++) {
        int x; cin >> x;
        V.emplace_back(x);
    }
    sort(all(V));
    int l=0, r=1e9;
    while(l<=r) {
        int m = (l+r)/2;
        if(check(m)) l=m+1;
        else r=m-1;
    }
    cout << r << '\n';

    return 0;
}
```