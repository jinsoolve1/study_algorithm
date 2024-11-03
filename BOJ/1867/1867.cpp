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
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

const int mxn = 500;
int n, k;
vector<int> g[mxn+1];
bool capacity[mxn+1];
int parent[mxn+1];

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
    memset(parent, 0, sizeof parent);
    int ans = 0;
    for(int i=1; i<=n; i++) {
        memset(capacity, 0, sizeof capacity);
        ans += dfs(i);
    }
    return ans;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    while(k--) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
    }
    cout << bipartite() << '\n';


    return 0;
}