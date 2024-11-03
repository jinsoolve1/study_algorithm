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

bool cmp(pii a, pii b) {
    if(a.second == b.second) return a.first < b.first;
    return a.second > b.second;
}
int n;
vector<pii> v;
vector<int> lis;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for(int i=0; i<n; i++) {
        int j, l, r; cin >> j >> l >> r;
        v.emplace_back(l,r);
    }
    sort(all(v), cmp); v.erase(unique(all(v)), v.end());
    for(pii x : v) {
        auto it = upper_bound(all(lis), x.first);
        if(it == lis.end()) lis.emplace_back(x.first);
        else *it = x.first;
    }
    cout << lis.size() << '\n';

    return 0;
}