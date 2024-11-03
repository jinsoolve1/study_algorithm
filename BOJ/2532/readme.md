## [백준 2532 - 먹이사슬](https://www.acmicpc.net/problem/2532)

### 알고리즘
- LIS(Longest Increasing Subsequence)

### 풀이
1. r 내림차순, l 오름차순으로 정렬한다.
2. l, r이 똑같은 동물은 셀 필요가 없으므로 삭제해준다.
3. 정렬한 순서대로 l의 LIS를 구한다. 이때 중복이 가능하도록 해준다.  
   이분탐색을 이용한 LIS로 구현해야 시간 초과가 나오지 않는다.

예를 들어,  
5  
1 0 10  
2 0 5  
3 3 10  
4 3 4  
5 2 5  
입력이 들어왔다고 했을 때, 정렬한 결과는 다음과 같다.  
1 0 10  
3 3 10  
2 0 5  
5 2 5  
4 3 4  
중복을 허용한 l의 LIS는 0, 0, 2, 3 이 된다. 즉, {1->2->5->4} 가 가장 큰 먹이사슬 구조가 된다.

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

bool cmp(pii a, pii b) {
    if(a.second == b.second) return a.first < b.first;
    return a.second > b.second;
}
int n;
vector<pii> v;
vector<int> lis;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for(int i=0; i<n; i++) {
        int j, l, r; cin >> j >> l >> r;
        v.emplace_back(l,r);
    }
    sort(all(v), cmp); v.erase(unique(all(v)), v.end());
    for(pii x : v) {
        auto it = upper_bound(all(lis), x.first);
        if(it == lis.end()) lis.emplace_back(x.first);
        else *it = x.first;
    }
    cout << lis.size() << '\n';

    return 0;
}
```