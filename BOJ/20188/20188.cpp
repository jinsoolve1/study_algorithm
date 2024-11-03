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

const int mxn = 3e5;
ll N;
vector<int> g[mxn+1];
ll treeSize[mxn+1], depth[mxn+1];

int makeTree(int here, int lv) {
    depth[here] = lv;
    int ret = 1;
    for(int there : g[here]) {
        if(depth[there] != -1) continue;
        ret += makeTree(there, lv+1);
    }
    return treeSize[here] = ret;
}
// here 노드가 LCS 역할을 하는 횟수
ll LCS(int here) {
    ll ret = 0;
    ll childNum = treeSize[here];
    for(int there : g[here]) {
        if(depth[there] < depth[here]) continue;
        ret += treeSize[there] * (childNum - treeSize[there]);
        childNum -= treeSize[there];
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N-1; i++) {
        int a, b; cin >> a >> b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    // make tree by root 1
    memset(treeSize, 0, sizeof treeSize);
    memset(depth, -1, sizeof depth);
    makeTree(1,0);

    // calculate the sum of diversity
    ll ans = 0;
    for(int i=1; i<=N; i++) {
        ans += (N-1)*depth[i];
        ans -= LCS(i)*depth[i];
    }
    cout << ans << '\n';

    return 0;
}