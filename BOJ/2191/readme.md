## [백준 2191 - 들쥐의 탈출](https://www.acmicpc.net/problem/2191)

### 알고리즘
- 이분매칭
- 기하학

### 풀이
1. 각 쥐가 초속 V로 S초 안에 들어갈 수 있는 동굴들과의 연결 그래프를 만든다.
2. 이분매칭을 이용해서 최대 몇 마리의 쥐가 S초 안에 동굴 안에 들어갈 수 있는 지 구한다.
3. 전체 N마리에서 최대 이분매칭 값을 빼준 값이 정답이다.

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
using pdd = pair<double, double>;
using ti3 = tuple<int, int, int>;

int N, M, S, V;
vector<pdd> rats, caves;
vector<int> g[100];
int parent[100];
bool capacity[100];

double cal_dist(pdd a, pdd b) { return sqrt(pow(a.first-b.first,2) + pow(a.second-b.second,2)); }
bool dfs(int here) {
    for(int there : g[here]) {
        if(capacity[there]) continue;
        capacity[there] = true;
        if(parent[there] == -1 || dfs(parent[there])) {
            parent[there] = here;
            return true;
        }
    }
    return false;
}
int bipartite() {
    memset(parent, -1, sizeof parent);
    int ret = 0;
    for(int i=0; i<N; i++) {
        memset(capacity, 0, sizeof capacity);
        ret += dfs(i);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> S >> V;
    for(int i=0; i<N; i++) {
        double x, y; cin >> x >> y;
        rats.emplace_back(x,y);
    }
    for(int i=0; i<M; i++) {
        double x, y; cin >> x >> y;
        caves.emplace_back(x,y);
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(cal_dist(rats[i], caves[j]) <= V*S) g[i].emplace_back(j);
        }
    }
    cout << N - bipartite() << '\n';

    return 0;
}
```