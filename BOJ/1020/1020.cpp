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

ll pow_10[] = { 1,10,100,1000,10000,100000,1000000, 10000000, 100000000, 1000000000, 10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000 };
int line[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};
ll dp[16][106];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(&dp[0][0], &dp[15][106], numeric_limits<ll>::max());

    for(int a=0; a<10; a++)
        dp[1][line[a]] = min(dp[1][line[a]], (ll)a);
    for(int i=2; i<=15; i++) {
        for(int num=0; num<10; num++) {
            for(int j=0; j<=105; j++) {
                if(dp[i-1][j] == numeric_limits<ll>::max()) continue;
                dp[i][j+line[num]] = min(dp[i][j+line[num]], pow_10[i-1]*num + dp[i-1][j]);
            }
        }
    }

    string num; cin >> num;
    int numLen = (int)num.length(), lines = 0;
    ll val, res, ans = pow_10[numLen];
    for(int i=numLen-1, ri=0; i>=0; i--, ri++) {
        lines += line[num[i]-'0'];
        if(i>0) val = stoll(num.substr(0,i));
        else val = 0;
        for(int n=0; n<10; n++) {
            if(ri == 0) {
                if(line[n] != line[num[i]-'0']) continue;
                res = val*pow_10[ri+1] + n;
                if(res == stoll(num)) continue;
                ans = min(ans, (res + pow_10[numLen] - stoll(num)) % pow_10[numLen]);
            }
            else {
                res = dp[ri][lines - line[n]];
                if(res == numeric_limits<ll>::max()) continue;
                res = val*pow_10[ri+1] + n*pow_10[ri] + res;
                if(res == stoll(num)) continue;
                ans = min(ans, (res + pow_10[numLen] - stoll(num)) % pow_10[numLen]);
            }
        }
    }
    cout << ans << '\n';

    return 0;
}