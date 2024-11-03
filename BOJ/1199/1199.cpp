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

int N;
int adj[1001][1001];
int nxt[1001], deg[1001];

void dfs(int here) {
    while(nxt[here] <= N) {
        int there = nxt[here];
        while(adj[here][there]) {
            adj[here][there]--;
            adj[there][here]--;
            dfs(there);
        }
        nxt[here]++;
    }
    cout << here << ' ';
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            cin >> adj[i][j];
            deg[i] += adj[i][j];
            deg[j] += adj[i][j];
        }
    }
    for(int i=1; i<=N; i++) {
        deg[i] /= 2;
        if(deg[i] % 2) {
            cout << "-1";
            return 0;
        }
    }
    dfs(1);
    return 0;
}