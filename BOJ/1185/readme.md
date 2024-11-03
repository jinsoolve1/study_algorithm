## [백준 1185 - 유럽여행](https://www.acmicpc.net/problem/1185)

### 알고리즘
- 최소 스패닝 트리(MST)

### 풀이
1. 트리에서 출발점에서 시작해서 모든 정점을 방문하고 다시 출발점으로 돌아오는 경우를 생각해보자.  
   결국 u - v 연결 간선을 이용할 때, u와 v를 각각 한번, 간선은 2번 이용하는 것을 알 수 있다.  
   다만 출발점은 맨 처음에 비용을 내고 시작하므로 다른 노드들보다 한 번 더 방문한다.
2. 이를 이용해서 우선순위 큐에 C[u] + C[v] + L*2 를 넣어주고 작은 순으로 정렬한다.
3. Kruskal 알고리즘을 이용해서 merge할 수 있는 지를 확인하고 가능하다면 비용을 추가해준다.  
   시작 정점은 가장 도시 방문 비용이 적은 도시로 한다.

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

#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

const int mxn = 1e4+1;

struct type {
    int u, v, w;
};
struct cmp {
    bool operator()(type a , type b) {
        return a.w > b.w;
    }
};

int N, P;
int startCost;
int city[mxn];
int parent[mxn];
priority_queue<type, vector<type>, cmp> pq;

int find(int i) {
    if(i == parent[i]) return i;
    return parent[i] = find(parent[i]);
}
bool merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    parent[b] = a;
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i=0; i<mxn; i++) parent[i] = i;
    cin >> N >> P;
    startCost = INF;
    for(int i=1; i<=N; i++) {
        cin >> city[i];
        startCost = min(startCost, city[i]);
    }
    for(int i=1; i<=P; i++) {
        int s, e, l; cin >> s >> e >> l;
        pq.push({s,e,l*2+city[s]+city[e]});
    }
    ll ans = startCost;
    while(!pq.empty()) {
        type val = pq.top(); pq.pop();
        if(!merge(val.u, val.v)) continue;
        ans += val.w;
    }
    cout << ans << '\n';

    return 0;
}
```