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

int n, q;
vector<int> cnt;
vector<ll> psum;

string solve(int l, int r) {
    if(l == r) return "NO";
    ll minVal = 2ll*(cnt[r]-cnt[l-1]) + ( r-l+1 - (cnt[r]-cnt[l-1]) ); // all 1s -> 2, other numbers -> 1
    if(psum[r]-psum[l-1] < minVal) return "NO";
    else return "YES";
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc; cin >> tc;
    while(tc--) {
        cin >> n >> q;

        cnt = vector<int>(n+1,0);
        psum = vector<ll>(n+1, 0);
        for(int i=1; i<=n; i++) {
            ll x; cin >> x;
            psum[i] = psum[i-1] + x;
            cnt[i] = cnt[i-1] + (x==1);
        }

        while(q--) {
            int l, r; cin >> l >> r;
            cout << solve(l,r) << endl;
        }
    }


    return 0;
}