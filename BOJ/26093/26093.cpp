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
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int N, K;
pii ribbon[100][3]; //ribbon[cat] = (ribbon's idx, satisfy)
int dp[100][4];

int solve(int cat, int used) {
    if(cat == N) return 0;
    int color;
    for(color=0; color<3; color++) {
        if(used == ribbon[cat][color].first) break;
    }
    int &ret = dp[cat][color];
    if(ret != -1) return ret;
    if(color != 0) ret = max(ret, solve(cat+1, ribbon[cat][0].first) + ribbon[cat][0].second);
    if(color != 1) ret = max(ret, solve(cat+1, ribbon[cat][1].first) + ribbon[cat][1].second);
    if(color != 2) ret = max(ret, solve(cat+1, ribbon[cat][2].first) + ribbon[cat][2].second);
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);

    cin >> N >> K;
    for(int i=0; i<N; i++) {
        ribbon[i][0] = ribbon[i][1] = ribbon[i][2] = pii(-1,0);
        for(int j=0; j<K; j++) {
            int x; cin >> x;
            if(ribbon[i][0].second < x) {
                ribbon[i][2] = ribbon[i][1];
                ribbon[i][1] = ribbon[i][0];
                ribbon[i][0] = pii(j,x);
            }
            else if(ribbon[i][1].second < x) {
                ribbon[i][2] = ribbon[i][1];
                ribbon[i][1] = pii(j,x);
            }
            else if(ribbon[i][2].second < x) ribbon[i][2] = pii(j,x);
        }
    }
    cout << solve(0,-1) << '\n';


    return 0;
}