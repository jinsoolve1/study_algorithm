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
#define f first
#define s second
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

ll N,M;
vector<pll> g[101010];
ll dist[101010];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dist, -1, sizeof dist);

    cin >> N >> M;
    for(ll i=1; i<=M; i++) {
        ll a,b; cin >> a >> b;
        g[a].emplace_back(b,i);
        g[b].emplace_back(a,i);
    }
    queue<pll> q;
    dist[1] = 0;
    q.emplace(1, 0);
    while(!q.empty()) {
        ll here = q.front().f, curDist = q.front().s;
        q.pop();
        if(dist[here] < curDist) continue;
        for(pll edge : g[here]) {
            ll there = edge.f, len = edge.s;
            ll nextDist = M*((dist[here]-len+M)/M) + len;
            if(dist[there] != -1 && dist[there] <= nextDist) continue;
            dist[there] = nextDist;
            q.emplace(there, nextDist);
        }
    }
    cout << dist[N] << '\n';

    return 0;
}