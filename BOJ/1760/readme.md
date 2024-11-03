## [백준 1760 - N-Rook](https://www.acmicpc.net/problem/1760)

### 알고리즘
- 이분매칭

### 풀이
1. 행 방향과 열 방향으로 각각 탐색하면서 한 구간으로 만들 수 있는 것을 이어 번호를 붙인다.  
   만약 벽이 있어 나눠지면 다음 번호를 주어 이어서 탐색하면 된다.
2. 벽은 나누기만 하면 되지만 구덩이라는 특수한 장치가 있는데, 구덩이는 빈칸처럼 취급해서 한 구간으로 이을 수 있도록 번호를 매긴다.  
   다만, 룩은 빈칸에만 놓을 수 있으므로 edge는 빈칸에서만 생성한다.  
   이렇게 하면 구덩이가 포함된 행과 열에는 최대 1개의 룩만 존재할 수 있다.

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

int N, M;
int grid[101][101];
int row[101][101], col[101][101];
int rowNum=0, colNum=0;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    for(int i=1; i<=N; i++)
        for(int j=1; j<=M; j++)
            cin >> grid[i][j];

    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(j==1 || grid[i][j-1]==2) row[i][j] = ++rowNum;
            else row[i][j] = row[i][j-1];
        }
    }
    for(int j=1; j<=M; j++) {
        for(int i=1; i<=N; i++) {
            if(i==1 || grid[i-1][j]==2) col[i][j] = ++colNum;
            else col[i][j] = col[i-1][j];
        }
    }

    BipartiteMatching bi(rowNum, colNum);
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++)
            if(grid[i][j] == 0) bi.add_edge(row[i][j], col[i][j]);
    cout << bi.matching() << endl;

    return 0;
}
```