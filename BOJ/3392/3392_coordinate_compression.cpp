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
using ti4 = tuple<int, int, int, int>;

struct Map {
    int x1, y1, x2, y2;
    ll area;

    Map() {}
    Map(int pm1, int pm2, int pm3, int pm4) : x1(pm1), y1(pm2), x2(pm3), y2(pm4) {
        area = (x2-x1)*(y2-y1);
    }

    bool operator ==(Map other) const {
        return (x1 == other.x1) && (y1 == other.y1) && (x2 == other.x2) && (y2 == other.y2);
    }
    bool operator <(Map other) const {
        if(x1 == other.x1) return y1 < other.y1;
        return x1 < other.x1;
    }
};

int N;
vector<Map> maps;
vector<int> X, Y;
map<Map,bool> mp;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        maps.emplace_back(x1,y1,x2,y2);
        X.emplace_back(x1); X.emplace_back(x2);
        Y.emplace_back(y1); Y.emplace_back(y2);
    }
    sort(all(X)); X.erase(unique(all(X)), X.end());
    sort(all(Y)); Y.erase(unique(all(Y)), Y.end());
    for(Map map: maps) {
        int x1 = lower_bound(all(X), map.x1) - X.begin();
        int x2 = lower_bound(all(X), map.x2) - X.begin();
        int y1 = lower_bound(all(Y), map.y1) - Y.begin();
        int y2 = lower_bound(all(Y), map.y2) - Y.begin();
        for(int x=x1; x<x2; x++) {
            for(int y=y1; y<y2; y++) {
                mp[Map(X[x],Y[y],X[x+1],Y[y+1])] = true;
            }
        }
    }

    ll ans = 0;
    for(auto x : mp) {
        ans += x.first.area;
    }
    cout << ans << '\n';

    return 0;
}