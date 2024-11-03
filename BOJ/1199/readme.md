## [백준 1199 - 오일러 회로](https://www.acmicpc.net/problem/1199)

### 알고리즘
- 그래프 탐색
- DFS
- 오일러 경로(회로)

### 풀이
그래프의 모든 간선을 정확히 1번씩만 방문하는 연속된 경로인데 시작점과 도착점이 같으면 오일러 회로가 되고, 다르면 오일러 경로가 된다.  
이 문제는 오일러 회로를 찾는 문제다. 오일러 회로를 찾는데는 Hierholzer's Algorithm 을 사용하면 된다.  

1. 오일러 회로의 존재여부는 무향 그래프이므로 차수(degree)가 홀수인 정점이 없어야 한다.
2. 오일러 회로가 존재하면 DFS를 통해서 오일러 회로를 구한다.  
   이때 nxt 배열을 이용해서 there을 찾을 때의 연산을 최적화시킨다.  
   nxt[here]보다 작은 노드들은 이미 앞에서 다 방문한 후이므로 굳이 다시 확인할 필요가 없기 때문이다. 

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

int N;
int adj[1001][1001];
int nxt[1001], deg[1001];

void dfs(int here) {
    while(nxt[here] <= N) {
        int there = nxt[here];
        while(adj[here][there]) {
            adj[here][there]--;
            adj[there][here]--;
            dfs(there);
        }
        nxt[here]++;
    }
    cout << here << ' ';
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            cin >> adj[i][j];
            deg[i] += adj[i][j];
            deg[j] += adj[i][j];
        }
    }
    for(int i=1; i<=N; i++) {
        deg[i] /= 2;
        if(deg[i] % 2) {
            cout << "-1";
            return 0;
        }
    }
    dfs(1);
    return 0;
}
```

### 참고
https://sdy-study.tistory.com/233  
https://blog.encrypted.gg/625