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

struct Type {
    int x, y, h;

    Type() {}
    Type(int _x, int _y, int _h) : x(_x), y(_y), h(_h) {}
    bool operator<(Type &other) const {
        return h < other.h;
    }
    bool operator>(Type &other) const {
        return h > other.h;
    }
};


int N, M, H;
int hole[1002][1002][4];
vector<vector<int>> waterHeight;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
priority_queue<Type, vector<Type>, greater<>> pq;

bool out_of_bound(int x, int y) { return x<1 || x>N || y<1 || y>M; }

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> H;
    memset(hole, -1, sizeof hole);
    waterHeight = vector<vector<int>>(N+2, vector<int>(M+2,H));
    for(int i=0; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            int h; cin >> h;
            hole[i][j][1] = hole[i+1][j][0] = h;
        }
    }
    for(int i=1; i<=N; i++) {
        for(int j=0; j<=M; j++) {
            int h; cin >> h;
            hole[i][j][3] = hole[i][j+1][2] = h;
        }
    }

    // search outer wall
    // horizontal wall
    for(int i=1; i<=N; i++) {
        if(hole[i][1][2] != -1) {
            pq.emplace(i,1,hole[i][1][2]);
            waterHeight[i][1] = min(waterHeight[i][1], hole[i][1][2]);
        }
        if(hole[i][M][3] != -1) {
            pq.emplace(i,M,hole[i][M][3]);
            waterHeight[i][M] = min(waterHeight[i][M], hole[i][M][3]);
        }
    }
    // vertical wall
    for(int j=1; j<=M; j++) {
        if(hole[1][j][0] != -1) {
            pq.emplace(1,j,hole[1][j][0]);
            waterHeight[1][j] = min(waterHeight[1][j], hole[1][j][0]);
        }
        if(hole[N][j][1] != -1) {
            pq.emplace(N,j,hole[N][j][1]);
            waterHeight[N][j] = min(waterHeight[N][j], hole[N][j][1]);
        }
    }

    while(!pq.empty()) {
        int x = pq.top().x, y = pq.top().y, h = pq.top().h;
        pq.pop();
        if(waterHeight[x][y] < h) continue;
        for(int d=0; d<4; d++) {
            if(hole[x][y][d] == -1) continue;
            int nx = x+dx[d], ny = y+dy[d];
            if(out_of_bound(nx,ny)) continue;
            int nh = max(h, min(waterHeight[nx][ny], hole[x][y][d]));
            if(waterHeight[nx][ny] <= nh) continue;
            pq.emplace(nx,ny,nh);
            waterHeight[nx][ny] = nh;
        }
    }
    int ans = 0;
    for(int i=1; i<=N; i++)
        for(int j=1; j<=M; j++)
            ans += waterHeight[i][j];
    cout << ans << endl;

    return 0;
}