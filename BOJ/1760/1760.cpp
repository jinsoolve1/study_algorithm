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