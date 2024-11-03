## [백준 2631 - 줄세우기](https://www.acmicpc.net/problem/2631)

### 풀이
LCS를 찾아서 LCS에 포함되지 않는 아이들을 옮기면 해결되는 문제다.

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

int N;
vector<int> dp;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N; i++) {
        int x; cin >> x;
        auto it = lower_bound(all(dp), x);
        if(it == dp.end()) dp.emplace_back(x);
        else *it = x;
    }
    cout << N-dp.size() << '\n';


    return 0;
}
```