## [백준 2049 - 가장 먼 두 점](https://www.acmicpc.net/problem/2049)

### 알고리즘
- 기히학
- convex hull
- rotating calipers

### 풀이
1. 점들을 정렬하고 중복되는 점들을 삭제해준다.
2. graham scan 알고리즘을 이용해 볼록 껍질 부분의 점들만 찾는다.
3. rotating calipers 알고리즘을 이용해 O(n) 시간복잡도로 가장 먼 거리의 점을 찾는다.

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

struct Point {
    ll x, y;

    Point() {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    ll cross(Point other) {
        return x*other.y - y*other.x;
    }
    ll crossSign(Point other) {
        ll res = this->cross(other);
        if(res > 0) return 1;
        else if(res < 0) return -1;
        return 0;
    }
    ll dist(Point other) {
        return pow(x-other.x,2) + pow(y-other.y,2);
    }
    Point operator-(Point other) const {
        return Point(x-other.x, y-other.y);
    }
    bool operator==(Point other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(Point other) const {
        if(x == other.x) return y < other.y;
        return x < other.x;
    }
    void print() {
        cout << x << ' ' << y << ' ';
    }
};

ll n;
Point reference;

vector<Point> Graham_Scan(vector<Point> &points) {
    sort(all(points)); points.erase(unique(all(points)), points.end());
    reference = points[0];
    auto cmp = [&](Point a, Point b) {
        ll res = (a - reference).cross(b - reference);
        if(res != 0) return res > 0;
        return reference.dist(a) < reference.dist(b);
    };
    sort(points.begin()+1, points.end(), cmp);

    vector<Point> convex;
    for(Point p3 : points) {
        while(convex.size() >= 2) {
            Point p2 = convex.back();
            Point p1 = convex[convex.size() - 2];
            ll ccw = (p2-p1).cross(p3-p2);
            if(ccw > 0) break;
            convex.pop_back();
        }
        convex.emplace_back(p3);
    }
    return convex;
}
ll Rotating_Calipers(vector<Point> &convex) {
    int sz = convex.size();
    int l=0, r=0;
    for(int k=0; k<sz; k++) {
        if(convex[l].x > convex[k].x) l = k;
        if(convex[r].x < convex[k].x) r = k;
    }

    ll ret = convex[l].dist(convex[r]);
    for(int _=0; _<sz; _++) {
        int nl = (l+1)%sz, nr = (r+1)%sz;
        ll ccw = (convex[nl] - convex[l]).crossSign(convex[nr] - convex[r]);
        if(ccw < 0) l = (l+1)%sz;
        else r = (r+1)%sz;
        ll res = convex[l].dist(convex[r]);
        ret = max(ret, res);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    vector<Point> points(n);
    for(int i=0; i<n; i++) cin >> points[i].x >> points[i].y;
    vector<Point> convex = Graham_Scan(points);
    cout << Rotating_Calipers(convex) << endl;

    return 0;
}
```