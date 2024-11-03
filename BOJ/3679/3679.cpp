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
    ll idx, x, y;

    Point() {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    Point(ll _idx, ll _x, ll _y) : idx(_idx), x(_x), y(_y) {}
    ll cross(Point other) {
        return x*other.y - y*other.x;
    }
    ll dist(Point other) {
        return pow(x-other.x,2) + pow(y-other.y,2);
    }
    Point operator-(Point other) const {
        return Point(x-other.x, y-other.y);
    }
    bool operator<(Point other) const {
        if(y == other.y) return x < other.x;
        return y < other.y;
    }
};

Point refer;
bool cmp(Point a, Point b) {
    ll ccw = (a-refer).cross(b-refer);
    if(ccw == 0) return refer.dist(a) < refer.dist(b);
    return ccw > 0;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int c; cin >> c;
    while(c--) {
        int n; cin >> n;
        vector<Point> ps;
        for(int i=0; i<n; i++) {
            int x, y; cin >> x >> y;
            ps.emplace_back(i,x,y);
        }
        sort(all(ps));
        refer = ps.front();
        sort(ps.begin()+1, ps.end(), cmp);
        int r = ps.size()-1, l=r;
        while(l>0 && (ps[l-1]-refer).cross(ps[r]-refer) == 0) l--;
        while(l<r) swap(ps[l++],ps[r--]);
        for(Point p : ps) cout << p.idx << ' ';
        cout << '\n';
    }


    return 0;
}