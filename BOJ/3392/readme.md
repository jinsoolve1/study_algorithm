## [백준 3392 - 화성 지도](https://www.acmicpc.net/problem/3392)

### 풀이1 - 좌표 압축
압축된 좌표로 지도를 모두 쪼개서 겹치는 지도가 없도록 한다.  
map을 이용해서 지도가 중복되지 않도록 모두 다 넣는다.  
map에 있는 모든 쪼개진 지도의 넓이의 합이 정답이다.
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
```

---
### 풀이2 - 스위핑
해당 풀이는 https://jason9319.tistory.com/58 블로그를 참고했다.  

직사각형은 왼쪽 아래(x1,y1) ~ 오른쪽 위(x2,y2)라 하자.  
x축 기준으로 왼쪽에서 오른쪽으로 탐색한다고 하자.   
x = x1, y = y1 ~ y2의 수직선은 직사각형의 시작선이고, x = x2, y = y1 ~ y2의 수직선은 직사각형의 끝선이다.  
해당 수직선들을 query라고 생각하고 x를 기준으로 정렬시킨다.  
y좌표들에 시작선을 만나면 +1을, 끝선을 만나면 -1을 해준다. 이 작업은 세그먼트 트리로 행한다.

1. 시작선을 만나면 {x - (가장 최근의 x좌표)} * (현재 활성화된 y좌표의 개수)가 추가할 넓이가 될 것이다.
2. 넓이를 구하고 나면, 현재 만난 수직선을 segment tree에 업데이트 시킨다.

### 후기
해당 풀이에서 세그먼트 트리의 update가 구간 변경으로 이루어져 원래는 lazy segment tree를 사용해야 하는 것처럼 보이나,
이 문제에서는 수직선의 query이므로 해당 구간이 시작선이 들어왔을 떄가 중요하고 정확히 끝선에서 해당 구간의 빼기가 이루어진다는 점으로 인해 
해당 노드가 범위에 포함된다면 +1, -1을 해주면 된다.  

cnt에는 들어온 수직선의 query를 기록하고 tree에는 해당 y좌표가 활성화되었는지의 여부를 저장한다.
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

struct Query {
    int x, y1, y2, diff;
    bool operator<(Query other) const {
        return x < other.x;
    }
};

class segment {
public:
    vector<ll> tree, cnt; //tree[node] := a[start ~ end] 의 합

    segment() {}
    segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size, 0);
        cnt.resize(size, 0);
    }
    void update(int node, int start, int end, int left, int right, ll diff) {
        if(right < start || end < left) return;
        if(left <= start && end <= right) cnt[node] += diff;
        else {
            update(node * 2, start, (start + end) / 2, left, right, diff);
            update(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
        }
        if(cnt[node]) tree[node] = end-start+1;
        else {
            if(start == end) tree[node] = 0;
            else tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
};

const int mxn = 3e4;
int N;
vector<Query> qs;
ll ans = 0;
segment root(mxn+1);

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        qs.push_back({x1,y1,y2-1,1});
        qs.push_back({x2,y1,y2-1,-1});
    }
    sort(all(qs));
    int previous_x = qs.front().x;
    for(Query convex : qs) {
        ans += (convex.x - previous_x) * root.tree[1];
        root.update(1,0,mxn,convex.y1, convex.y2, convex.diff);
        previous_x = convex.x;
    }
    cout << ans << '\n';

    return 0;
}
```