## [백준 9577 - 토렌트](https://www.acmicpc.net/problem/9577)

### 알고리즘
- 이분매칭

### 풀이
1. 왼쪽 노드: (전송 완료 시각), 오른쪽 노드: (조각), 왼쪽->오른쪽 간선: (사용자들별로 매칭 가능한 조각들)  
   위와 같이 구성된 이분 그래프에서 최대 매칭을 한다.
2. 주의할 점은 전송이 끝나고 난 시각이 왼쪽 노드들이므로  
   t1, t2가 주어지면 t1+1 ~ t2 에게 사용자들에게 주어진 조각들을 추가해야 한다.
3. 만약 매칭의 개수가 조각의 총 개수인 n과 같아지는 시각이 나오면 해당 시각을 반환한다.  
   만약 모든 시간(1 ~ 100)을 탐색했는데도 n개보다 작다면 -1을 반환한다.

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
            if(ret == rn) return i;
        }
        return -1;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        int n, m; cin >> n >> m;
        BipartiteMatching bi(100,n);
        while(m--) {
            int t1, t2, a; cin >> t1 >> t2 >> a;
            while(a--) {
                int q; cin >> q;
                for(int t=t1+1; t<=t2; t++) bi.add_edge(t,q);
            }
        }
        cout << bi.matching() << endl;
    }


    return 0;
}
```

### 참고
https://jason9319.tistory.com/171