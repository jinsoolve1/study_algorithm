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
using ti3 = tuple<int, int, int>;

struct Vector {
    double x, y;

    Vector() {}
    Vector(double pm1, double pm2) : x(pm1), y(pm2) {}

    double cross(const Vector &other) const {
        return x*other.y - y*other.x;
    }
    double dist(const Vector &other) const {
        return sqrt(pow(x-other.x,2) + pow(y-other.y,2));
    }

    Vector operator -(Vector other) const {
        return Vector(x-other.x, y-other.y);
    }

    bool operator <(Vector other) const {
        if(y == other.y) return x < other.x;
        return y < other.y;
    }
};

int C;
vector<Vector> points;
vector<Vector> convex;

bool cmp(Vector a, Vector b) {
    double res = (a-points[0]).cross(b-points[0]);
    if(res == 0) return points[0].dist(a) < points[0].dist(b);
    return res > 0;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed; cout.precision(9);

    cin >> C;
    for(int i=0; i<C; i++) {
        double x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    sort(all(points));
    sort(points.begin()+1, points.end(), cmp);
    for(int i=0; i<points.size(); i++) {
        Vector p3 = points[i];
        while(convex.size() >= 2) {
            Vector p2 = convex.back();
            Vector p1 = convex[convex.size()-2];
            if((p2-p1).cross(p3-p2) > 0) break;
            convex.pop_back();
        }
        convex.emplace_back(p3);
    }
    double ans = 0;
    for(int i=0; i<convex.size(); i++) {
        for(int j=i+1; j<convex.size(); j++) {
            ans = max(ans, convex[i].dist(convex[j]));
        }
    }
    cout << ans << '\n';

    return 0;
}