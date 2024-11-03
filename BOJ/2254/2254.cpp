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
        return (x == other.x) && (y == other.y);
    }
    bool operator!=(Point other) const {
        return !(*this == other);
    }
    bool operator<(Point other) const {
        if(x == other.x) return y < other.y;
        return x < other.x;
    }
    void print() {
        cout << x << ' ' << y << ' ';
    }
};

int N;
Point P;
vector<Point> points;
Point reference;
bool used[1010];

bool cmp(Point a, Point b) {
    ll res = (a - reference).cross(b - reference);
    if(res != 0) return res > 0;
    return reference.dist(a) < reference.dist(b);
}
bool isIntersect(Point p1, Point p2, Point p3, Point p4) {
    ll p1p2 = (p2-p1).crossSign(p3-p2) * (p2-p1).crossSign(p4-p2); // 선분 p1p2 기준
    ll p3p4 = (p4-p3).crossSign(p1-p4) * (p4-p3).crossSign(p2-p4); // 선분 p3p4 기준

    // 두 직선이 일직선 상에 존재
    if(p1p2 == 0 && p3p4 == 0) {
        if(p2 < p1) swap(p1,p2);
        if(p4 < p3) swap(p3,p4);
        return p3 < p2 && p1 < p4;
    }
    return p1p2 <= 0 && p3p4 <= 0;
}
bool isIncluded(vector<Point> &A, Point B) {
    int sza = A.size();
    Point pointNB(B.x + INF, B.y);
    int cnt = 0;
    for (int a = 0; a < sza; a++) {
        int na = (a + 1) % sza;
        if((B.y < A[na].y) != (B.y < A[a].y)) cnt += isIntersect(A[a], A[na], B, pointNB);
    }
    if(cnt%2 == 0) return false;
    return true;
}
bool Graham_Scan(vector<Point> &points) {
    if(points.size() < 3) return false;
    sort(all(points));
    reference = points[0];
    sort(points.begin()+1, points.end(), cmp);

    vector<Point> convex;
    for(int i=0; i<points.size(); i++) {
        if(used[i]) continue;
        Point p3 = points[i];
        while(convex.size() >= 2) {
            Point p2 = convex.back();
            Point p1 = convex[convex.size() - 2];
            ll ccw = (p2-p1).cross(p3-p2);
            if(ccw > 0) break;
            convex.pop_back();
        }
        convex.emplace_back(p3);
    }
    auto it = points.begin();
    vector<Point> tmp;
    for(Point p : convex) {
        while(*it != p) tmp.emplace_back(*it++);
        it++;
    }
    while(it != points.end()) tmp.emplace_back(*it++);
    points = tmp;
    return isIncluded(convex, P);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(used, 0, sizeof used);

    cin >> N >> P.x >> P.y;
    points.resize(N);
    for(int i=0; i<N; i++) cin >> points[i].x >> points[i].y;
    int ans = 0;
    while(Graham_Scan(points)) ans++;
    cout << ans << '\n';

    return 0;
}