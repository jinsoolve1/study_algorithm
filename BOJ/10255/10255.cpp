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
int isIntersect(Point p1, Point p2, Point p3, Point p4) {
    ll p1p2p3 = (p2-p1).crossSign(p3-p2), p1p2p4 = (p2-p1).crossSign(p4-p2);
    ll p3p4p1 = (p4-p3).crossSign(p1-p4), p3p4p2 = (p4-p3).crossSign(p2-p4);
    ll p1p2 = p1p2p3 * p1p2p4; // 선분 p1p2 기준
    ll p3p4 = p3p4p1 * p3p4p2; // 선분 p3p4 기준

    // 두 직선이 일직선 상에 존재
    if(p1p2p3 == 0 && p1p2p4 == 0) {
        if(p2 < p1) swap(p1,p2);
        if(p4 < p3) swap(p3,p4);
        if(p3p4p1 == 0 && p3p4p2 == 0) { // 평행할 때
            if(p2 < p3 || p4 < p1) return 0; // 평행 하지만 겹치지 않음
            if(p2 == p3 || p4 == p1) return 1; // 한 점만 겹침
            return INF; // 해가 무수히 많음
        }
        return 1;
    }
    return p1p2 <= 0 && p3p4 <= 0;
}
int solve(vector<Point> &rec, Point A, Point B) {
    int ret = 0;
    for(int i=0; i<4; i++) {
        int ni = (i+1) % 4;
        int res = isIntersect(A,B,rec[i],rec[ni]);
        if(res == INF) return 4;
        ret += res;
        if(isIntersect(A,B,rec[i],rec[i])) ret--;
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    vector<Point> rec(4);
    Point A, B;
    while(T--) {
        int xmin, ymin, xmax, ymax; cin >> xmin >> ymin >> xmax >> ymax;
        rec[0] = Point(xmin,ymin), rec[1] = Point(xmax,ymin), rec[2] = Point(xmax,ymax), rec[3] = Point(xmin,ymax);
        cin >> A.x >> A.y >> B.x >> B.y;
        cout << solve(rec,A,B) << '\n';
    }


    return 0;
}