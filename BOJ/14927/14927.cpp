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
bool bulb[18][18];
int dx[] = {0,-1,1,0,0};
int dy[] = {0,0,0,-1,1};

bool out_of_bound(int x, int y) { return x<0 || x>=N || y<0 || y>=N; }
void turn(int x, int y) {
    for(int d=0; d<5; d++) {
        int nx = x+dx[d], ny = y+dy[d];
        if(out_of_bound(nx,ny)) continue;
        bulb[nx][ny] = !bulb[nx][ny];
    }
}
int solve(int x, int y, int bit) {
    if(y == N) return solve(x+1, 0, bit);
    if(x == N) return (bit == 0 ? 0 : INF);
    int ret = INF;
    bit = (2*bit + bulb[x][y]) % (1<<N);
    if(x==0 || bulb[x-1][y] == 0)
        ret = min(ret, solve(x,y+1,bit));
    if(x==0 || bulb[x-1][y] == 1) {
        turn(x,y);
        ret = min(ret, solve(x,y+1,bit^3) + 1);
        turn(x,y);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            cin >> bulb[i][j];

    int res = solve(0,0,0);
    if(res == INF) res = -1;
    cout << res << '\n';

    return 0;
}