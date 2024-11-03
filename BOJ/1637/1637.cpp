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

struct Type {
    ll l, r, d;
};

int N;
vector<Type> input;

ll count(ll s, ll e) {
    ll ret = 0;
    for(Type in : input) {
        if(e < in.l || in.r < s) continue;
        int sn = 0;
        if(in.l < s) sn = (s-in.l)/in.d + ((s-in.l)%in.d != 0);
        int en = (min(e,in.r) - in.l)/in.d;
        ret += en-sn+1;
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N; i++) {
        int a, c, b; cin >> a >> c >> b;
        input.push_back({a,c,b});
    }
    ll l=1, r=INF2;
    while(l<r) {
        ll m = (l+r)/2;
        if(count(l,m)%2 == 1) r = m;
        else l = m+1;
    }
    ll cnt = count(r,r);
    if(cnt%2 == 1) cout << r << ' ' << cnt << '\n';
    else cout << "NOTHING\n";

    return 0;
}