## [백준 18138 - 리유나는 세일러복을 좋아해](https://www.acmicpc.net/problem/18138)

### 알고리즘
- 이분매칭

### 풀이
이분매칭으로 해결할 수 있다.  
티셔츠(t) -> 카라(c) 연결하는 이분매칭을 생각할 때, 4c가 [2t,3t] or [4t,5t] 범위 안에 있으면 t->c 는 연결된다.  
해당 그래프를 기준으로 이분매칭 알고리즘을 구현하면 쉽게 풀린다.

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

    int N, M; cin >> N >> M;
    vector<int> shirts(N+1), collar(M+1);
    for(int i=1; i<=N; i++) cin >> shirts[i];
    for(int i=1; i<=M; i++) cin >> collar[i];

    BipartiteMatching bi(N,M);
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(2*shirts[i] <= 4*collar[j] && 4*collar[j] <= 3*shirts[i]) bi.add_edge(i,j);
            else if(4*shirts[i] <= 4*collar[j] && 4*collar[j] <= 5*shirts[i]) bi.add_edge(i,j);
        }
    }
    cout << bi.matching() << endl;

    return 0;
}
```