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

int C, D, V;
vector<pii> catLover, dogLover; //(like, dislike)

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
    parent = vector<int>(dogLover.size(), -1);
    capacity = vector<bool>(dogLover.size());
    int ans = 0;
    for(int i=0; i<catLover.size(); i++) {
        fill(all(capacity), false);
        ans += dfs(i);
    }
    return ans;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        catLover.resize(0); dogLover.resize(0);
        cin >> C >> D >> V;
        for(int i=0; i<V; i++) {
            string u, v; cin >> u >> v;
            if(u.front() == 'C') catLover.emplace_back(stoi(u.substr(1)), stoi(v.substr(1)));
            else dogLover.emplace_back(stoi(u.substr(1)), stoi(v.substr(1)));
        }

        g = vector<vector<int>>(catLover.size());
        for(int i=0; i<catLover.size(); i++) {
            for(int j=0; j<dogLover.size(); j++) {
                if(catLover[i].first == dogLover[j].second || catLover[i].second == dogLover[j].first) g[i].emplace_back(j);
            }
        }
        cout << V - bipartite() << endl;
    }

    return 0;
}