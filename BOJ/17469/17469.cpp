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

int N, Q;
vector<int> parent, color, p;
vector<set<int>> sets;
vector<pii> querys;
vector<int> ans;

int f(int i) {
    if(p[i] == i) return i;
    return p[i] = f(p[i]);
}
bool merge(int a, int b) {
    a = f(a), b = f(b);
    if(a == b) return false;
    if(sets[a].size() < sets[b].size()) swap(a, b);
    p[b] = a;
    for(auto x : sets[b]) sets[a].insert(x);
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> Q;
    parent = vector<int>(N+1), p = vector<int>(N+1);

    parent[1] = 1;
    for(int i=2; i<=N; i++) cin >> parent[i];
    for(int i=1; i<=N; i++) p[i] = i;

    sets = vector<set<int>>(N+1);
    color = vector<int>(N+1);
    for(int i=1; i<=N; i++) {
        cin >> color[i];
        sets[i].insert(color[i]);
    }

    Q += N-1;
    while(Q--) {
        int cmd, a; cin >> cmd >> a;
        querys.emplace_back(cmd, a);
    }
    for(auto it = querys.rbegin(); it != querys.rend(); it++) {
        if(it->first == 1) merge(it->second, parent[it->second]);
        else ans.emplace_back(sets[f(it->second)].size());
    }
    for(auto it = ans.rbegin(); it != ans.rend(); it++)
        cout << *it << endl;

    return 0;
}