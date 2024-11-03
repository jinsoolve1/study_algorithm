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
#define x first
#define y second

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int N, M;
int board[9][9];
vector<pii> camLoc;
bool visited[9][9];
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
vector<int> camera[6];

bool out_of_bound(int x, int y) { return x<1 || x>N || y<1 || y>M; }
int blind_spot(int camDir) {
    memset(visited, 0, sizeof visited);
    for(pii here : camLoc) {
        int d = camDir%4; camDir /= 4;
        for(int nd : camera[board[here.x][here.y]]) {
            nd = (nd + d) % 4;
            int nx = here.x, ny = here.y;
            while(true) {
                if(out_of_bound(nx,ny) || board[nx][ny]==6) break;
                visited[nx][ny] = true;
                nx += dx[nd], ny += dy[nd];
            }
        }
    }
    int ret = N*M;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            if(board[i][j]) ret--;
            else ret -= visited[i][j];
        }
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    camera[1].emplace_back(0);
    camera[2].emplace_back(0); camera[2].emplace_back(2);
    camera[3].emplace_back(0); camera[3].emplace_back(1);
    camera[4].emplace_back(0); camera[4].emplace_back(1); camera[4].emplace_back(2);
    camera[5].emplace_back(0); camera[5].emplace_back(1); camera[5].emplace_back(2); camera[5].emplace_back(3);

    cin >> N >> M;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cin >> board[i][j];
            if(1 <= board[i][j] && board[i][j] <= 5) camLoc.emplace_back(i,j);
        }
    }
    int ans = INF;
    for(int bit = pow(4,camLoc.size())-1; bit >= 0; bit--) {
        ans = min(ans, blind_spot(bit));
    }
    cout << ans << endl;

    return 0;
}