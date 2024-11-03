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

int N;
int dp[101][101];
bool ln[101][101];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, 0, sizeof dp);
    memset(ln, 0, sizeof ln);

    cin >> N;
    for(int i=0; i<N; i++) {
        int a, b; cin >> a >> b;
        ln[a][b] = ln[b][a] = true;
    }
    for(int e=1; e<=100; e++) {
        for(int s=e; s>=1; s--) {
            for(int k=s; k<e; k++) {
                dp[s][e] = max(dp[s][e], dp[s][k] + dp[k][e] + ln[s][e]);
            }
        }
    }
    cout << dp[1][100] << '\n';

    return 0;
}