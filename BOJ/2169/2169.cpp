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
#define f first
#define s second
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int N, M;
int Mars[1010][1010];
int dp[1010][1010][3]; // 0:left,right,down, 1:right,down, 2:left,down
int dx[] = {1,0,0};
int dy[] = {0,1,-1};

bool out_of_bound(int x, int y) {
    return x<1 || x>N || y<1 || y>M;
}
int solve(int x, int y, int dir) {
    if(x == N && y == M) return Mars[x][y];
    int &ret = dp[x][y][dir];
    if(ret != -INF) return ret;
    for(int d=0; d<3; d++) {
        int nx = x+dx[d], ny = y+dy[d];
        if((dir==1 && d==2) || (dir==2 && d==1)) continue;
        if(out_of_bound(nx,ny)) continue;
        ret = max(ret, solve(nx,ny,d) + Mars[x][y]);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(&dp[0][0][0], &dp[1009][1009][3], -INF);

    cin >> N >> M;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cin >> Mars[i][j];
        }
    }
    cout << solve(1,1,0) << '\n';

    return 0;
}