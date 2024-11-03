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

int N, M, Building, K;
vector<pii> stars;
bool cnt[101][101];
vector<int> idx, jdx;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(cnt, 0, sizeof cnt);

    cin >> N >> M >> Building >> K;
    for(int i=0; i<K; i++) {
        int x, y; cin >> x >> y;
        stars.emplace_back(x,y);
        idx.emplace_back(x);
        jdx.emplace_back(y);
    }
    sort(all(idx)); idx.erase(unique(all(idx)), idx.end());
    sort(all(jdx)); jdx.erase(unique(all(jdx)), jdx.end());
    for(int i=0; i<K; i++) {
        stars[i] = pii(lower_bound(all(idx), stars[i].x) - idx.begin(),
                       lower_bound(all(jdx), stars[i].y) - jdx.begin());
        cnt[stars[i].x][stars[i].y] = true;
    }
    int ans = 0;
    for(int x=0; x<idx.size(); x++) {
        for(int y=0; y<jdx.size(); y++) {
            int ex = upper_bound(all(idx), idx[x] + Building) - idx.begin();
            int ey = upper_bound(all(jdx), jdx[y] + Building) - jdx.begin();
            int  res = 0;
            for(int nx=x; nx<ex; nx++) {
                for(int ny=y; ny<ey; ny++) {
                    res += cnt[nx][ny];
                }
            }
            ans = max(ans, res);
        }
    }
    cout <<  K - ans << '\n';

    return 0;
}