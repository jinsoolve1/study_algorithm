## [백준 18251 - 내 생각에 A번인 단순 dfs 문제가 이 대회에서 E번이 되어버린 건에 관하여 (Easy)](https://www.acmicpc.net/problem/18251)

### 알고리즘
- dfs 탐색
- 스위핑

### 풀이
1. 입력으로 들어오는 값은 2^k-1 형태이고, k<=18이다.  
   이는 최대 18층짜리 포화 이진트리라는 의미가 된다.
2. v[s][e] := depth가 s ~ e 범위의 모든 노드의 가중치값들을 왼쪽부터 순서대로 저장한 배열이다.  
   dfs탐색을 하면서 왼쪽 자식들 -> 현재 노드 -> 오른쪽 자식들 순으로 방문하면서 배열에 노드의 가중치를 추가하면 된다.
3. 모든 v들에 대하여 스위핑하면서 연속된 노드들의 최대값을 찾는다.  
   psum은 부분합이고 항상 0보다 크거나 같은 값을 유지해준다.  
   ans은 psum과 비교하여 큰 값이 나오면 업데이트해준다.
4. 만약 모든 노드의 가중치가 음수이면, 노드 값들 중 가장 큰 값을 출력한다.

시간복잡도는 s * e * v[s][e].length() = 18 * 18 * 262,143 = 약 8e7이다. 

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
#include <set>
#include <unordered_set>
#include <climits>

#define endl "\n"
#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int max_lv=0;
int N;
vector<int> tree;
vector<int> v[18][18];

void dfs(int u, int lv) {
    if(lv == max_lv) return;
    dfs(2*u, lv+1);
    for(int s=0; s<=lv; s++) {
        for(int e=lv; e<max_lv; e++) {
            v[s][e].emplace_back(tree[u]);
        }
    }
    dfs(2*u+1, lv+1);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    while(pow(2,max_lv)-1 < N) max_lv++;
    tree = vector<int>(N+1);
    for(int i=1; i<=N; i++) cin >> tree[i];
    dfs(1,0);
    ll ans = 0, psum;
    for(int s=0; s<max_lv; s++) {
        for(int e=s; e<max_lv; e++) {
            psum = 0;
            for(ll x : v[s][e]) {
                psum = max((ll)0, psum+x);
                ans = max(ans, psum);
            }
        }
    }
    if(ans == 0) {
        ans = numeric_limits<ll>::min();
        for(int i=1; i<=N; i++) ans = max(ans, (ll)tree[i]);
    }
    cout << ans << endl;

    return 0;
}
```