## [atcoder abc319 - C : False Hope](https://atcoder.jp/contests/abc319/tasks/abc319_c)

### 알고리즘
- 구현
- 순열

### 풀이
생각 자체는 쉬우나, 구현하는 부분이 조금 까다로울 수 있다. 

order[i] := grid[i]가 보여지는 순서  
vector\<tuple\> line에는 가능한 모든 라인들을 집어 넣자

next_permutation을 이용해서 가능한 모든 순서 중에서 문제에서 말한 조건에 만족하는 경우들의 개수를 구한 후, 9! 로 나누면 정답이다.

즉, 한 주어진 순서에 대해서 모든 line이 조건을 만족하는 지 체크하는 문제다.

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

const double MAX = 362880;
int grid[9];
vector<ti3> line {
        {0,1,2}, {3,4,5}, {6,7,8}, // horizontal
        {0,3,6}, {1,4,7}, {2,5,8}, // vertical
        {0,4,8}, {2,4,6} // diagonal
};
vector<int> order{1,2,3,4,5,6,7,8,9};

bool check() {
    for(auto &l : line) {
        int a = get<0>(l), b = get<1>(l), c = get<2>(l);
        if(grid[a] == grid[b] && order[a] < order[c] && order[b] < order[c]) return false;
        else if(grid[b] == grid[c] && order[b] < order[a] && order[c] < order[a]) return false;
        else if(grid[c] == grid[a] && order[c] < order[b] && order[a] < order[b]) return false;
    }
    return true;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cout << fixed; cout.precision(8);

    for(int i=0; i<9; i++) cin >> grid[i];

    double ans = 0;
    do {
        ans += check();
    } while(next_permutation(all(order)));
    cout << ans / MAX << endl;

    return 0;
}
```
