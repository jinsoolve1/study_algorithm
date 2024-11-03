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

int N; ll K;
ll dp[51][101];
string ans = "";

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, 0, sizeof dp);
    for(int p=0; p<=100; p++)
        dp[0][p] = 1, dp[1][p] = 2;
    dp[0][50] = 0, dp[1][51] = 1;

    for(int n=2; n<=50; n++) {
        for(int p=0; p<50; p++) dp[n][p] = (1LL << n);
        for(int p=50; p<=100; p++) dp[n][p] = dp[n-1][p+1] + dp[n-1][p-1];
    }

    int prefix = 50;
    cin >> N >> K; K++;
    if(K > dp[N][50]) {
        cout << "-1\n";
        return 0;
    }
    bool alright = true; // 올바른 괄호인가
    for(int n=N; n>=1; n--) {
        ll val = dp[n-1][prefix+1]; // '('를 배치했을 때 가능한 괄호ㄴㄴ 문자열 개수
        if(!alright) val = 1LL << (n-1);
        if(val >= K) ans += '(', prefix++;
        else ans += ')', K -= val, prefix--;
        if(prefix < 50) alright = false;
    }
    cout << ans << '\n';

    return 0;
}