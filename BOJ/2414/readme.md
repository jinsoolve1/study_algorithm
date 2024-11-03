## [백준 2414 - 게시판 구멍 막기](https://www.acmicpc.net/problem/2414)

### 알고리즘
- 이분매칭
- 최소 버텍스 커버

### 풀이
1. (행 방향 테이프) -> (열 방향 테이프) 를 잇는 이분그래프를 만든다.
2. 이분 그래프의 edge는 뚤려있는 구멍이고, node는 테이프가 된다.
3. 최소 버텍스 커버. 즉, 모든 구멍을 지우는 테이프의 최소 개수가 정답이다.
4. 퀴니그 정리에 의해 최소 버텍스커버의 값은 이분 매칭의 값과 같다.

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

int N, M;
int row=1, col=1;
char board[50][50];
pii tape[50][50];
vector<vector<int>> g;
vector<bool> capacity;
vector<int> parent;

bool dfs(int here) {
    // 연결된 모든 노드에 대해서 들어갈 수 있는지 시도
    for(int there : g[here]) {
        // 이미 처리한 노드는 더 이상 볼 필요가 없음
        if(capacity[there]) continue;
        capacity[there] = true;
        if(parent[there] == 0 || dfs(parent[there])) {
            parent[there] = here;
            return true;
        }
    }
    return false;
}
int bipartite() {
    parent = vector<int>(col, 0);
    capacity = vector<bool>(col);
    int ans = 0;
    for(int i=1; i<row; i++) {
        fill(all(capacity), false);
        ans += dfs(i);
    }
    return ans;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    for(int i=0; i<N; i++) {
        string s; cin >> s;
        for(int j=0; j<M; j++) {
            board[i][j] = s[j];
        }
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(board[i][j] == '.') continue;
            if(j != 0 && board[i][j-1] == '*') tape[i][j].first = tape[i][j-1].first;
            else tape[i][j].first = row++;
        }
    }
    g = vector<vector<int>>(row);
    for(int j=0; j<M; j++) {
        for(int i=0; i<N; i++) {
            if(board[i][j] == '.') continue;
            if(i!=0 && board[i-1][j] == '*') tape[i][j].second = tape[i-1][j].second;
            else tape[i][j].second = col++;
            g[tape[i][j].first].emplace_back(tape[i][j].second);
        }
    }

    cout << bipartite() << endl;

    return 0;
}
```