## [백준 10000 - 원 영역](https://www.acmicpc.net/problem/10000)

### 알고리즘
- 기하학
- 정렬
- dfs

### 풀이
1. 원의 왼쪽 끝 오름차순, 오른쪽 끝 내림차순으로 정렬한다.
2. 원의 자신의 직속 자식들(포함되어 있는 원)을 찾아서 그래프를 만든다.
3. dfs 탐색으로 현재 원의 직속 자식들의 원의 영역 개수들 다 더하고 직속 자식 원으로 현재 원이 분리되어 있다면 2를, 아니라면 1을 더해준다.
4. graph를 설정할 때 시간초과가 나지 않도록 마지막까지 확인한 원의 인덱스를 반환하여 바로 다음 원부터 시작할 수 있도록 한다.

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
vector<pii> circles;
vector<vector<int>> g;
vector<int> parent;

bool cmp(pii a, pii b) {
    if(a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}
int set_graph(int i) {
    for(int j=i+1; j<N; j++) {
        if(circles[i].second < circles[j].second) return j-1;
        g[i].emplace_back(j);
        parent[j] = i;
        j = set_graph(j);
    }
    return N-1;
}
int solve(int i) {
    int ret = 1;
    int loc = circles[i].first;
    for(int j : g[i]) {
        ret += solve(j);
        if(loc == circles[j].first) loc = circles[j].second;
    }
    return ret + (loc == circles[i].second);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    g.resize(N); parent.resize(N, -1);
    for(int i=0; i<N; i++) {
        int x, r; cin >> x >> r;
        circles.emplace_back(x-r,x+r);
    }
    sort(all(circles), cmp);
    for(int i=0; i<N; i++) i = set_graph(i);
    int ans = 1;
    for(int i=0; i<N; i++) {
        if(parent[i] != -1) continue;
        ans += solve(i);
    }
    cout << ans << '\n';

    return 0;
}
```