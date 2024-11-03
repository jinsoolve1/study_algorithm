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

int N, M;
int score[5][5] = {
        {10,8,7,5,1},
        {8,6,4,3,1},
        {7,4,3,2,1},
        {5,3,2,2,1},
        {1,1,1,1,0}
};
int grid[14][14];
int dp[14][14][1<<14];

int solve(int i, int j, int bit) {
    if(i == N) return 0;
    if(j == M) return solve(i+1, 0, bit);
    int &ret = dp[i][j][bit];
    if(ret != -1) return ret;
    ret = solve(i,j+1,(2*bit+1) % (1<<M));
    if(j != 0 && bit%2 == 1) ret = max(ret, score[grid[i][j-1]][grid[i][j]] + solve(i, j+1, 2*(bit-1) % (1<<M)));
    if(i != 0 && bit/(1<<(M-1)) == 1) ret = max(ret, score[grid[i-1][j]][grid[i][j]] + solve(i,j+1,2*bit % (1<<M)));
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);

    cin >> N >> M;
    for(int i=0; i<N; i++) {
        string s; cin >> s;
        for(int j=0; j<M; j++) {
            grid[i][j] = s[j] - 'A';
            if(grid[i][j] == 5) grid[i][j]--;
        }
    }
    cout << solve(0,0,0) << '\n';

    return 0;
}