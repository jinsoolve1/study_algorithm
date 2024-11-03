## [백준 1514 - 자물쇠](https://www.acmicpc.net/problem/1514)

### 알고리즘
- 다이나믹 프로그래밍

### 풀이
1. dp[idx][n1][n2][n3] := (현재 [idx, idx+1, idx+2]의 숫자가 [n1, n2, n3]일 때 target[idx~]와 동일하게 되도록 하는 최소 횟수) 이라 하자.
2. 시계, 반시계 방향으로 최대 3칸, 연속되어 있는 최대 3개의 디스크를 돌릴 수 있다. 디스크를 한 번 돌린다고 가정할 때 다음과 같은 경우의 수가 발생한다.
   1. n1 == target[idx]이라면 돌리지 않고 다음 idx로 넘기기
   2. idx 디스크만 돌리기
   3. idx, idx+1 디스크 돌리기
   4. idx, idx+1, idx+2 디스크 돌리기
3. 마지막 idx == n이 되면 0을 반환한다.

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

int N;
vector<int> current, target;
int dp[100][10][10][10];


vector<int> get_stovi() {
    string s; cin >> s;
    vector<int> ret;
    for(char c : s) ret.emplace_back(c-'0');
    return ret;
}
int rotate(int x, int mv) { return (x + mv + 10) % 10; }
int solve(int idx, int n1, int n2, int n3) {
    if(idx == N) return 0;

    int &ret = dp[idx][n1][n2][n3];
    if(ret != -1) return ret;

    ret = INF;
    if(n1 == target[idx]) ret = min(ret, solve(idx+1, n2, n3, current[idx+3]));
    for(int i=-3; i<=3; i++)
        if(i) ret = min(ret, solve(idx, rotate(n1,i), n2, n3) + 1);
    for(int i=-3; i<=3; i++)
        if(i) ret = min(ret, solve(idx, rotate(n1,i), rotate(n2,i), n3) + 1);
    for(int i=-3; i<=3; i++)
        if(i) ret = min(ret, solve(idx, rotate(n1,i), rotate(n2,i), rotate(n3,i)) + 1);

    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);

    cin >> N;
    current = get_stovi(); current.emplace_back(0); current.emplace_back(0); current.emplace_back(0);
    target = get_stovi();

    cout << solve(0, current[0], current[1], current[2]);

    return 0;
}
```