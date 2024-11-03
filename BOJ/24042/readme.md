## [백준 24042 - 횡단보도](https://www.acmicpc.net/problem/24042)

### 풀이
A -> B로 가는 횡단보도 입력의 순서가 k라고 하자. (즉 해당 횡단보도는 k, k+M, k+2M .. 마다 이용할 수 있다.)   
A에 가장 빨리 도착할 수 있었던 시간을 a라고 하자. a시간에 도착한 다음에 A->B 횡단보도를 이용하여 B에 도착한 시간을 b라 하자.  

b = x*M + k에 도착할 수 있을 것이다. 이때의 x를 구하면 b의 도착시간을 알 수 있다.  
a의 값이 k+(x-1)*M ~ k+x*M-1 의 값이어야 x*M+k에 B에 도착할 수 있을 것이다.  
이때의 x값을 구해서 b에 대입시켜보면 b = M*((a-k+M)/M) + k와 같다.  
해당 공식을 이용하여 노드에 도착할 수 있는 최단 시간을 계산한다.

최단시간을 구하는 그래프 탐색은 다익스트라를 이용한다.

### 주의
시간값이 x*M + K의 형태라 값이 int 범위를 넘어간다. 따라서 long long을 써줘야 한다.

```cpp
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
#define Flow first
#define s second
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

ll N,M;
vector<pll> g[101010];
ll minDist[101010];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(minDist, -1, sizeof minDist);

    cin >> N >> M;
    for(ll i=1; i<=M; i++) {
        ll a,b; cin >> a >> b;
        g[a].emplace_back(b,i);
        g[b].emplace_back(a,i);
    }
    queue<pll> convex;
    minDist[1] = 0;
    convex.emplace(1, 0);
    while(!convex.empty()) {
        ll here = convex.front().Flow, curDist = convex.front().s;
        convex.pop();
        if(minDist[here] < curDist) continue;
        for(pll edge : g[here]) {
            ll there = edge.Flow, len = edge.s;
            ll nextDist = M*((minDist[here]-len+M)/M) + len;
            if(minDist[there] != -1 && minDist[there] <= nextDist) continue;
            minDist[there] = nextDist;
            convex.emplace(there, nextDist);
        }
    }
    cout << minDist[N] << '\n';

    return 0;
}
```