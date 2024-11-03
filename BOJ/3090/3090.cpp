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

int N, T;
vector<int> A, a, ans;

bool possible(int s) {
    ll cnt = 0;
    a.assign(all(A));
    for(int i=0; i<N-1; i++) {
        if(a[i + 1] - a[i] > s) {
            cnt += a[i + 1] - a[i] - s;
            a[i + 1] = a[i] + s;
        }
    }
    for(int i=N-1; i>0; i--) {
        if(a[i - 1] - a[i] > s) {
            cnt += a[i - 1] - a[i] - s;
            a[i - 1] = a[i] + s;
        }
    }
    return cnt <= T;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> T;
    A = vector<int>(N);
    for(int i=0; i<N; i++) cin >> A[i];

    int l=0, r=1e9, m;
    while(l<=r) {
        m = (l+r)/2;
        if(possible(m)) ans.assign(all(a)), r= m - 1;
        else l=m+1;
    }
    for(int x : ans) cout << x << ' ';
    cout << endl;

    return 0;
}