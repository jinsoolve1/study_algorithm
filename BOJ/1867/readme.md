## [백준 1867 - 돌멩이 제거](https://www.acmicpc.net/problem/1867)

### 풀이
최소 버텍스 커버 문제이다. 즉, 이분매칭으로 해결할 수 있는 문제다.(by 쾨니그 정리)  

행 번호가 start node, 열 번호가 end node, 그리고 돌멩이가 그 둘을 잇는 edge라고 하자.  
<span style="color:grey">예를 들어, 돌멩이의 좌표가 (2,5)이면 노드2 -> 노드5의 유향 edge가 생성되는 것이다.</span>  
x번 행의 돌멩이들을 제거한다고 했을때, 돌멩이가 n개가 있으면 y1, y2, ... ,yn의 열에 영향을 끼친다.  
따라서 그래프를 버텍스 커버로 만들면 모든 엣지가 사용되므로 즉, 모든 돌멩이가 제거된다.  
이때 최소한의 회수로 제거해야 하므로 최소 버텍스 커버 문제가 되는 것이다.

쾨니그의 정리에 의해서 이는 이분매칭으로 해결할 수 있다.

### 후기
처음에는 2차원 펜윅트리로 풀려고 했으나 너무 단순하게 생각했는지 솔브를 받지 못 했다.  
유량 알고리즘과 이분 매칭을 좀 더 익숙해질 필요를 느꼈다.

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
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

const int mxn = 500;
int n, k;
vector<int> g[mxn+1];
bool Capacity[mxn+1];
int Prev[mxn+1];

bool dfs(int here) {
    // 연결된 모든 노드에 대해서 들어갈 수 있는지 시도
    for(int there : g[here]) {
        // 이미 처리한 노드는 더 이상 볼 필요가 없음
        if(Capacity[there]) continue;
        Capacity[there] = true;
        if(Prev[there] == 0 || dfs(Prev[there])) {
            Prev[there] = here;
            return true;
        }
    }
    return false;
}
int bipartite() {
    memset(Prev, 0, sizeof Prev);
    int ans = 0;
    for(int i=1; i<=n; i++) {
        memset(Capacity, 0, sizeof Capacity);
        ans += dfs(i);
    }
    return ans;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    while(k--) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
    }
    cout << bipartite() << '\n';


    return 0;
}
```