## [백준 13034 - 다각형 게임](https://www.acmicpc.net/problem/13034)

### 알고리즘
- 게임 이론
- 스프라그-그런디 정리

### 풀이
스프라그-그런디 정리를 이용하여 문제를 해결한다.  
현재 게임 상태가 x(x꼭짓점 다각형)일 때, 다각형의 두 점을 선택하고 나눠진 좌우 다각형의 꼭짓점 개수를 y, z라 하자. (y+z = x-2)  
dp[x] = mew({ dp[y]^dp[z] | y=0~x-2, z=x-2-y } )이 된다.  
모든 y, z에 대한 dp[y]^dp[z]의 집합을 s라 할 때, mew(s)는 집합 s에 속하지 않는 정수 중 가장 작은 정수가 된다.

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

int N;
int dp[1001];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, 0, sizeof dp);

    cin >> N;
    for(int x=2; x<=N; x++) {
        set<int> s;
        for(int y=0; y<=x-2; y++) s.insert(dp[y]^dp[x-2-y]);
        while(s.count(dp[x])) dp[x]++;
    }
    cout << (dp[N] ? 1 : 2) << endl;

    return 0;
}
```

### 참고
https://blog.naver.com/PostView.naver?blogId=jinhan814&logNo=222729302576&categoryNo=11&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView