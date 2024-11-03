## [백준 4225 - 쓰레기 슈트](https://www.acmicpc.net/problem/4225)

### 알고리즘
- 기하학
- 볼록껍질
- 회전하는 캘리퍼스

### 풀이
1. 다각형의 convex hull을 찾는다.
2. 회전하는 캘리퍼스 알고리즘을 이용해, convex들 중에서 i -> ni(ni는 i의 다음 convex) 선분에서 가장 먼 점 j를 찾는다.
3. 선분 i-ni와 점 j의 거리는 (벡터 i->ni x 벡터 i->j)의 외적이 평행사변형의 넓이임을 이용해  
   선분 i-ni의 길이로 나누면 점과 선분 사이의 거리를 구할 수 있다.
4. 각 선분에 대한 점의 거리 중 최솟값이 정답이다.

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
    bool operator<(Point other) const {
        if(x == other.x) return y < other.y;
        return x < other.x;
    }
    void print() {
        cout << x << ' ' << y << ' ';
    }
};
int n;
vector<Point> points, convex;
Point reference;

bool cmp(Point a, Point b) {
    ll res = (a - reference).cross(b - reference);
    if(res != 0) return res > 0;
    return reference.dist(a) < reference.dist(b);
}
void Graham_Scan(vector<Point> &points, vector<Point> &convex) {
    sort(all(points));
    reference = points[0];
    sort(points.begin()+1, points.end(), cmp);
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
}
double Rotating_Calipers() {
    int sz = convex.size();
    int j = 1, nj = (j+1) % sz, pj = (j-1+sz) % sz;
    double ans = INF;
    for(int i=0; i<sz; i++) {
        int ni = (i+1) % sz;
        while((convex[ni]-convex[i]).crossSign(convex[nj]-convex[j]) > 0) j = (j+1)%sz, nj = (nj+1)%sz, pj = (pj+1)%sz;
        while((convex[ni]-convex[i]).crossSign(convex[j]-convex[pj]) < 0) j = (j-1+sz)%sz, nj = (nj-1+sz)%sz, pj = (pj-1+sz)%sz;
        double dist = abs((convex[ni]-convex[i]).cross(convex[j]-convex[i]));
        dist /= sqrt(convex[i].dist(convex[ni]));
        ans = min(ans, dist);
    }
    return ans;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cout << fixed; cout.precision(2);

    for(int tc=1; ; tc++){
        cin >> n;
        if(n == 0) break;
        points.resize(n); convex.resize(0);
        for(int i=0; i<n; i++) cin >> points[i].x >> points[i].y;
        Graham_Scan(points, convex);
        cout << "Case " << tc << ": " << ceil(Rotating_Calipers()*100)/100 << endl;
    }

    return 0;
}
```