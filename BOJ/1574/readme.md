## [백준 1574 - 룩 어택](https://www.acmicpc.net/problem/1574)

### 알고리즘
- 이분매칭

### 풀이
1. 행 -> 열 의 이분그래프를 구성하는데, edge는 룩이 된다.
2. 빈칸을 제외한 나머지 칸들에는 룩을 놓을 수 있으므로 edge로 추가해준다.
3. 행 -> 열의 최대 이분매칭의 값을 출력하면 정답이다.

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

class BipartiteMatching {
private:
    int ln, rn; // (1~ln) -> (1~rn) bipartite graph
    vector<vector<int>> g; // g[1~ln]
    vector<bool> visited; // visited[1~ln]
    vector<int> parent; // parent[1~rn]

public:
    BipartiteMatching() {}
    BipartiteMatching(int _ln, int _rn) : ln(_ln), rn(_rn), g(_ln+1), visited(_ln+1), parent(_rn+1) {}
    ~BipartiteMatching() { this->clear(); }
    void clear() {
        for(int i=1; i<=ln; i++) g[i].clear();
    }
    void add_edge(int u, int v) { g[u].emplace_back(v); }
    bool dfs(int here) {
        // 이미 처리한 노드는 더 이상 볼 필요가 없음
        if(visited[here]) return false;
        visited[here] = true;

        // 연결된 모든 노드에 대해서 들어갈 수 있는지 시도
        for(int there : g[here]) {
            if(parent[there] == -1 || dfs(parent[there])) {
                parent[there] = here;
                return true;
            }
        }
        return false;
    }
    int matching() {
        fill(all(parent), -1);
        int ret = 0;
        for(int i=1; i<=ln; i++) {
            fill(all(visited), false);
            ret += dfs(i);
        }
        return ret;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int R, C, N; cin >> R >> C >> N;
    bool blank[301][301]; memset(blank, 0, sizeof blank);
    while(N--) {
        int r, c; cin >> r >> c;
        blank[r][c] = true;
    }
    BipartiteMatching bi(R,C);
    for(int r=1; r<=R; r++) {
        for(int c=1; c<=C; c++) {
            if(!blank[r][c]) bi.add_edge(r,c);
        }
    }
    cout << bi.matching() << endl;

    return 0;
}
```