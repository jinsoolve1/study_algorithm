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

int N, M, Q;
vector<int> tm, idx;
vector<pii> sorted;
vector<vector<pii>> dist;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> Q;

    dist = vector<vector<pii>>(N+1, vector<pii>(N+1, pii(INF,0)));

    for(int i=1; i<=N; i++) {
        int x; cin >> x;
        sorted.emplace_back(x,i);
    }
    sort(all(sorted));
    tm.resize(N+1); idx.resize(N+1);
    for(int i=0; i<sorted.size(); i++) {
        tm[i+1] = sorted[i].first;
        idx[sorted[i].second] = i+1;
    }
    while(M--) {
        int a, b, d; cin >> a >> b >> d;
        a = idx[a], b = idx[b];
        dist[a][b] = dist[b][a] = pii(d,max(tm[a],tm[b]));
    }

    for(int k=1; k<=N; k++) {
        for(int i=1; i<=N; i++) {
            for(int j=1; j<=N; j++) {
                pii res = pii(dist[i][k].first + dist[k][j].first, max(dist[i][k].second, dist[k][j].second));
                if(dist[i][j].first + dist[i][j].second > res.first + res.second) dist[i][j] = res;
            }
        }
    }

    while(Q--) {
        int s, t; cin >> s >> t;
        s = idx[s], t = idx[t];
        if(dist[s][t].first == INF) cout << "-1\n";
        else cout << dist[s][t].first + dist[s][t].second << endl;
    }


    return 0;
}