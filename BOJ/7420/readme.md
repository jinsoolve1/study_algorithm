## [백준 7420 - 맹독 방벽](https://www.acmicpc.net/problem/7420)

### 알고리즘
- convex hull
- 기하학

### 풀이
1. 건물들의 convex hull을 구한다.
2. convex hull 건물들 사이의 모든 거리를 구한다.
3. 코너 부분은 부채꼴이지만 결국 모든 볼록 껍질의 코너를 합하면 원이 된다는 점을 알 수 있다.   
   볼록 껍질(convex hull)에서는 오목한 부분이 없기 때문에 전부 합치면 하나의 원이 된다.

```c++
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
#include <numbers>

#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

struct Point {
    ll x, y;

    Point() {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    ll cross(Point other) {
        return x*other.y - y*other.x;
    }
    ll dist(Point other) const {
        return pow(x-other.x,2) + pow(y-other.y,2);
    }
    bool operator<(Point other) const {
        if(x == other.x) return y < other.y;
        return x < other.x;
    }
    Point operator-(Point other) const {
        return Point(x-other.x, y-other.y);
    }
};

ll N, L;
vector<Point> buildings, convex;
Point refer;
bool cmp(Point a, Point b) {
    ll res = (a-refer).cross(b-refer);
    if(res == 0) return refer.dist(a) < refer.dist(b);
    return res > 0;
}
vector<Point> Graham_Scan(vector<Point> &points) {
    vector<Point> ret;
    sort(all(buildings));
    refer = buildings.front();
    sort(buildings.begin()+1, buildings.end(), cmp);
    for(Point p3 : buildings) {
        while(ret.size() >= 2) {
            Point p2 = ret.back();
            Point p1 = ret[ret.size() - 2];
            ll ccw = (p2-p1).cross(p3-p2);
            if(ccw > 0) break;
            ret.pop_back();
        }
        ret.emplace_back(p3);
    }
    return ret;
}
ll solve(vector<Point> &convex) {
    double ret = 2*M_PI*(double)L;
    int sz = convex.size();
    for(int i=0; i<sz; i++) {
        int ni = (i+1)%sz;
        ret += sqrt(convex[i].dist(convex[ni]));
    }
    return round(ret);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> L;
    for(int i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        buildings.emplace_back(x,y);
    }
    convex = Graham_Scan(buildings);
    cout << solve(convex) << '\n';

    return 0;
}
```