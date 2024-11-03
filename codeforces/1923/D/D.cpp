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

int n;
vector<ll> a, psum;
vector<int> lloc, rloc;

int binary_search_left(int idx) {
    if(idx == 1) return INF;
    int l = 1, r = idx-1;

    while(l<r) {
        int m = (l+r)/2 + (l+r)%2;
        ll sum = psum[idx-1] - psum[m-1];
        if(sum > a[idx]) l = m;
        else r = m-1;
    }
    if(l < idx-1 &&l > lloc[idx-1]) {
        l = lloc[idx-1];
        if(l == 0) return INF;
    }
    return (psum[idx-1] - psum[l-1] > a[idx] ? idx-l : INF);
}
int binary_search_right(int idx) {
    if(idx == n) return INF;
    if(a[idx] < a[idx+1]) return 1;
    int l = rloc[idx+1], r = n;
    if(l == n+1) return INF;

    while(l<r) {
        int m = (l+r)/2;
        ll sum = psum[m] - psum[idx];
        if(sum > a[idx]) r = m;
        else l = m+1;
    }
    if(r > idx+1 && r < rloc[idx+1]) {
        r = rloc[idx+1];
        if(r == n+1) return INF;
    }
    return (psum[r] - psum[idx] > a[idx] ? r-idx : INF);
}
int solve(int idx) {
    ll left_res = binary_search_left(idx);
    ll right_res = binary_search_right(idx);
    ll ret = min(left_res, right_res);
    return (ret == INF ? -1 : ret);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc; cin >> tc;
    while(tc--) {
        cin >> n;
        a = vector<ll>(n+1);
        psum = vector<ll>(n+1,0);
        lloc = vector<int>(n+1, 0);
        rloc = vector<int>(n+1, 0);
        for(int i=1; i<=n; i++) {
            cin >> a[i];
            psum[i] = psum[i-1] + a[i];
        }

        lloc[1] = 0;
        for(int i=2; i<=n; i++) {
            if(a[i] == a[i-1]) lloc[i] = lloc[i-1];
            else lloc[i] = i-1;
        }

        rloc[n] = n+1;
        for(int i=n-1; i>=1; i--) {
            if(a[i] == a[i+1]) rloc[i] = rloc[i+1];
            else rloc[i] = i+1;
        }

        for(int i=1; i<=n; i++) {
            cout << solve(i) << ' ';
        }
        cout << endl;
    }


    return 0;
}