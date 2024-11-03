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