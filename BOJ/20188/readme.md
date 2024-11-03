## [백준 20188 - 등산 마니아](https://www.acmicpc.net/problem/20188)

### 풀이
A와 B의 '산 정상을 거치는 가장 짧은 길'은 depth[A] + depth[B] - depth[LCS]가 된다.  
여기서 depth[A]는 루트에서부터의 깊이이고, LCS는 A와 B의 최소 공통 조상이다.

- 모든 노드 X에 대하여, depth[X]는 N-1번 호출될 것이다.  
- depth[LCS]가 호촐되는 횟수는 LCS의 자식 수에 따라 결정되는데, 노드 LCS의 직속 자식노드가 c1, c2, .., cm 이라고 하자.   
  si을 ci을 루트로 하는 subtree라 하자.  
  s1의 노드 하나와 LCS 본인 혹은 s2 ~ sm의 노드 하나를 고르면 depth[LCS]를 빼줘야 한다.  
  그 다음 s2의 노드 하나와 LCS 본인 혹은 s3 ~ sm의 노드 하나를 고르면 depth[LCS]를 빼줘야 한다.  
  ...  
  sm의 노드 하나와 LCS 본인을 고르면 depth[LCS]를 빼줘야 한다.  

해당 과정을 코드로 작성하면 다음과 같다.

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
#define Flow first
#define s second
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

const int mxn = 3e5;
ll N;
vector<int> g[mxn+1];
ll treeSize[mxn+1], depth[mxn+1];

int makeTree(int here, int lv) {
    depth[here] = lv;
    int ret = 1;
    for(int there : g[here]) {
        if(depth[there] != -1) continue;
        ret += makeTree(there, lv+1);
    }
    return treeSize[here] = ret;
}
// here 노드가 LCS 역할을 하는 횟수
ll LCS(int here) {
    ll ret = 0;
    ll childNum = treeSize[here];
    for(int there : g[here]) {
        if(depth[there] < depth[here]) continue;
        ret += treeSize[there] * (childNum - treeSize[there]);
        childNum -= treeSize[there];
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N-1; i++) {
        int a, b; cin >> a >> b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    // make tree by root 1
    memset(treeSize, 0, sizeof treeSize);
    memset(depth, -1, sizeof depth);
    makeTree(1,0);

    // calculate the sum of diversity
    ll ans = 0;
    for(int i=1; i<=N; i++) {
        ans += (N-1)*depth[i];
        ans -= LCS(i)*depth[i];
    }
    cout << ans << '\n';

    return 0;
}
```