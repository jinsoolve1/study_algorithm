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
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int N, M;
vector<pii> g[101010];
pii parent[101010]; // first: sample number, second: difference

pii Find(int here) {
    if(here == parent[here].f) return parent[here] = pii(here, 0);
    pii update = Find(parent[here].f);
    return parent[here] = pii(update.f, parent[here].s + update.s);
}
void Union(int a, int b, int w) {
    Find(a);
    Find(b);
    int moveA = parent[a].s, moveB = parent[b].s;
    a = parent[a].f, b = parent[b].f;
    if(a == b) return;
    w = w + moveA - moveB;
    parent[b] = pii(a,w);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while(cin >> N >> M) {
        if(N==0 && M==0) break;
        // init
        for(int i=1; i<=N; i++) vector<pii>().swap(g[i]);
        for(int a=1; a<=N; a++) parent[a] = pii(a,0);

        while(M--) {
            char cmd; int a, b, w;
            cin >> cmd;
            if(cmd == '!') {
                cin >> a >> b >> w;
                Union(a,b,w);
            }
            else {
                cin >> a >> b;
                Find(a);
                Find(b);
                int moveA = parent[a].s, moveB = parent[b].s;
                a = parent[a].f, b = parent[b].f;
                if(a != b) cout << "UNKNOWN\n";
                else cout << moveB-moveA << '\n';
            }
        }
    }


    return 0;
}