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

const int mxn = 1e4+1;

struct type {
    int u, v, w;
};
struct cmp {
    bool operator()(type a , type b) {
        return a.w > b.w;
    }
};

int N, P;
int startCost;
int city[mxn];
int parent[mxn];
priority_queue<type, vector<type>, cmp> pq;

int find(int i) {
    if(i == parent[i]) return i;
    return parent[i] = find(parent[i]);
}
bool merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    parent[b] = a;
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i=0; i<mxn; i++) parent[i] = i;
    cin >> N >> P;
    startCost = INF;
    for(int i=1; i<=N; i++) {
        cin >> city[i];
        startCost = min(startCost, city[i]);
    }
    for(int i=1; i<=P; i++) {
        int s, e, l; cin >> s >> e >> l;
        pq.push({s,e,l*2+city[s]+city[e]});
    }
    ll ans = startCost;
    while(!pq.empty()) {
        type val = pq.top(); pq.pop();
        if(!merge(val.u, val.v)) continue;
        ans += val.w;
    }
    cout << ans << '\n';

    return 0;
}