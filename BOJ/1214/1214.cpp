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

ll d, p, q;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> d >> p >> q;
    if(p < q) swap(p,q);

    ll ans = numeric_limits<ll>::max();
    // d <= px + qy, x = 0 ~ q-1
    for(ll x=0; x<q && p*x<d+p; x++) {
        ll y = (d - p*x + q-1) / q;
        ans = min(ans, p*x + q*y);
    }
    cout << ans << endl;

    return 0;
}