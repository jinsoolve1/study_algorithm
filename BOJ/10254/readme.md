## [백준 10254  - 고속도로](https://www.acmicpc.net/problem/10254)

### 풀이

- convex hull algorithm (Graham's Scan)
- rotating calipers

convex hull 알고리즘으로 바깥쪽 나라들을 고른다.  
다만, worst-case의 경우 convex 나라들의 수도 $8 * 10^5$ 이 되므로 이중 for문을 사용하면 시간초과가 난다.  
이를 '회전하는 캘리퍼스'로 해결한다.  
1. convex 나라들 중에서 x가 가장 작은 나라를 l, x가 가장 큰 나라를 r이라 하자.
2. convex 기준으로 l의 다음 나라를 nl, r의 다음 나라를 nr 이라 하자.
3. nl-l 벡터와 nr-r 벡터를 외적했을 때 값을 res이라 하자.
   1. if res < 0, l을 다음 나라로 옮긴다.
   2. else, r을 다음 나라로 옮긴다.
4. 3번 과정을 convex 나라의 수만큼 반복한다.

```C++
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
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

struct Vector {
    ll x, y;

    Vector() {}
    Vector(ll _x, ll _y) : x(_x), y(_y) {}
    ll cross(Vector other) {
        return x*other.y - y*other.x;
    }
    ll minDist(Vector other) {
        return pow(x-other.x,2) + pow(y-other.y,2);
    }
    Vector operator-(Vector other) const {
        return Vector(x-other.x, y-other.y);
    }
    bool operator<(Vector other) const {
        if(y == other.y) return x < other.x;
        return y < other.y;
    }
    void print() {
        cout << x << ' ' << y << ' ';
    }
};

ll n;
vector<Vector> cities;
vector<Vector> convex;

bool cmp(Vector a, Vector b) {
    ll res = (a - cities.front()).cross(b - cities.front());
    if(res != 0) return res > 0;
    return cities.front().minDist(a) < cities.front().minDist(b);
}

void Graham_Scan() {
    sort(all(cities));
    sort(cities.begin()+1, cities.end(), cmp);
    for(Vector p3 : cities) {
        while(convex.size() >= 2) {
            Vector p2 = convex.back();
            Vector p1 = convex[convex.size() - 2];
            ll ccw = (p2-p1).cross(p3-p2);
            if(ccw > 0) break;
            convex.pop_back();
        }
        convex.emplace_back(p3);
    }
}
void Rotating_Calipers() {
    int sz = convex.size();
    ll ans = 0; int l=0, r=0;
    for(int k=0; k<sz; k++) {
        if(convex[l].x > convex[k].x) l = k;
        if(convex[r].x < convex[k].x) r = k;
    }

    int L = l, R = r;
    ll maxDist = convex[l].minDist(convex[r]);
    for(int _=0; _<sz; _++) {
        int nl = (l+1)%sz, nr = (r+1)%sz;
        ll ccw = (convex[nl] - convex[l]).cross(convex[nr] - convex[r]);
        if(ccw < 0) l = (l+1)%sz;
        else r = (r+1)%sz;
        ll minDist = convex[l].minDist(convex[r]);
        if(maxDist < minDist) {
            maxDist = minDist;
            L = l, R = r;
        }
    }
    convex[L].print(); convex[R].print();
    cout << '\n';
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        cities.resize(0); convex.resize(0);

        cin >> n;
        for(int i=0; i<n; i++) {
            ll x, y; cin >> x >> y;
            cities.emplace_back(x,y);
        }
        Graham_Scan();
        Rotating_Calipers();
    }


    return 0;
}
```