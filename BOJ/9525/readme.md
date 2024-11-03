## [백준 9525 - 룩 배치하기](https://www.acmicpc.net/problem/9525)

### 알고리즘
- 이분매칭

### 풀이
1. 행 방향 혹은 열 방향으로 움직일 떄, 막히지 않고 움직일 수 있는 구간을 하나의 행 혹은 열로 여기자.
2. ..X..이면, 11022 가 된다. 열 방향도 마찬가지로 번호를 매긴다.
3. 행 -> 열 로의 그래프를 만든다.
4. 최대 이분매칭을 구한다.
5. 쾨니그 정리에 의해, 최소 버텍스 커버의 값은 최대 이분매칭 값과 같다.  
   각 노드는 새로운 행, 열 번호가 되고 노드 들을 잇는 간선은 룩이 된다.  
   따라서, 가능한 룩의 최대 개수는 행과 열 노드들의 최소 버텍스 커버가 된다.

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

int N;
char board[100][100];
int row[100][100], col[100][100];
int row_sz=1, col_sz=1;

vector<vector<int>> g;
vector<bool> capacity;
vector<int> parent;

bool dfs(int here) {
    // 연결된 모든 노드에 대해서 들어갈 수 있는지 시도
    for(int there : g[here]) {
        // 이미 처리한 노드는 더 이상 볼 필요가 없음
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
    parent = vector<int>(col_sz, -1);
    capacity = vector<bool>(col_sz);
    int ans = 0;
    for(int i=1; i<row_sz; i++) {
        fill(all(capacity), false);
        ans += dfs(i);
    }
    return ans;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(row, 0, sizeof row); memset(col, 0, sizeof col);

    cin >> N;
    for(int i=0; i<N; i++) {
        string s; cin >> s;
        for(int j=0; j<N; j++) {
            board[i][j] = s[j];
        }
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(board[i][j] == 'X') continue;
            if(j==0 || board[i][j-1]=='X') row[i][j] = row_sz++;
            else row[i][j] = row[i][j-1];
        }
    }

    g = vector<vector<int>>(row_sz);
    for(int j=0; j<N; j++) {
        for(int i=0; i<N; i++) {
            if(board[i][j] == 'X') continue;
            if(i==0 || board[i-1][j]=='X') col[i][j] = col_sz++;
            else col[i][j] = col[i-1][j];
            g[row[i][j]].emplace_back(col[i][j]);
        }
    }

     cout << bipartite() << endl;

    return 0;
}
```