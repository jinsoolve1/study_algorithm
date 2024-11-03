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

ll n, m;
vector<Point> white, black;
vector<Point> convex_white, convex_black;
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
// 모든 B가 A의 영역 안에 있는지를 반환
// 점을 오른쪽으로 선을 끝까지 그었을 때 만나는 선분의 개수가 홀수면 내부, 짝수면 외부에 있는 것이다.
bool isIncluded(vector<Point> &A, vector<Point> &B) {
    int sza = A.size(), szb = B.size();
    for(int b=0; b<szb; b++) {
        Point pointNB(B[b].x + INF, B[b].y);
        int cnt = 0;
        for (int a = 0; a < sza; a++) {
            int na = (a + 1) % sza;
            if((B[b].y < A[na].y) != (B[b].y < A[a].y)) cnt += isIntersect(A[a], A[na], B[b], pointNB);
        }
        if(cnt%2 == 0) return false;
    }
    return true;
}
string solve() {
    int szb = convex_black.size(), szw = convex_white.size();

    for(int b=0; b<szb; b++) {
        int nb = (b+1) % szb;
        for(int w=0; w<szw; w++) {
            int nw = (w+1) % szw;
            if(isIntersect(convex_black[b], convex_black[nb], convex_white[w], convex_white[nw])) return "NO";
        }
    }
    if(szb < 3 || szw < 3) return "YES";
    // 영역을 구축할 수 있으려면 각 점들이 3개 이상이어야 한다.

    // 검은색 점 영역 안에 모든 흰색 점이 들어가 있는지 확인
    if(isIncluded(convex_black, convex_white)) return "NO";
    // 흰색 점 영역 안에 모든 검은색 점이 들어가 있는지 확인
    if(isIncluded(convex_white, convex_black)) return "NO";

    return "YES";
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        black.resize(0); white.resize(0);
        convex_black.resize(0); convex_white.resize(0);

        cin >> n >> m;
        for(int i=0; i<n; i++) {
            ll x, y; cin >> x >> y;
            black.emplace_back(x,y);
        }
        for(int i=0; i<m; i++) {
            ll x, y; cin >> x >> y;
            white.emplace_back(x,y);
        }
        Graham_Scan(black, convex_black);
        Graham_Scan(white, convex_white);
        cout << solve() << '\n';
    }


    return 0;
}