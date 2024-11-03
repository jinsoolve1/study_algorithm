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

int max_lv=0;
int N;
vector<int> tree;
vector<int> v[18][18];

void dfs(int u, int lv) {
    if(lv == max_lv) return;
    dfs(2*u, lv+1);
    for(int s=0; s<=lv; s++) {
        for(int e=lv; e<max_lv; e++) {
            v[s][e].emplace_back(tree[u]);
        }
    }
    dfs(2*u+1, lv+1);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    while(pow(2,max_lv)-1 < N) max_lv++;
    tree = vector<int>(N+1);
    for(int i=1; i<=N; i++) cin >> tree[i];
    dfs(1,0);
    ll ans = 0, psum;
    for(int s=0; s<max_lv; s++) {
        for(int e=s; e<max_lv; e++) {
            psum = 0;
            for(ll x : v[s][e]) {
                psum = max((ll)0, psum+x);
                ans = max(ans, psum);
            }
        }
    }
    if(ans == 0) {
        ans = numeric_limits<ll>::min();
        for(int i=1; i<=N; i++) ans = max(ans, (ll)tree[i]);
    }
    cout << ans << endl;

    return 0;
}