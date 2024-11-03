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

const ll mod = 1e5;
int N;
string S;
char open[] = {'(', '{', '['};
char close[] = {')', '}', ']'};
ll dp[200][200];

ll solve(int s, int e) {
    if(s>e) return 1;
    ll &ret = dp[s][e];
    if(ret != -1) return ret;
    ret = 0;
    for(int i=s+1; i<=e; i+=2) {
        for(int j=0; j<3; j++) {
            if((S[s] == open[j] || S[s] == '?') && (S[i] == close[j] || S[i] == '?')) {
                ret += solve(s+1,i-1) * solve(i+1,e);
                if(ret >= mod) ret = ret%mod + mod;
            }
        }
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);
    cin >> N >> S;
    ll ans = solve(0,N-1);
    if(ans >= mod) {
        cout.width(5); cout.fill('0');
        cout << ans % mod << endl;
    }
    else cout << ans;

    return 0;
}