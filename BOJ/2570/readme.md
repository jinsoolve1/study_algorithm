## [백준 2570 - 비숍2](https://www.acmicpc.net/problem/2570)

### 풀이
- 이분매칭

1. left 대각선과 right 대각선으로 나눌 수 있다.
2. left 대각선 -> right 대각선 을 잇는 edge는 비숍이 된다.
3. 각 left 대각선과 right 대각선은 한 번씩만 사용되어야 하므로 left->right의 최대 이분매칭이   
   결국 최대로 놓을 수 있는 비숍의 수가 된다.

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

struct Diagonal {
    int left, right;

    Diagonal() : left(-1), right(-1) {}
    Diagonal(int _left, int _right) : left(_left), right(_right) {}
};

int N, M;
int leftCnt, rightCnt;
Diagonal board[101][101];
bool obstacle[101][101];
int dx[] = {1, 1};
int dy[] = {-1, 1};

vector<int> parent;
vector<bool> capacity;
vector<vector<int>> g;

inline bool out_of_bound(int x, int y) { return x<1 || x>N || y<1 || y>N; }
void bishopLeftDown(int x, int y) {
    while(!out_of_bound(x,y) && !obstacle[x][y]) {
        board[x][y].left = leftCnt;
        x += dx[0], y += dy[0];
    }
    leftCnt++;
}
void bishopRightDown(int x, int y) {
    while(!out_of_bound(x,y) && !obstacle[x][y]) {
        board[x][y].right = rightCnt;
        x += dx[1], y += dy[1];
    }
    rightCnt++;
}
void bishopMove() {
    leftCnt = rightCnt = 0;
    for(int x=1; x<=N; x++) {
        for(int y=1; y<=N; y++) {
            if(obstacle[x][y]) continue;
            if(board[x][y].left == -1) bishopLeftDown(x,y);
            if(board[x][y].right == -1) bishopRightDown(x,y);
        }
    }
}
bool DFS(int here) {
    for(int there : g[here]) {
        if(capacity[there]) continue;
        capacity[there] = true;
        if(parent[there] == -1 || DFS(parent[there])) {
            parent[there] = here;
            return true;
        }
    }
    return false;
}
int bipartite() {
    fill(all(parent), -1);
    int ret = 0;
    for(int i=0; i<leftCnt; i++) {
        fill(all(capacity), 0);
        ret += DFS(i);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int x, y; cin >> x >> y;
        obstacle[x][y] = true;
    }
    bishopMove();

    // init
    parent.resize(rightCnt);
    capacity.resize(rightCnt);
    g.resize(leftCnt);

    for(int x=1; x<=N; x++) {
        for(int y=1; y<=N; y++) {
            if(obstacle[x][y]) continue;
            g[board[x][y].left].emplace_back(board[x][y].right);
        }
    }

    cout << bipartite() << '\n';

    return 0;
}
```