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

ll n, k;
vector<ll> a, x;
vector<pll> v;

string solve() {
    ll tm = 0, bullet = 0;
    for(auto &val : v) {
        bullet += (val.first - tm) * k; tm = val.first;
        bullet -= val.second;
        if(bullet < 0) return "NO";
    }
    return "YES";
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc; cin >> tc;
    while(tc--) {
        cin >> n >> k;
        a.resize(n+1); x.resize(n+1); v.resize(0);
        for(int i=1; i<=n; i++) cin >> a[i];
        for(int i=1; i<=n; i++) cin >> x[i];
        for(int i=1; i<=n; i++) v.emplace_back(abs(x[i]), a[i]);
        sort(all(v));

        cout << solve() << endl;
    }


    return 0;
}
