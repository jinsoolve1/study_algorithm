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

int N;
vector<ll> A;

ll solve(int s, int e) {
    if(s == e) return A[s]*A[s];

    int m = (s+e)/2;
    ll ret = max(solve(s,m), solve(m+1,e));
    int l = m, r = m+1;
    ll sum = A[l] + A[r], minVal = min(A[l],A[r]);
    ret = max(ret, sum*minVal);
    while(s!=l || r!=e) {
        ll lval = (s<l) ? A[l-1] : -1;
        ll rval = (r<e) ? A[r+1] : -1;

        if(lval >= rval) {
            sum += A[--l];
            minVal = min(minVal, A[l]);
        }
        else {
            sum += A[++r];
            minVal = min(minVal, A[r]);
        }
        ret = max(ret, sum*minVal);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    A.resize(N+1);
    for(int i=1; i<=N; i++) cin >> A[i];
    cout << solve(1,N) << endl;

    return 0;
}