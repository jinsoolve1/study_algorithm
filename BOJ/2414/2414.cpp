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