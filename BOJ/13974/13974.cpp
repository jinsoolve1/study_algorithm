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

int K;
int dp[5050][5050], loc[5050][5050]; //dp[i][j] := i+1 ~ j의 solve value
int psum[5001];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, 0, sizeof dp);
    memset(loc, 0, sizeof loc);
    memset(psum, 0, sizeof psum);

    int T; cin >> T;
    while(T--) {
        cin >> K;
        for(int i=1; i<=K; i++) {
            cin >> psum[i]; psum[i] += psum[i-1];
            dp[i-1][i] = 0; loc[i-1][i] = i;
        }
        for(int l=2; l<=K; l++) {
            for(int i=0, j=i+l; j<=K; i++, j++) {
                dp[i][j] = INF;
                for(int k=loc[i][j-1]; k<=loc[i+1][j]; k++) {
                    int res = dp[i][k] + dp[k][j] + psum[j] - psum[i];
                    if(dp[i][j] <= res) continue;
                    dp[i][j] = res;
                    loc[i][j] = k;
                }
            }
        }
        cout << dp[0][K] << '\n';
    }


    return 0;
}